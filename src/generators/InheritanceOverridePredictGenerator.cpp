#include "generators/InheritanceOverridePredictGenerator.h"

#include <array>
#include <cstddef>
#include <string>

#include "FnvHash.h"

namespace {

// Fixed base/derived class names and method name per the generator's design
// brief — only the instance/pointer identifiers and the printed text vary.
constexpr const char* kBaseClassName = "Taban";
constexpr const char* kDerivedClassName = "Turetilmis";
constexpr const char* kMethodName = "mesaj";

constexpr std::array<const char*, 5> kInstanceNames = {
    "d", "obj", "nesne", "t", "x",
};
constexpr std::array<const char*, 5> kPointerNames = {
    "b", "ptr", "taban", "p", "tb",
};

constexpr std::array<const char*, 5> kBaseTexts = {
    "Taban mesaji", "Genel bilgi", "Varsayilan deger", "Standart yanit", "Ana metin",
};
constexpr std::array<const char*, 5> kDerivedTexts = {
    "Turetilmis mesaji", "Ozel bilgi", "Yeni deger", "Guncel yanit", "Alt metin",
};

}  // namespace

std::string_view InheritanceOverridePredictGenerator::id() const noexcept {
    return "InheritanceOverridePredictGenerator";
}

int InheritanceOverridePredictGenerator::topicId() const noexcept {
    return 69;
}

std::optional<GeneratedQuestion> InheritanceOverridePredictGenerator::generate(
    std::mt19937_64& randomEngine, GenerationStage stage) const {
    std::uniform_int_distribution<std::size_t> instanceDist(0, kInstanceNames.size() - 1);
    std::uniform_int_distribution<std::size_t> pointerDist(0, kPointerNames.size() - 1);
    std::uniform_int_distribution<std::size_t> baseTextDist(0, kBaseTexts.size() - 1);
    std::uniform_int_distribution<std::size_t> derivedTextDist(0, kDerivedTexts.size() - 1);

    const std::string instanceName = kInstanceNames[instanceDist(randomEngine)];
    const std::string pointerName = kPointerNames[pointerDist(randomEngine)];
    const std::string baseText = kBaseTexts[baseTextDist(randomEngine)];
    const std::string derivedText = kDerivedTexts[derivedTextDist(randomEngine)];

    const std::string classDeclaration =
        std::string("class ") + kBaseClassName + " {\npublic:\n    std::string " + kMethodName +
        "() { return \"" + baseText + "\"; }\n};\nclass " + kDerivedClassName + " : public " +
        kBaseClassName + " {\npublic:\n    std::string " + kMethodName + "() { return \"" +
        derivedText + "\"; }\n};\n";

    const bool basePointerShape = stage == GenerationStage::StructuralVariation;

    GeneratedQuestion result;
    result.question.id = 0;
    result.question.topicId = 69;
    result.question.type = QuestionType::PredictOutput;
    result.question.difficulty = Difficulty::Medium;
    result.question.baseXp = 20;

    if (basePointerShape) {
        // mesaj() is not declared virtual, so a call through a Taban*
        // resolves at compile time using the pointer's static type — it
        // calls Taban::mesaj() even though the pointer points at a
        // Turetilmis object. Verified via standalone compilation.
        result.question.prompt = classDeclaration + "\n" + kDerivedClassName + " " + instanceName +
                                  ";\n" + kBaseClassName + "* " + pointerName + " = &" +
                                  instanceName + ";\nstd::cout << " + pointerName + "->" +
                                  kMethodName + "();\nYukarıdaki kodun ekran çıktısı nedir?";
        result.question.acceptedAnswers = {baseText};
        result.question.explanation = kMethodName + std::string("() sanal (virtual) olarak "
                                       "tanımlanmadığı için, ") + pointerName + " (" +
                                       kBaseClassName + "*) üzerinden yapılan çağrı statik türe göre "
                                       "çözülür ve " + kBaseClassName + "::" + kMethodName +
                                       "() çalışır: \"" + baseText + "\".";

        result.exactSignature = "generator=InheritanceOverridePredictGenerator;var=" +
                                 instanceName + ":" + pointerName + ";shape=basePointer;baseText=" +
                                 baseText + ";derivedText=" + derivedText;
        result.semanticSignature =
            "generator=InheritanceOverridePredictGenerator;shape=basePointer;baseText=" + baseText +
            ";derivedText=" + derivedText;
    } else {
        result.question.prompt = classDeclaration + "\n" + kDerivedClassName + " " + instanceName +
                                  ";\nstd::cout << " + instanceName + "." + kMethodName +
                                  "();\nYukarıdaki kodun ekran çıktısı nedir?";
        result.question.acceptedAnswers = {derivedText};
        result.question.explanation = instanceName + " değişkeni doğrudan " + kDerivedClassName +
                                       " türünde olduğu için, " + kDerivedClassName + "::" +
                                       kMethodName + "() çağrılır: \"" + derivedText + "\".";

        result.exactSignature = "generator=InheritanceOverridePredictGenerator;var=" +
                                 instanceName + ";shape=direct;baseText=" + baseText +
                                 ";derivedText=" + derivedText;
        result.semanticSignature =
            "generator=InheritanceOverridePredictGenerator;shape=direct;baseText=" + baseText +
            ";derivedText=" + derivedText;
    }

    result.generatorId = std::string(id());
    result.exactHash = fnv1a64(result.exactSignature);
    result.semanticHash = fnv1a64(result.semanticSignature);

    return result;
}
