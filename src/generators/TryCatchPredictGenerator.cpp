#include "generators/TryCatchPredictGenerator.h"

#include <array>
#include <cstddef>
#include <string>

#include "FnvHash.h"
#include "ParameterDomain.h"

namespace {

constexpr std::array<const char*, 5> kFunctionNames = {
    "fonksiyon", "kontrol", "islem", "calis", "test",
};

constexpr ParameterDomain kValueDomain{1, 50};

std::string functionDeclaration(const std::string& functionName) {
    return "int " + functionName + "(bool patlat, int deger) {\n    if (patlat) {\n        "
           "throw std::runtime_error(\"Hata olustu\");\n    }\n    return deger;\n}\n";
}

std::string tryCatchBlock(
    const std::string& functionName, bool throwsFlag, int value, const std::string& caughtLabel) {
    return "try {\n    std::cout << " + functionName + "(" + (throwsFlag ? "true" : "false") +
           ", " + std::to_string(value) + ");\n} catch (const std::exception& e) {\n    "
           "std::cout << \"" + caughtLabel + "\";\n}\n";
}

}  // namespace

std::string_view TryCatchPredictGenerator::id() const noexcept {
    return "TryCatchPredictGenerator";
}

int TryCatchPredictGenerator::topicId() const noexcept {
    return 99;
}

std::optional<GeneratedQuestion> TryCatchPredictGenerator::generate(
    std::mt19937_64& randomEngine, GenerationStage stage) const {
    std::uniform_int_distribution<std::size_t> nameDist(0, kFunctionNames.size() - 1);
    std::uniform_int_distribution<int> flagDist(0, 1);

    const std::string functionName = kFunctionNames[nameDist(randomEngine)];
    const ParameterDomain valueDomain =
        stage == GenerationStage::Normal ? kValueDomain : kValueDomain.expanded();

    const bool twoBlockShape = stage == GenerationStage::StructuralVariation;

    GeneratedQuestion result;
    result.question.id = 0;
    result.question.topicId = 99;
    result.question.type = QuestionType::PredictOutput;
    result.question.difficulty = Difficulty::Medium;
    result.question.baseXp = 20;

    if (twoBlockShape) {
        const bool flag1 = flagDist(randomEngine) == 1;
        const bool flag2 = flagDist(randomEngine) == 1;
        const int value1 = valueDomain.draw(randomEngine);
        const int value2 = valueDomain.draw(randomEngine);

        const std::string part1 = flag1 ? "Yakalandi1" : std::to_string(value1);
        const std::string part2 = flag2 ? "Yakalandi2" : std::to_string(value2);
        const std::string answer = part1 + part2;

        result.question.prompt = functionDeclaration(functionName) + "\n" +
                                  tryCatchBlock(functionName, flag1, value1, "Yakalandi1") + "\n" +
                                  tryCatchBlock(functionName, flag2, value2, "Yakalandi2") +
                                  "\nYukarıdaki kodun ekran çıktısı nedir?";
        result.question.acceptedAnswers = {answer};
        result.question.explanation = "İlk try/catch " + (flag1 ? std::string("istisna fırlatıldığı "
                                       "için \"Yakalandi1\" yazdırır") : std::string("değeri (" +
                                       std::to_string(value1) + ") doğrudan yazdırır")) +
                                       "; ikincisi bağımsız olarak " +
                                       (flag2 ? std::string("istisna fırlatıldığı için "
                                                             "\"Yakalandi2\" yazdırır")
                                              : std::string("değeri (" + std::to_string(value2) +
                                                             ") doğrudan yazdırır")) +
                                       ". Sonuç: " + answer + ".";

        result.exactSignature = "generator=TryCatchPredictGenerator;var=" + functionName +
                                 ";shape=two;flag1=" + (flag1 ? "1" : "0") + ";value1=" +
                                 std::to_string(value1) + ";flag2=" + (flag2 ? "1" : "0") +
                                 ";value2=" + std::to_string(value2);
        result.semanticSignature = "generator=TryCatchPredictGenerator;shape=two;flag1=" +
                                    std::string(flag1 ? "1" : "0") + ";value1=" +
                                    std::to_string(value1) + ";flag2=" +
                                    std::string(flag2 ? "1" : "0") + ";value2=" +
                                    std::to_string(value2);
    } else {
        const bool throwsFlag = flagDist(randomEngine) == 1;
        const int value = valueDomain.draw(randomEngine);
        const std::string answer = throwsFlag ? "Yakalandi" : std::to_string(value);

        result.question.prompt = functionDeclaration(functionName) + "\n" +
                                  tryCatchBlock(functionName, throwsFlag, value, "Yakalandi") +
                                  "\nYukarıdaki kodun ekran çıktısı nedir?";
        result.question.acceptedAnswers = {answer};
        result.question.explanation =
            throwsFlag ? "patlat true olduğu için fonksiyon istisna fırlatır ve catch bloğu "
                         "\"Yakalandi\" yazdırır."
                       : "patlat false olduğu için fonksiyon " + std::to_string(value) +
                             " değerini döndürür ve doğrudan yazdırılır.";

        result.exactSignature = "generator=TryCatchPredictGenerator;var=" + functionName +
                                 ";shape=one;throws=" + (throwsFlag ? "1" : "0") + ";value=" +
                                 std::to_string(value);
        result.semanticSignature = "generator=TryCatchPredictGenerator;shape=one;throws=" +
                                    std::string(throwsFlag ? "1" : "0") + ";value=" +
                                    std::to_string(value);
    }

    result.generatorId = std::string(id());
    result.exactHash = fnv1a64(result.exactSignature);
    result.semanticHash = fnv1a64(result.semanticSignature);

    return result;
}
