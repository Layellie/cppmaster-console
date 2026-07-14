#include <iostream>

#include "QuestionManager.h"

int main() {
    QuestionManager questions;

    int total = 0;
    for (int topicId = 1; topicId <= 10; ++topicId) {
        total += static_cast<int>(questions.questionsForTopic(topicId).size());
    }
    std::cout << "Toplam soru sayisi: " << total << " (beklenen: 72)\n";

    std::cout << "Konu 1 soru sayisi: " << questions.questionsForTopic(1).size()
              << " (beklenen: 8)\n";
    std::cout << "Konu 2 soru sayisi: " << questions.questionsForTopic(2).size()
              << " (beklenen: 6, degismedi)\n";
    std::cout << "Konu 4 soru sayisi: " << questions.questionsForTopic(4).size()
              << " (beklenen: 9)\n";
    std::cout << "Konu 6 soru sayisi: " << questions.questionsForTopic(6).size()
              << " (beklenen: 9)\n";
    std::cout << "Konu 7 soru sayisi: " << questions.questionsForTopic(7).size()
              << " (beklenen: 7)\n";
    std::cout << "Konu 8 soru sayisi: " << questions.questionsForTopic(8).size()
              << " (beklenen: 7)\n";
    std::cout << "Konu 9 soru sayisi: " << questions.questionsForTopic(9).size()
              << " (beklenen: 7)\n";
    std::cout << "Konu 10 soru sayisi: " << questions.questionsForTopic(10).size()
              << " (beklenen: 7)\n";

    return 0;
}
