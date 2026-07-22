#include "HintProvider.h"

#include <cctype>
#include <charconv>
#include <cstddef>
#include <system_error>

namespace {

std::string genericTipFor(QuestionType type) {
    switch (type) {
        case QuestionType::MultipleChoice:
            return "Seçenekleri tek tek elemeye çalış; açıkça yanlış olanları çıkar.";
        case QuestionType::TrueFalse:
            return "İfadeyi parça parça oku; tek bir kelime bile ifadeyi yanlış yapabilir.";
        case QuestionType::FillBlank:
            return "Boşluğa gelecek kelimeyi ders anlatımındaki sözdizimini hatırlayarak düşün.";
        case QuestionType::CompleteLine:
            return "Kodun geri kalanına bakarak eksik satırın ne yapması gerektiğini düşün.";
        case QuestionType::PredictOutput:
            return "Kodu satır satır, değişkenlerin değerini takip ederek zihninde çalıştır.";
        case QuestionType::FindError:
            return "Noktalı virgül, parantez ve tırnak işaretlerini tek tek kontrol et.";
        case QuestionType::FixCode:
            return "Hatanın hangi satırda olduğunu bulduktan sonra o satırı nasıl düzelteceğini düşün.";
        case QuestionType::OrderCode:
            return "Bir C++ programının genel akışını (tanımlama, işlem, çıktı) hatırla.";
        case QuestionType::Scenario:
            return "Senaryoda asıl ihtiyacın ne olduğunu belirle, seçenekleri ona göre ele.";
        case QuestionType::Matching:
            return "Önce kesin bildiğin eşleşmeleri yerleştir, kalanları elemeyle bul.";
        case QuestionType::WriteCode:
            return "Sorunun ne istediğini tekrar dikkatlice oku.";
    }
    return "Sorunun ne istediğini tekrar dikkatlice oku.";
}

int wordCount(const std::string& text) {
    int count = 0;
    bool inWord = false;
    for (const char character : text) {
        const bool isSpace = std::isspace(static_cast<unsigned char>(character)) != 0;
        if (!isSpace && !inWord) {
            ++count;
        }
        inWord = !isSpace;
    }
    return count;
}

std::string firstOptionNotAccepted(const Question& question) {
    for (std::size_t index = 0; index < question.options.size(); ++index) {
        const char letter = static_cast<char>('a' + static_cast<int>(index));
        bool isAccepted = false;
        for (const std::string& accepted : question.acceptedAnswers) {
            if (!accepted.empty() && accepted.front() == letter) {
                isAccepted = true;
                break;
            }
        }
        if (!isAccepted) {
            const char upperLetter = static_cast<char>('A' + static_cast<int>(index));
            return std::string(1, upperLetter) + ") " + question.options[index];
        }
    }
    return "";
}

std::string computedClueFor(const Question& question) {
    if (question.acceptedAnswers.empty()) {
        return "Sorunun ne istediğini tekrar dikkatlice oku.";
    }
    const std::string& answer = question.acceptedAnswers.front();

    switch (question.type) {
        case QuestionType::MultipleChoice: {
            const std::string wrongOption = firstOptionNotAccepted(question);
            return wrongOption.empty() ? "Seçenekleri tekrar dikkatlice karşılaştır."
                                        : wrongOption + " kesinlikle yanlış.";
        }
        case QuestionType::TrueFalse:
            return "Cevap genellikle ders anlatımındaki net ifadeyle doğrudan ilgilidir; "
                   "'her zaman/asla' gibi kesin ifadelere dikkat et.";
        case QuestionType::FillBlank:
        case QuestionType::CompleteLine:
            return "Doğru cevap " + std::to_string(wordCount(answer)) + " kelimeden oluşuyor.";
        case QuestionType::PredictOutput: {
            // from_chars rather than stoi: "is this answer a plain integer?"
            // is a question, not an error, and stoi answers it by throwing —
            // which meant swallowing an exception in an empty catch block.
            int value = 0;
            const auto* const begin = answer.data();
            const auto* const end = begin + answer.size();
            const auto parsed = std::from_chars(begin, end, value);
            const bool isWholeNumber = parsed.ec == std::errc{} && parsed.ptr == end;
            if (isWholeNumber) {
                if (value == 0) {
                    return "Doğru cevap sıfır.";
                }
                return std::string("Doğru cevap ") + (value > 0 ? "pozitif" : "negatif") +
                       " bir sayı.";
            }
            return "Doğru cevap " + std::to_string(wordCount(answer)) + " kelimeden oluşuyor.";
        }
        case QuestionType::FindError:
        case QuestionType::FixCode:
            return answer.empty() ? "Sorunun ne istediğini tekrar dikkatlice oku."
                                   : std::string("Doğru satır '") + answer.front() +
                                         "' harfiyle başlıyor.";
        case QuestionType::OrderCode:
            return "Sıralaman gereken toplam adım sayısı: " +
                   std::to_string(question.options.size()) + ".";
        case QuestionType::Scenario:
            return answer.empty() ? "Sorunun ne istediğini tekrar dikkatlice oku."
                                  : std::string("Doğru seçenek '") + answer.front() + "' şıkkı.";
        case QuestionType::Matching:
            return "Eşleştirmen gereken toplam madde sayısı: " +
                   std::to_string(question.options.size()) + ".";
        case QuestionType::WriteCode:
            return "Sorunun ne istediğini tekrar dikkatlice oku.";
    }
    return "Sorunun ne istediğini tekrar dikkatlice oku.";
}

}  // namespace

std::string generateHint(const Question& question, int hintLevel) {
    if (hintLevel <= 1) {
        return genericTipFor(question.type);
    }
    if (hintLevel == 2) {
        return computedClueFor(question);
    }
    return question.explanation;
}
