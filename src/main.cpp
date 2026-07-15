#include <iostream>
#include <random>

#include "QuestionGenerationEngine.h"
#include "generators/IntArithmeticPredictGenerator.h"

int main() {
    IntArithmeticPredictGenerator generator;

    std::cout << "Generator id: " << generator.id() << " (beklenen: IntArithmeticPredictGenerator)\n";

    QuestionGenerationEngine genEngine;

    std::mt19937_64 engineA{123456789ULL};
    const auto first = genEngine.generateUnique(generator, engineA);
    std::cout << "Ilk uretim basarili mi: " << (first.has_value() ? "EVET (OK)" : "HATA") << '\n';
    std::cout << "Soru tipi PredictOutput mi: "
              << (first->question.type == QuestionType::PredictOutput ? "EVET (OK)" : "HATA") << '\n';
    std::cout << "Kabul edilen cevap sayisi 1 mi: "
              << (first->question.acceptedAnswers.size() == 1 ? "EVET (OK)" : "HATA") << '\n';

    // A fresh engine with the SAME seed reproduces generator.generate()'s first draw
    // exactly, which is `first` itself -- already recorded in genEngine's history.
    // generateUnique must reject that repeat and advance to the engine's next
    // random state, producing a genuinely different question.
    std::mt19937_64 engineB{123456789ULL};
    const auto second = genEngine.generateUnique(generator, engineB);
    std::cout << "Ikinci uretim basarili mi: " << (second.has_value() ? "EVET (OK)" : "HATA") << '\n';
    std::cout << "Tekrar eden aday reddedilip farkli soru mu uretildi: "
              << (second.has_value() && second->exactSignature != first->exactSignature ? "EVET (OK)"
                                                                                          : "HATA")
              << '\n';

    return 0;
}
