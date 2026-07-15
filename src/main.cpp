#include <iostream>
#include <random>

#include "QuestionGenerationEngine.h"
#include "generators/BoolOutputPredictGenerator.h"

int main() {
    BoolOutputPredictGenerator generator;
    std::cout << "Generator id: " << generator.id() << " (beklenen: BoolOutputPredictGenerator)\n";

    QuestionGenerationEngine genEngine;
    std::mt19937_64 engine{42ULL};

    const auto first = genEngine.generateUnique(generator, engine);
    std::cout << "Ilk uretim basarili mi: " << (first.has_value() ? "EVET (OK)" : "HATA") << '\n';

    const auto second = genEngine.generateUnique(generator, engine);
    std::cout << "Ikinci uretim basarili mi (diger semantik deger kaldiysa): "
              << (second.has_value() ? "EVET (OK)" : "HATA") << '\n';
    if (second.has_value() && first.has_value()) {
        std::cout << "Ilk ve ikinci farkli semantik mi: "
                  << (second->semanticSignature != first->semanticSignature ? "EVET (OK)" : "HATA")
                  << '\n';
    }

    // Only 2 possible semantic variants exist for this generator (true->1, false->0).
    // Both are now recorded in genEngine's history, so a third attempt must be
    // exhausted -- this is a hard guarantee, not a probabilistic one, since every
    // possible draw from here on is one of the 2 already-seen semantic values.
    const auto third = genEngine.generateUnique(generator, engine);
    std::cout << "Ucuncu uretim tukendi mi (bos deger bekleniyor): "
              << (!third.has_value() ? "EVET (OK)" : "HATA") << '\n';

    return 0;
}
