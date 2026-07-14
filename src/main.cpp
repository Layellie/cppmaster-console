#include <iostream>

#include "QuestionManager.h"
#include "QuizEngine.h"

int main() {
    QuestionManager questions;
    QuizEngine engine;

    const auto topic1Questions = questions.questionsForTopic(1);

    // Q1 (id=1, MultipleChoice, correct="b"): try correct, wrong, and case-insensitive.
    const auto& q1 = topic1Questions.at(0);
    std::cout << "Q1 dogru cevap 'b': "
              << (engine.evaluate(q1, "b").correct ? "DOGRU (OK)" : "HATA") << '\n';
    std::cout << "Q1 dogru cevap 'B' (buyuk harf): "
              << (engine.evaluate(q1, "B").correct ? "DOGRU (OK)" : "HATA") << '\n';
    std::cout << "Q1 yanlis cevap 'a': "
              << (!engine.evaluate(q1, "a").correct ? "YANLIS (OK)" : "HATA") << '\n';
    std::cout << "Q1 XP (dogru): " << engine.evaluate(q1, "b").xpAwarded << " (beklenen: 10)\n";
    std::cout << "Q1 XP (yanlis): " << engine.evaluate(q1, "a").xpAwarded << " (beklenen: 0)\n";
    std::cout << "Q1 dogru cevap gosterimi: " << engine.evaluate(q1, "a").correctAnswerDisplay
              << " (beklenen: B) cout)\n";

    // Q3 (id=3, TrueFalse, correct="2"): try correct digit and wrong digit.
    const auto& q3 = topic1Questions.at(2);
    std::cout << "Q3 dogru cevap '2': "
              << (engine.evaluate(q3, "2").correct ? "DOGRU (OK)" : "HATA") << '\n';
    std::cout << "Q3 yanlis cevap '1': "
              << (!engine.evaluate(q3, "1").correct ? "YANLIS (OK)" : "HATA") << '\n';

    // Q5 (id=5, FillBlank, correct="cout"): try with whitespace and different case.
    const auto& q5 = topic1Questions.at(4);
    std::cout << "Q5 dogru cevap '  COUT  ' (bosluklu, buyuk harf): "
              << (engine.evaluate(q5, "  COUT  ").correct ? "DOGRU (OK)" : "HATA") << '\n';
    std::cout << "Q5 yanlis cevap 'cin': "
              << (!engine.evaluate(q5, "cin").correct ? "YANLIS (OK)" : "HATA") << '\n';

    return 0;
}
