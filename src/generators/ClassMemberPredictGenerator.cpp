#include "generators/ClassMemberPredictGenerator.h"

#include <array>
#include <cstddef>
#include <string>

#include "FnvHash.h"
#include "ParameterDomain.h"

namespace {

constexpr std::array<const char*, 5> kClassNames = {
    "Kutu", "Ogr", "Nokta", "Veri", "Ornek",
};
constexpr std::array<const char*, 5> kMemberNames = {
    "deger", "sayi", "x", "veri", "miktar",
};
constexpr std::array<const char*, 5> kInstanceNames = {
    "a", "obj", "nesne", "k", "n",
};

constexpr ParameterDomain kValueDomain{1, 100};

}  // namespace

std::string_view ClassMemberPredictGenerator::id() const noexcept {
    return "ClassMemberPredictGenerator";
}

int ClassMemberPredictGenerator::topicId() const noexcept {
    return 64;
}

std::optional<GeneratedQuestion> ClassMemberPredictGenerator::generate(
    std::mt19937_64& randomEngine, GenerationStage stage) const {
    std::uniform_int_distribution<std::size_t> classDist(0, kClassNames.size() - 1);
    std::uniform_int_distribution<std::size_t> memberDist(0, kMemberNames.size() - 1);
    std::uniform_int_distribution<std::size_t> instanceDist(0, kInstanceNames.size() - 1);

    const std::string className = kClassNames[classDist(randomEngine)];
    const std::string memberName = kMemberNames[memberDist(randomEngine)];
    const std::size_t instanceIndexA = instanceDist(randomEngine);
    // The second instance's name must differ from the first, or the
    // two-instance shape would redeclare the same identifier twice.
    const std::size_t instanceIndexB = (instanceIndexA + 1) % kInstanceNames.size();
    const std::string instanceNameA = kInstanceNames[instanceIndexA];
    const std::string instanceNameB = kInstanceNames[instanceIndexB];

    const bool twoInstanceShape = stage == GenerationStage::StructuralVariation;

    const ParameterDomain valueDomain =
        stage == GenerationStage::Normal ? kValueDomain : kValueDomain.expanded();

    const std::string classDeclaration =
        "class " + className + " {\npublic:\n    int " + memberName + ";\n};\n";

    GeneratedQuestion result;
    result.question.id = 0;
    result.question.topicId = 64;
    result.question.type = QuestionType::PredictOutput;
    result.question.difficulty = Difficulty::Medium;
    result.question.baseXp = 20;

    if (twoInstanceShape) {
        const int valueA = valueDomain.draw(randomEngine);
        const int valueB = valueDomain.draw(randomEngine);

        result.question.prompt = classDeclaration + "\n" + className + " " + instanceNameA +
                                  ";\n" + instanceNameA + "." + memberName + " = " +
                                  std::to_string(valueA) + ";\n" + className + " " + instanceNameB +
                                  ";\n" + instanceNameB + "." + memberName + " = " +
                                  std::to_string(valueB) + ";\nstd::cout << " + instanceNameB + "." +
                                  memberName + ";\nYukarıdaki kodun ekran çıktısı nedir?";
        result.question.acceptedAnswers = {std::to_string(valueB)};
        result.question.explanation = instanceNameA + " ve " + instanceNameB +
                                       " birbirinden bağımsız nesnelerdir; " + instanceNameB + "." +
                                       memberName + " kendi ayarlanan değeri olan " +
                                       std::to_string(valueB) + "'i taşır.";

        result.exactSignature = "generator=ClassMemberPredictGenerator;var=" + className + ":" +
                                 memberName + ":" + instanceNameA + ":" + instanceNameB +
                                 ";shape=two;valueA=" + std::to_string(valueA) + ";valueB=" +
                                 std::to_string(valueB);
        result.semanticSignature = "generator=ClassMemberPredictGenerator;shape=two;valueA=" +
                                    std::to_string(valueA) + ";valueB=" + std::to_string(valueB);
    } else {
        const int value = valueDomain.draw(randomEngine);

        result.question.prompt = classDeclaration + "\n" + className + " " + instanceNameA +
                                  ";\n" + instanceNameA + "." + memberName + " = " +
                                  std::to_string(value) + ";\nstd::cout << " + instanceNameA + "." +
                                  memberName + ";\nYukarıdaki kodun ekran çıktısı nedir?";
        result.question.acceptedAnswers = {std::to_string(value)};
        result.question.explanation = instanceNameA + "." + memberName + " değişkenine atanan " +
                                       std::to_string(value) + " değeri doğrudan yazdırılır.";

        result.exactSignature = "generator=ClassMemberPredictGenerator;var=" + className + ":" +
                                 memberName + ":" + instanceNameA + ";shape=one;value=" +
                                 std::to_string(value);
        result.semanticSignature = "generator=ClassMemberPredictGenerator;shape=one;value=" +
                                    std::to_string(value);
    }

    result.generatorId = std::string(id());
    result.exactHash = fnv1a64(result.exactSignature);
    result.semanticHash = fnv1a64(result.semanticSignature);

    return result;
}
