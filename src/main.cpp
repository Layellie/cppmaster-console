#include <iostream>

#include "QuestionManager.h"

int main() {
    QuestionManager questions;

    int total = 0;
    for (int topicId = 1; topicId <= 10; ++topicId) {
        const auto topicQuestions = questions.questionsForTopic(topicId);
        std::cout << "Konu " << topicId << ": " << topicQuestions.size()
                  << " soru (beklenen: 6)\n";
        total += static_cast<int>(topicQuestions.size());
    }
    std::cout << "Toplam soru: " << total << " (beklenen: 60)\n";

    const auto emptyTopic = questions.questionsForTopic(11);
    std::cout << "Konu 11 soru sayisi: " << emptyTopic.size() << " (beklenen: 0)\n";

    return 0;
}
