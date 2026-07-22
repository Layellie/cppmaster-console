#include "generators/WhileLoopCountPredictGenerator.h"

#include <array>
#include <cstddef>
#include <string>

#include "FnvHash.h"
#include "ParameterDomain.h"

namespace {

constexpr std::array<const char*, 5> kVariableNames = {
    "deger", "sayi", "n", "x", "kalan",
};

constexpr ParameterDomain kStartDomain{1, 20};
constexpr ParameterDomain kDivisorDomain{2, 5};
constexpr ParameterDomain kLimitDomain{20, 200};

// Defense-in-depth cap: with the guards below (divisor forced to
// magnitude >= 2, multiply-stage start forced positive) neither loop can
// actually run unbounded, but this cap guarantees the generator itself
// can never hang even if a future edit weakens one of those guards.
constexpr int kMaxSimulatedIterations = 1000;

}  // namespace

std::string_view WhileLoopCountPredictGenerator::id() const noexcept {
    return "WhileLoopCountPredictGenerator";
}

int WhileLoopCountPredictGenerator::topicId() const noexcept {
    return 23;
}

std::optional<GeneratedQuestion> WhileLoopCountPredictGenerator::generate(
    std::mt19937_64& randomEngine, GenerationStage stage) const {
    std::uniform_int_distribution<std::size_t> nameDist(0, kVariableNames.size() - 1);
    const std::string variableName = kVariableNames[nameDist(randomEngine)];

    const bool doublingShape = stage == GenerationStage::StructuralVariation;

    GeneratedQuestion result;
    result.question.id = 0;
    result.question.topicId = 23;
    result.question.type = QuestionType::PredictOutput;
    result.question.difficulty = Difficulty::Medium;
    result.question.baseXp = 20;

    if (doublingShape) {
        const ParameterDomain startDomain = kStartDomain;  // kept modest; see guard below
        const ParameterDomain limitDomain = kLimitDomain;
        int start = startDomain.draw(randomEngine);
        if (start < 1) {
            start = 1;
        }
        const int limit = limitDomain.draw(randomEngine);

        int value = start;
        int count = 0;
        while (value < limit && count < kMaxSimulatedIterations) {
            value *= 2;
            ++count;
        }

        result.question.prompt = "int " + variableName + " = " + std::to_string(start) +
                                  ";\nint sayac = 0;\nwhile (" + variableName + " < " +
                                  std::to_string(limit) + ") {\n    " + variableName +
                                  " *= 2;\n    ++sayac;\n}\nstd::cout << sayac;\nYukarıdaki "
                                  "kodun ekran çıktısı nedir?";
        result.question.acceptedAnswers = {std::to_string(count)};
        result.question.explanation = variableName + ", " + std::to_string(start) +
                                       "'den başlayıp " + std::to_string(limit) +
                                       "'e ulaşana kadar ikiye katlanır; bu " + std::to_string(count) +
                                       " adımda gerçekleşir.";

        result.generatorId = std::string(id());
        result.exactSignature = "generator=WhileLoopCountPredictGenerator;var=" + variableName +
                                 ";shape=double;start=" + std::to_string(start) + ";limit=" +
                                 std::to_string(limit);
        result.semanticSignature = "generator=WhileLoopCountPredictGenerator;shape=double;start=" +
                                    std::to_string(start) + ";limit=" + std::to_string(limit);
    } else {
        const ParameterDomain startDomain =
            stage == GenerationStage::Normal ? kStartDomain : kStartDomain.expanded();
        int start = startDomain.draw(randomEngine);
        if (start < 1) {
            start = 1;
        }
        int divisor = kDivisorDomain.draw(randomEngine);
        if (divisor == 0 || divisor == 1) {
            divisor = 2;
        }

        int value = start;
        int count = 0;
        while (value > 1 && count < kMaxSimulatedIterations) {
            value /= divisor;
            ++count;
        }

        result.question.prompt = "int " + variableName + " = " + std::to_string(start) +
                                  ";\nint sayac = 0;\nwhile (" + variableName + " > 1) {\n    " +
                                  variableName + " /= " + std::to_string(divisor) +
                                  ";\n    ++sayac;\n}\nstd::cout << sayac;\nYukarıdaki kodun ekran "
                                  "çıktısı nedir?";
        result.question.acceptedAnswers = {std::to_string(count)};
        result.question.explanation = variableName + ", " + std::to_string(start) + "'den " +
                                       std::to_string(divisor) + "'e bölüne bölüne 1'e (veya "
                                       "altına) iner; bu " + std::to_string(count) + " adımda "
                                       "gerçekleşir.";

        result.generatorId = std::string(id());
        result.exactSignature = "generator=WhileLoopCountPredictGenerator;var=" + variableName +
                                 ";shape=divide;start=" + std::to_string(start) + ";divisor=" +
                                 std::to_string(divisor);
        result.semanticSignature = "generator=WhileLoopCountPredictGenerator;shape=divide;start=" +
                                    std::to_string(start) + ";divisor=" + std::to_string(divisor);
    }

    result.exactHash = fnv1a64(result.exactSignature);
    result.semanticHash = fnv1a64(result.semanticSignature);

    return result;
}
