#include "QuestionContent.h"

#include "Question.h"

void appendSection10Questions(std::vector<Question>& questions) {
    // Topic 91: sort()
    questions.push_back(Question{
        .id = 2393, .topicId = 91,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::sort(first, last)'ın varsayılan sıralama düzeni nedir?",
        .options = {"Artan (küçükten büyüğe)", "Azalan (büyükten küçüğe)", "Ekleme sırası korunur", "Rastgele"},
        .acceptedAnswers = {"a"},
        .explanation = "std::sort varsayılan olarak artan sırada sıralar.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2394, .topicId = 91,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::vector<int> v = {5, 2, 8, 1};\nstd::sort(v.begin(), v.end());\nfor (int x : v) { std::cout << x; }\nEkran çıktısı nedir?",
        .options = {"5281", "1258", "8521", "Derleme hatası"},
        .acceptedAnswers = {"b"},
        .explanation = "Artan sıralama: 1,2,5,8.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2395, .topicId = 91,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "Azalan (büyükten küçüğe) sıralama yapmak için std::sort'a ne verilmelidir?",
        .options = {"Hiçbir şey, varsayılan davranıştır", "İkinci bir vektör", "Üçüncü argüman olarak std::greater<int>()", "std::reverse çağrısı, std::sort'tan önce"},
        .acceptedAnswers = {"c"},
        .explanation = "std::greater<int>() üçüncü argüman olarak verilir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2396, .topicId = 91,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {3, 1, 2};\nstd::sort(v.begin(), v.end(), std::greater<int>());\nfor (int x : v) { std::cout << x; }\nEkran çıktısı nedir?",
        .options = {"123", "213", "132", "321"},
        .acceptedAnswers = {"d"},
        .explanation = "std::greater<int>() ile azalan sıralama: 3,2,1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2397, .topicId = 91,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::sort, hangi başlığı (header) gerektirir?",
        .options = {"<algorithm>", "<numeric>", "<memory>", "<fstream>"},
        .acceptedAnswers = {"a"},
        .explanation = "std::sort <algorithm> başlığında tanımlıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2398, .topicId = 91,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {4, 4, 2, 2, 3};\nstd::sort(v.begin(), v.end());\nfor (int x : v) { std::cout << x; }\nEkran çıktısı nedir?",
        .options = {"44322", "22344", "23244", "Derleme hatası"},
        .acceptedAnswers = {"b"},
        .explanation = "Artan sıralama: 2,2,3,4,4.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2399, .topicId = 91,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::vector<int> v = {9, 1, 5};\nstd::sort(v.begin(), v.begin() + 2);\nfor (int x : v) { std::cout << x; }\nEkran çıktısı nedir?",
        .options = {"159", "915", "195", "519"},
        .acceptedAnswers = {"c"},
        .explanation = "Sadece ilk 2 eleman [9,1] sıralanır -> [1,9]; 3. eleman (5) değişmez: 1,9,5.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2400, .topicId = 91,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::vector<int> v = {6, 3, 9, 1};\nstd::sort(v.begin(), v.end());\nstd::sort(v.begin(), v.end(), std::greater<int>());\nfor (int x : v) { std::cout << x; }\nEkran çıktısı nedir?",
        .options = {"1369", "6391", "1963", "9631"},
        .acceptedAnswers = {"d"},
        .explanation = "İlk sort artan (1,3,6,9); ikinci sort azalan (9,6,3,1) yapar.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2401, .topicId = 91,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::sort, varsayılan olarak artan (küçükten büyüğe) sıralar.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2402, .topicId = 91,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::sort, azalan sıralama için otomatik olarak ters çevirir, ek argüman gerekmez.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: azalan sıralama için üçüncü argüman (örn. std::greater<int>()) gerekir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2403, .topicId = 91,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::sort için <algorithm> başlığı gereklidir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2404, .topicId = 91,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::sort, konteynerin sadece bir KISMINI (örneğin ilk N elemanını) sıralayacak şekilde de çağrılabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2405, .topicId = 91,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::sort, üçüncü bir argüman olarak özel bir karşılaştırma fonksiyonu/lambda kabul edebilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2406, .topicId = 91,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::sort çağrıldıktan sonra orijinal (sıralanmamış) sıra korunur, ayrı bir kopya oluşturulur.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: std::sort yerinde (in-place) çalışır, orijinal sıra kaybolur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2407, .topicId = 91,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir aralığı sıralayan STL algoritması std::_____ dir (İngilizce kelime).",
        .acceptedAnswers = {"sort"},
        .explanation = "std::sort kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2408, .topicId = 91,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::vector<int> v = {3, 1, 2};\nstd::sort(v.begin(), v.end());\nfor (int x : v) std::cout << x;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"123"},
        .explanation = "Artan sıralama: 1,2,3.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2409, .topicId = 91,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "Azalan sıralama için üçüncü argüman olarak std::_____<int>() verilir (İngilizce kelime).",
        .acceptedAnswers = {"greater"},
        .explanation = "std::greater<int>() kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2410, .topicId = 91,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::sort'un gerektirdiği başlık dosyası <_____> dir (İngilizce kelime).",
        .acceptedAnswers = {"algorithm"},
        .explanation = "<algorithm> başlığı gerekir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2411, .topicId = 91,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {7, 2, 5};\nstd::sort(v.begin(), v.end(), std::greater<int>());\nfor (int x : v) std::cout << x;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"752"},
        .explanation = "Azalan sıralama: 7,5,2.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2412, .topicId = 91,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::sort, varsayılan olarak operator_____ kullanarak karşılaştırma yapar (bir sembol).",
        .acceptedAnswers = {"<"},
        .explanation = "operator< kullanılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2413, .topicId = 91,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {8, 3, 5};\n_____\nfor (int x : v) { std::cout << x; }\nv'yi artan sırada sıralayan satırı yazın.",
        .acceptedAnswers = {"std::sort(v.begin(), v.end());"},
        .explanation = "std::sort varsayılan olarak artan sıralar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2414, .topicId = 91,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {8, 3, 5};\n_____\nfor (int x : v) { std::cout << x; }\nv'yi azalan sırada sıralayan satırı yazın.",
        .acceptedAnswers = {"std::sort(v.begin(), v.end(), std::greater<int>());"},
        .explanation = "std::greater<int>() ile azalan sıralama.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2415, .topicId = 91,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {10, 4, 7};\nstd::sort(v.begin(), v.end());\nfor (int x : v) { std::cout << x << \" \"; }\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"4 7 10 "},
        .explanation = "Artan sıralama: 4, 7, 10.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2416, .topicId = 91,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "std::vector<int> v = {5, 5, 1, 3, 1};\nstd::sort(v.begin(), v.end());\nfor (int x : v) { std::cout << x; }\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"11355"},
        .explanation = "Artan sıralama: 1,1,3,5,5.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2417, .topicId = 91,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::vector<int> v = {3, 1, 2};\nsort(v.begin(), v.end());\n\nBu kod derlenmez çünkü sort, std:: öneki olmadan (using namespace std olmadan) çağrılamaz; std::sort olarak nitelenmelidir. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::sort(v.begin(), v.end());"},
        .explanation = "std::sort öneki gereklidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2418, .topicId = 91,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::vector<int> v = {5, 2, 8};\nstd::sort(v.begin(), v.end());\nstd::cout << v;\n\nBu kod derlenmez çünkü std::vector<int> için operator<< tanımlı değildir; bir vektörü yazdırmak için elemanları TEK TEK (bir döngüyle) yazdırmak gerekir. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"for (int x : v) { std::cout << x; }"},
        .explanation = "vector'ün operator<< tanımı yoktur; döngüyle yazdırılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2419, .topicId = 91,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nstd::vector<int> v = {3, 1, 2}\nstd::sort(v.begin(), v.end());\n\nProgramcı v tanımının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"std::vector<int> v = {3, 1, 2};"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2420, .topicId = 91,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir vektörü sıralayıp yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"for (int x : v) { std::cout << x; }\n    return 0;\n}", "std::vector<int> v = {9, 3, 6};\n    std::sort(v.begin(), v.end());", "int main() {"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "main açılışı (3), tanım+sıralama (2), yazdır+kapanış (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2421, .topicId = 91,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir int vektörü tanımlayın (sırasız en az 3 değer); std::sort ile artan sırada sıralayın ve tüm elemanları ekrana yazdırın.",
        .acceptedAnswers = {"sort", "algorithm"},
        .explanation = "std::sort ile artan sıralama yapılır.",
        .baseXp = 40,
    });

    // Topic 92: reverse()
    questions.push_back(Question{
        .id = 2422, .topicId = 92,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::reverse(first, last) ne yapar?",
        .options = {"Aralığı sıralar", "Aralığın elemanlarının sırasını YERİNDE tersine çevirir", "Aralığın bir kopyasını oluşturur", "Aralıktaki en büyük elemanı bulur"},
        .acceptedAnswers = {"b"},
        .explanation = "std::reverse elemanları yerinde tersine çevirir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2423, .topicId = 92,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::vector<int> v = {1, 2, 3};\nstd::reverse(v.begin(), v.end());\nfor (int x : v) { std::cout << x; }\nEkran çıktısı nedir?",
        .options = {"123", "213", "321", "Derleme hatası"},
        .acceptedAnswers = {"c"},
        .explanation = "Tersine çevrilmiş hali: 3,2,1.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2424, .topicId = 92,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::reverse'ün dönüş türü nedir?",
        .options = {"int", "Yeni bir vektör", "bool", "void"},
        .acceptedAnswers = {"d"},
        .explanation = "std::reverse void döndürür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2425, .topicId = 92,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "auto sonuc = std::reverse(v.begin(), v.end());\nBu kod derlenir mi?",
        .options = {"Hayır, std::reverse void döndürür; bir değişkene atanamaz, derleme hatası oluşur", "Evet, sonuc yeni bir vektör olur", "Evet, sonuc bir bool olur", "Evet, sonuc bir iterator olur"},
        .acceptedAnswers = {"a"},
        .explanation = "void bir değişkene atanamaz.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2426, .topicId = 92,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {1, 2, 3, 4};\nstd::reverse(v.begin(), v.begin() + 2);\nfor (int x : v) { std::cout << x; }\nEkran çıktısı nedir?",
        .options = {"4321", "2134", "1234", "1243"},
        .acceptedAnswers = {"b"},
        .explanation = "Sadece ilk 2 eleman [1,2] tersine çevrilir -> [2,1]; kalan [3,4] değişmez.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2427, .topicId = 92,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::reverse, hangi başlığı gerektirir?",
        .options = {"<numeric>", "<memory>", "<algorithm>", "<fstream>"},
        .acceptedAnswers = {"c"},
        .explanation = "std::reverse <algorithm> başlığında tanımlıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2428, .topicId = 92,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::vector<int> v = {5, 3, 8};\nstd::sort(v.begin(), v.end());\nstd::reverse(v.begin(), v.end());\nfor (int x : v) { std::cout << x; }\nEkran çıktısı nedir?",
        .options = {"358", "583", "385", "853"},
        .acceptedAnswers = {"d"},
        .explanation = "sort artan (3,5,8) yapar; reverse bunu (8,5,3) yapar.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2429, .topicId = 92,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::string s = \"merhaba\";\nstd::reverse(s.begin(), s.end());\nstd::cout << s;\nBu kod derlenir mi ve çıktısı nedir?",
        .options = {"Evet, derlenir; çıktı \"abahrem\"dir", "Hayır, std::reverse sadece std::vector ile çalışır", "Evet, çıktı \"merhaba\" olarak kalır", "Evet ama çalışma zamanı hatası verir"},
        .acceptedAnswers = {"a"},
        .explanation = "std::reverse herhangi bir bidirectional iterator aralığıyla (std::string dahil) çalışır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2430, .topicId = 92,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::reverse, bir aralığın elemanlarının sırasını yerinde (in-place) tersine çevirir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2431, .topicId = 92,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::reverse, yeni bir konteyner oluşturup orijinali değiştirmeden bırakır.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: orijinal konteynerin kendisi değişir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2432, .topicId = 92,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::reverse'ün dönüş türü void'dir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2433, .topicId = 92,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::reverse, sadece std::vector ile çalışır, std::string ile çalışmaz.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: std::reverse std::string ile de çalışır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2434, .topicId = 92,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::reverse, bir konteynerin sadece bir KISMINI (örneğin ilk N elemanını) tersine çevirecek şekilde de çağrılabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2435, .topicId = 92,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::reverse'ün dönüş değerini bir değişkene atamak geçerli bir C++ kodudur.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: void bir değişkene atanamaz, derleme hatası oluşur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2436, .topicId = 92,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir aralığın elemanlarının sırasını yerinde tersine çeviren STL algoritması std::_____ dir (İngilizce kelime).",
        .acceptedAnswers = {"reverse"},
        .explanation = "std::reverse kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2437, .topicId = 92,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::vector<int> v = {4, 5, 6};\nstd::reverse(v.begin(), v.end());\nfor (int x : v) std::cout << x;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"654"},
        .explanation = "Tersine çevrilmiş hali: 6,5,4.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2438, .topicId = 92,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::reverse'ün dönüş türü _____ dir (İngilizce kelime).",
        .acceptedAnswers = {"void"},
        .explanation = "void döner.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2439, .topicId = 92,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::reverse, hangi başlığı (header) gerektirir (İngilizce kelime)?",
        .acceptedAnswers = {"algorithm"},
        .explanation = "<algorithm> başlığı gerekir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2440, .topicId = 92,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::string s = \"abc\";\nstd::reverse(s.begin(), s.end());\nstd::cout << s;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"cba"},
        .explanation = "Tersine çevrilmiş hali: cba.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2441, .topicId = 92,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::reverse çağrıldıktan sonra, orijinal konteynerin _____ değişir (Türkçe kelime, 'kendisi' anlamında).",
        .acceptedAnswers = {"kendisi"},
        .explanation = "Konteynerin kendisi değişir, kopya değil.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2442, .topicId = 92,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {7, 8, 9};\n_____\nfor (int x : v) { std::cout << x; }\nv'yi yerinde tersine çeviren satırı yazın.",
        .acceptedAnswers = {"std::reverse(v.begin(), v.end());"},
        .explanation = "std::reverse yerinde tersine çevirir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2443, .topicId = 92,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {1, 2, 3};\nstd::reverse(v.begin(), v.end());\n_____\nv'nin tersine çevrilmiş halini ekrana yazdıran döngüyü yazın.",
        .acceptedAnswers = {"for (int x : v) { std::cout << x; }"},
        .explanation = "range-for ile elemanlar yazdırılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2444, .topicId = 92,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {2, 4, 6};\nstd::reverse(v.begin(), v.end());\nfor (int x : v) { std::cout << x << \" \"; }\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"6 4 2 "},
        .explanation = "Tersine çevrilmiş hali: 6, 4, 2.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2445, .topicId = 92,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "std::vector<int> v = {1, 2, 3, 4, 5};\nstd::reverse(v.begin(), v.end());\nstd::reverse(v.begin(), v.end());\nfor (int x : v) { std::cout << x; }\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"12345"},
        .explanation = "İki kez tersine çevirmek orijinal sırayı geri getirir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2446, .topicId = 92,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::vector<int> v = {1, 2, 3};\nauto sonuc = std::reverse(v.begin(), v.end());\n\nBu kod derlenmez çünkü std::reverse void döndürür; dönüş değeri bir değişkene ATANAMAZ. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::reverse(v.begin(), v.end());"},
        .explanation = "void bir değişkene atanamaz.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2447, .topicId = 92,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::vector<int> v = {1, 2, 3};\nreverse(v.begin(), v.end());\n\nBu kod derlenmez çünkü reverse, std:: öneki olmadan (using namespace std olmadan) çağrılamaz. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::reverse(v.begin(), v.end());"},
        .explanation = "std::reverse öneki gereklidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2448, .topicId = 92,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nstd::vector<int> v = {1, 2, 3}\nstd::reverse(v.begin(), v.end());\n\nProgramcı v tanımının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"std::vector<int> v = {1, 2, 3};"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2449, .topicId = 92,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir vektörü tersine çevirip yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"for (int x : v) { std::cout << x; }\n    return 0;\n}", "std::vector<int> v = {2, 4, 6};\n    std::reverse(v.begin(), v.end());", "int main() {"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "main açılışı (3), tanım+tersine çevirme (2), yazdır+kapanış (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2450, .topicId = 92,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir int vektörü tanımlayın (en az 3 değer); std::reverse ile tersine çevirin ve tüm elemanları ekrana yazdırın.",
        .acceptedAnswers = {"reverse", "algorithm"},
        .explanation = "std::reverse ile elemanların sırası tersine çevrilir.",
        .baseXp = 40,
    });

    // Topic 93: find()
    questions.push_back(Question{
        .id = 2451, .topicId = 93,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::find(first, last, deger) ne döndürür?",
        .options = {"Bir bool", "Elemanların sayısı", "Bulunan elemanı gösteren bir iterator (ya da bulunamazsa last)", "Elemanın index'i (bir int)"},
        .acceptedAnswers = {"c"},
        .explanation = "std::find bir iterator döndürür.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2452, .topicId = 93,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::vector<int> v = {4, 7, 2};\nauto it = std::find(v.begin(), v.end(), 7);\nstd::cout << (it != v.end());\nEkran çıktısı nedir?",
        .options = {"7", "0", "Derleme hatası", "1"},
        .acceptedAnswers = {"d"},
        .explanation = "7 bulunduğundan it != v.end() true (1).",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2453, .topicId = 93,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::find, bir değer BULUNAMAZSA ne döndürür?",
        .options = {"last (genellikle konteynerin end()'i)", "nullptr", "-1", "Bir istisna (exception) fırlatır"},
        .acceptedAnswers = {"a"},
        .explanation = "Bulunamazsa last (end()) döndürülür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2454, .topicId = 93,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {4, 7, 2};\nauto it = std::find(v.begin(), v.end(), 100);\nstd::cout << (it == v.end());\nEkran çıktısı nedir?",
        .options = {"0", "1", "100", "Derleme hatası"},
        .acceptedAnswers = {"b"},
        .explanation = "100 bulunamadığından it == v.end() true (1).",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2455, .topicId = 93,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::find sonucunu it != v.end() ile kontrol ETMEDEN *it ile dereference etmek ne anlama gelir?",
        .options = {"Her zaman güvenlidir", "Derleme hatası oluşur", "Değer bulunamadıysa tanımsız davranıştır (undefined behavior)", "Otomatik olarak 0 döner"},
        .acceptedAnswers = {"c"},
        .explanation = "Kontrol edilmeden dereference etmek tanımsız davranıştır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2456, .topicId = 93,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {5, 5, 5};\nauto it = std::find(v.begin(), v.end(), 5);\nstd::cout << *it;\nEkran çıktısı nedir?",
        .options = {"3", "15", "555", "5"},
        .acceptedAnswers = {"d"},
        .explanation = "std::find ilk eşleşmeyi bulur; değeri 5'tir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2457, .topicId = 93,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::vector<int> v = {1, 2, 3, 2, 1};\nauto it = std::find(v.begin(), v.end(), 2);\nstd::cout << (it - v.begin());\nEkran çıktısı nedir?",
        .options = {"1", "3", "0", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "2'nin İLK geçtiği index 1'dir (0-indexed).",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2458, .topicId = 93,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::find, hangi başlığı gerektirir?",
        .options = {"<numeric>", "<algorithm>", "<memory>", "<fstream>"},
        .acceptedAnswers = {"b"},
        .explanation = "std::find <algorithm> başlığında tanımlıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2459, .topicId = 93,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::find, bir değeri bir aralıkta arar ve bulursa bir iterator döndürür.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2460, .topicId = 93,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::find, bulunamazsa bir istisna (exception) fırlatır.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: istisna fırlatmaz, last (end()) döndürür.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2461, .topicId = 93,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::find sonucunu end() ile karşılaştırmak, değerin bulunup bulunmadığını kontrol etmenin doğru yoludur.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2462, .topicId = 93,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::find, birden fazla eşleşme varsa SON eşleşmeyi döndürür.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: ilk eşleşmeyi döndürür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2463, .topicId = 93,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::find'ın sonucunu kontrol etmeden dereference etmek tanımsız davranışa yol açabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2464, .topicId = 93,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::find, elemanların sayısını değil, bir iterator döndürür.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2465, .topicId = 93,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir aralıkta bir değeri arayan STL algoritması std::_____ dir (İngilizce kelime).",
        .acceptedAnswers = {"find"},
        .explanation = "std::find kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2466, .topicId = 93,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::find bir değeri bulamazsa _____ döndürür (İngilizce kelime).",
        .acceptedAnswers = {"last"},
        .explanation = "last (genellikle end()) döndürülür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2467, .topicId = 93,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::find'ın bulup bulmadığını kontrol etmek için sonucu konteynerin _____ üye fonksiyonunun sonucuyla karşılaştırmak gerekir (İngilizce kelime).",
        .acceptedAnswers = {"end"},
        .explanation = "end() ile karşılaştırılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2468, .topicId = 93,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {9, 3, 6};\nauto it = std::find(v.begin(), v.end(), 3);\nstd::cout << *it;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"3"},
        .explanation = "Bulunan elemanın değeri 3'tür.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2469, .topicId = 93,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::find, hangi başlığı gerektirir (İngilizce kelime)?",
        .acceptedAnswers = {"algorithm"},
        .explanation = "<algorithm> başlığı gerekir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2470, .topicId = 93,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::find sonucunu kontrol etmeden dereference etmek _____ davranıştır (Türkçe iki kelime).",
        .acceptedAnswers = {"tanımsız davranış", "tanımsız"},
        .explanation = "Bu, tanımsız davranıştır (UB).",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2471, .topicId = 93,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {2, 5, 8};\n_____\nif (it != v.end()) { std::cout << *it; }\nv içinde 5 değerini arayan satırı yazın.",
        .acceptedAnswers = {"auto it = std::find(v.begin(), v.end(), 5);"},
        .explanation = "std::find ile arama yapılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2472, .topicId = 93,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {2, 5, 8};\nauto it = std::find(v.begin(), v.end(), 100);\n_____\nit'nin bulunup bulunmadığını kontrol eden if satırını yazın.",
        .acceptedAnswers = {"if (it != v.end()) {"},
        .explanation = "end() ile karşılaştırılarak kontrol edilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2473, .topicId = 93,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {6, 1, 9};\nauto it = std::find(v.begin(), v.end(), 1);\nstd::cout << (it != v.end());\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"1"},
        .explanation = "1 bulunduğundan sonuç true (1).",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2474, .topicId = 93,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "std::vector<int> v = {3, 6, 9};\nauto it = std::find(v.begin(), v.end(), 100);\nif (it == v.end()) { std::cout << \"yok\"; } else { std::cout << *it; }\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"yok"},
        .explanation = "100 bulunamadığından \"yok\" yazdırılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2475, .topicId = 93,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::vector<int> v = {3, 6, 9};\nauto it = std::find(v.begin(), v.end(), 100);\nstd::cout << *it;\n\nBu kod derlenir AMA tanımsız davranışa (undefined behavior) yol açar çünkü 100 v içinde bulunamadığından it, v.end()'e eşittir; *it ile bu konum okunmaya çalışılıyor. Hatalı satırı, kontrol ekleyerek düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"if (it != v.end()) { std::cout << *it; }"},
        .explanation = "Kontrol eklenmelidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2476, .topicId = 93,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::vector<int> v = {3, 6, 9};\nauto it = find(v.begin(), v.end(), 6);\n\nBu kod derlenmez çünkü find, std:: öneki olmadan çağrılamaz. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"auto it = std::find(v.begin(), v.end(), 6);"},
        .explanation = "std::find öneki gereklidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2477, .topicId = 93,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nstd::vector<int> v = {3, 6, 9}\nauto it = std::find(v.begin(), v.end(), 6);\n\nProgramcı v tanımının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"std::vector<int> v = {3, 6, 9};"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2478, .topicId = 93,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir vektörde bir değer arayıp sonucunu yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"if (it != v.end()) { std::cout << *it; }\n    return 0;\n}", "std::vector<int> v = {4, 8, 12};\n    auto it = std::find(v.begin(), v.end(), 8);", "int main() {"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "main açılışı (3), tanım+arama (2), kontrol+kapanış (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2479, .topicId = 93,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir int vektörü tanımlayın (en az 3 değer); std::find ile bir değeri arayın ve bulunup bulunmadığını (varsa değerini) ekrana yazdırın.",
        .acceptedAnswers = {"find", "end"},
        .explanation = "std::find sonucu end() ile kontrol edilerek kullanılır.",
        .baseXp = 40,
    });

    // Topic 94: count()
    questions.push_back(Question{
        .id = 2480, .topicId = 94,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::count(first, last, deger) ne döndürür?",
        .options = {"Bir iterator", "Bir bool", "deger'in index'i", "deger'e eşit elemanların sayısı"},
        .acceptedAnswers = {"d"},
        .explanation = "std::count eşleşen eleman sayısını döndürür.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2481, .topicId = 94,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::vector<int> v = {2, 5, 2, 8};\nint sayi = std::count(v.begin(), v.end(), 2);\nstd::cout << sayi;\nEkran çıktısı nedir?",
        .options = {"2", "1", "4", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "2 değeri iki kez geçiyor.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2482, .topicId = 94,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::count, bir değer HİÇ bulunamazsa ne döndürür?",
        .options = {"-1", "0", "Bir istisna fırlatır", "nullptr"},
        .acceptedAnswers = {"b"},
        .explanation = "Eşleşme yoksa 0 döner.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2483, .topicId = 94,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {7, 7, 7};\nint sayi = std::count(v.begin(), v.end(), 7);\nstd::cout << sayi;\nEkran çıktısı nedir?",
        .options = {"1", "0", "3", "7"},
        .acceptedAnswers = {"c"},
        .explanation = "7 değeri üç kez geçiyor.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2484, .topicId = 94,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::count'un dönüş türü hakkında ne söylenebilir?",
        .options = {"Her zaman bir iterator döner", "Her zaman true/false döner", "Her zaman bir string döner", "Bir tam sayı (integral) türü döner"},
        .acceptedAnswers = {"d"},
        .explanation = "std::count bir tam sayı döner.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2485, .topicId = 94,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::count, hangi başlığı gerektirir?",
        .options = {"<algorithm>", "<numeric>", "<memory>", "<fstream>"},
        .acceptedAnswers = {"a"},
        .explanation = "std::count <algorithm> başlığında tanımlıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2486, .topicId = 94,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::vector<int> v = {1, 2, 1, 3, 1, 2};\nint sayi1 = std::count(v.begin(), v.end(), 1);\nint sayi2 = std::count(v.begin(), v.end(), 2);\nstd::cout << sayi1 << \" \" << sayi2;\nEkran çıktısı nedir?",
        .options = {"2 3", "3 2", "1 1", "Derleme hatası"},
        .acceptedAnswers = {"b"},
        .explanation = "1 üç kez, 2 iki kez geçiyor.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2487, .topicId = 94,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::string s = \"banana\";\nint sayi = std::count(s.begin(), s.end(), 'a');\nstd::cout << sayi;\nBu kod derlenir mi ve çıktısı nedir?",
        .options = {"Hayır, derleme hatası", "1", "3", "6"},
        .acceptedAnswers = {"c"},
        .explanation = "\"banana\" içinde 'a' harfi üç kez geçer.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2488, .topicId = 94,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::count, eşleşen elemanların SAYISINI döndürür.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2489, .topicId = 94,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::count, eşleşme yoksa bir istisna fırlatır.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: istisna fırlatmaz, 0 döner.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2490, .topicId = 94,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::count'un dönüş türü bir tam sayıdır (iterator ya da bool değil).",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2491, .topicId = 94,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::count, sadece std::vector<int> ile çalışır, std::string ile çalışmaz.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: std::count std::string ile de çalışır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2492, .topicId = 94,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::count, eşleşme sayısını bulmak için tüm aralığı gezer.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2493, .topicId = 94,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::count, ilk eşleşmeyi bulduğunda aramayı durdurur ve 1 döndürür.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: tüm aralığı gezip toplam eşleşme sayısını döndürür.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2494, .topicId = 94,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir aralıkta bir değerin kaç kez geçtiğini sayan STL algoritması std::_____ dir (İngilizce kelime).",
        .acceptedAnswers = {"count"},
        .explanation = "std::count kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2495, .topicId = 94,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::vector<int> v = {4, 4, 9};\nint sayi = std::count(v.begin(), v.end(), 4);\nstd::cout << sayi;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"2"},
        .explanation = "4 değeri iki kez geçiyor.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2496, .topicId = 94,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::count, eşleşme yoksa _____ döndürür (bir rakam).",
        .acceptedAnswers = {"0"},
        .explanation = "Eşleşme yoksa 0 döner.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2497, .topicId = 94,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::count, hangi başlığı gerektirir (İngilizce kelime)?",
        .acceptedAnswers = {"algorithm"},
        .explanation = "<algorithm> başlığı gerekir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2498, .topicId = 94,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {5, 5, 5, 5};\nint sayi = std::count(v.begin(), v.end(), 5);\nstd::cout << sayi;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"4"},
        .explanation = "5 değeri dört kez geçiyor.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2499, .topicId = 94,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::count'un dönüş türü bir _____ dir (Türkçe kelime, 'tam sayı' anlamında).",
        .acceptedAnswers = {"tam sayı", "tamsayi", "tam sayi"},
        .explanation = "Dönüş türü bir tam sayıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2500, .topicId = 94,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {6, 6, 3, 6};\n_____\nstd::cout << sayi;\nv içinde 6 değerinin kaç kez geçtiğini sayan satırı yazın.",
        .acceptedAnswers = {"int sayi = std::count(v.begin(), v.end(), 6);"},
        .explanation = "std::count ile sayım yapılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2501, .topicId = 94,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {1, 2, 3};\nint sayi = std::count(v.begin(), v.end(), 5);\n_____\nsayi'yi ekrana yazdıran satırı yazın.",
        .acceptedAnswers = {"std::cout << sayi;"},
        .explanation = "sayi değişkeni yazdırılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2502, .topicId = 94,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {8, 3, 8, 8};\nint sayi = std::count(v.begin(), v.end(), 8);\nstd::cout << sayi;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"3"},
        .explanation = "8 değeri üç kez geçiyor.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2503, .topicId = 94,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "std::vector<int> v = {2, 4, 6, 8};\nint ciftSayisi = std::count(v.begin(), v.end(), 4) + std::count(v.begin(), v.end(), 8);\nstd::cout << ciftSayisi;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"2"},
        .explanation = "count(4)=1, count(8)=1, toplam 2.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2504, .topicId = 94,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::vector<int> v = {3, 3, 5};\nbool bulundu = std::count(v.begin(), v.end(), 3);\n\nBu kod TEKNİK OLARAK derlenir (int, bool'a örtük dönüştürülür) ama YANILTICIDIR çünkü std::count bir SAYI döndürür, bool değil; doğrusu sonucu bir int değişkende tutmaktır. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"int sayi = std::count(v.begin(), v.end(), 3);"},
        .explanation = "std::count sonucu bir int'te tutulmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2505, .topicId = 94,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::vector<int> v = {3, 3, 5};\nint sayi = count(v.begin(), v.end(), 3);\n\nBu kod derlenmez çünkü count, std:: öneki olmadan çağrılamaz. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"int sayi = std::count(v.begin(), v.end(), 3);"},
        .explanation = "std::count öneki gereklidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2506, .topicId = 94,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nstd::vector<int> v = {3, 3, 5}\nint sayi = std::count(v.begin(), v.end(), 3);\n\nProgramcı v tanımının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"std::vector<int> v = {3, 3, 5};"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2507, .topicId = 94,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir vektörde bir değerin kaç kez geçtiğini sayıp yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"std::cout << sayi;\n    return 0;\n}", "std::vector<int> v = {2, 2, 5};\n    int sayi = std::count(v.begin(), v.end(), 2);", "int main() {"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "main açılışı (3), tanım+sayım (2), yazdır+kapanış (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2508, .topicId = 94,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir int vektörü tanımlayın (en az bir değer tekrar etmeli); std::count ile bir değerin kaç kez geçtiğini sayın ve ekrana yazdırın.",
        .acceptedAnswers = {"count", "algorithm"},
        .explanation = "std::count ile eşleşme sayısı bulunur.",
        .baseXp = 40,
    });
}
