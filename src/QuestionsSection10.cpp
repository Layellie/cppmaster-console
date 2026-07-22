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

    // Topic 95: min(), max() ve max_element()
    questions.push_back(Question{
        .id = 2509, .topicId = 95,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::max(a, b) ne döndürür?",
        .options = {"İki DEĞERDEN büyük olanı, doğrudan bir değer olarak", "Bir iterator", "Her zaman a'yı", "Her zaman b'yi"},
        .acceptedAnswers = {"a"},
        .explanation = "std::max iki değerden büyük olanı doğrudan döndürür.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2510, .topicId = 95,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::cout << std::max(3, 9);\nEkran çıktısı nedir?",
        .options = {"3", "9", "Derleme hatası", "12"},
        .acceptedAnswers = {"b"},
        .explanation = "9, 3'ten büyük olduğundan 9 döner.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2511, .topicId = 95,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::max_element(first, last) ne döndürür?",
        .options = {"Aralıktaki en büyük değeri, doğrudan", "Bir bool", "Aralıktaki en büyük elemanı gösteren bir ITERATOR", "Elemanların sayısı"},
        .acceptedAnswers = {"c"},
        .explanation = "std::max_element bir iterator döndürür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2512, .topicId = 95,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {4, 9, 2};\nauto it = std::max_element(v.begin(), v.end());\nstd::cout << it;\nBu kod derlenir mi?",
        .options = {"Evet, çıktı 9'dur", "Evet, çıktı bir adres olur", "Evet, çıktı 0 olur", "Hayır, vector iterator'ı için operator<< tanımlı değildir, derleme hatası oluşur"},
        .acceptedAnswers = {"d"},
        .explanation = "Iterator'ı dereference etmeden yazdırmak derleme hatasıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2513, .topicId = 95,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {4, 9, 2};\nauto it = std::max_element(v.begin(), v.end());\nstd::cout << *it;\nEkran çıktısı nedir?",
        .options = {"9", "4", "2", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "Dereference edilen değer en büyük elemandır: 9.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2514, .topicId = 95,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::min(a, b) ile std::min_element(first, last) arasındaki fark nedir?",
        .options = {"Aralarında fark yoktur", "std::min iki DEĞERİ karşılaştırıp birini döndürür; std::min_element bir ARALIKTAKİ en küçük elemanı gösteren bir ITERATOR döndürür", "std::min_element her zaman std::min'den daha hızlıdır", "std::min sadece int ile çalışır, std::min_element her türle çalışır"},
        .acceptedAnswers = {"b"},
        .explanation = "min değer döndürür, min_element iterator döndürür.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2515, .topicId = 95,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::vector<int> v = {3, 7, 1, 9, 4};\nauto it = std::min_element(v.begin(), v.end());\nstd::cout << *it;\nEkran çıktısı nedir?",
        .options = {"9", "3", "1", "4"},
        .acceptedAnswers = {"c"},
        .explanation = "En küçük eleman 1'dir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2516, .topicId = 95,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::cout << std::max(std::max(3, 7), std::max(2, 9));\nEkran çıktısı nedir?",
        .options = {"7", "3", "2", "9"},
        .acceptedAnswers = {"d"},
        .explanation = "max(3,7)=7, max(2,9)=9, max(7,9)=9.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2517, .topicId = 95,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::max(a, b), iki değerden büyük olanı doğrudan döndürür.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2518, .topicId = 95,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::max_element, bir aralıktaki en büyük DEĞERİ doğrudan döndürür, iterator değil.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: max_element bir iterator döndürür.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2519, .topicId = 95,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::max_element'in sonucunu * ile dereference etmeden yazdırmaya çalışmak bir derleme hatasıdır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2520, .topicId = 95,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::min_element, bir aralıktaki en küçük elemanı gösteren bir iterator döndürür.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2521, .topicId = 95,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::max ve std::min, sadece iki argüman alabilir, üç ya da daha fazla değer karşılaştırmak için iç içe (nested) çağrılabilirler.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2522, .topicId = 95,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::max_element, boş bir aralık üzerinde çağrılırsa nullptr döndürür.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: end() döndürür, nullptr değil.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2523, .topicId = 95,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "İki değerden büyük olanı doğrudan döndüren fonksiyon std::_____ dir (İngilizce kelime).",
        .acceptedAnswers = {"max"},
        .explanation = "std::max kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2524, .topicId = 95,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::cout << std::min(5, 2);\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"2"},
        .explanation = "2, 5'ten küçük olduğundan 2 döner.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2525, .topicId = 95,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "Bir aralıktaki en büyük elemanı gösteren bir ITERATOR döndüren fonksiyon std::_____ dir (İngilizce iki kelime, alt çizgiyle).",
        .acceptedAnswers = {"max_element"},
        .explanation = "std::max_element kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2526, .topicId = 95,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {6, 2, 8};\nauto it = std::max_element(v.begin(), v.end());\nstd::cout << *it;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"8"},
        .explanation = "En büyük eleman 8'dir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2527, .topicId = 95,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::max_element'in sonucuna gerçek DEĞERE erişmek için _____ operatörü kullanılmalıdır (bir sembol).",
        .acceptedAnswers = {"*"},
        .explanation = "Dereference operatörü (*) kullanılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2528, .topicId = 95,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "Bir aralıktaki en küçük elemanı gösteren bir iterator döndüren fonksiyon std::_____ dir (İngilizce iki kelime, alt çizgiyle).",
        .acceptedAnswers = {"min_element"},
        .explanation = "std::min_element kullanılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2529, .topicId = 95,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {5, 9, 2};\n_____\nstd::cout << *it;\nv'nin en büyük elemanını gösteren bir iterator tanımlayan satırı yazın.",
        .acceptedAnswers = {"auto it = std::max_element(v.begin(), v.end());"},
        .explanation = "std::max_element ile bir iterator elde edilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2530, .topicId = 95,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::cout << std::max(4, 8);\n_____\n7 ve 3'ten küçük olanı ekrana yazdıran satırı yazın.",
        .acceptedAnswers = {"std::cout << std::min(7, 3);"},
        .explanation = "std::min iki değerden küçük olanı döndürür.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2531, .topicId = 95,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {1, 8, 3};\nauto it = std::max_element(v.begin(), v.end());\nstd::cout << *it;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"8"},
        .explanation = "En büyük eleman 8'dir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2532, .topicId = 95,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "std::vector<int> v = {7, 2, 9, 4};\nauto en_kucuk = std::min_element(v.begin(), v.end());\nauto en_buyuk = std::max_element(v.begin(), v.end());\nstd::cout << *en_kucuk << \" \" << *en_buyuk;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"2 9"},
        .explanation = "En küçük 2, en büyük 9'dur.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2533, .topicId = 95,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::vector<int> v = {3, 7, 1};\nauto it = std::max_element(v.begin(), v.end());\nstd::cout << it;\n\nBu kod derlenmez çünkü it bir ITERATOR'dır ve vector iterator'ı için operator<< tanımlı değildir; gerçek değere erişmek için * ile dereference edilmelidir. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::cout << *it;"},
        .explanation = "Iterator dereference edilmelidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2534, .topicId = 95,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::vector<int> v = {3, 7, 1};\nint en_buyuk = std::max_element(v.begin(), v.end());\n\nBu kod derlenmez çünkü std::max_element bir ITERATOR döndürür, bir int DEĞİL; bir int değişkene doğrudan atanamaz. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"int en_buyuk = *std::max_element(v.begin(), v.end());"},
        .explanation = "Iterator dereference edilip int'e atanmalıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2535, .topicId = 95,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nstd::vector<int> v = {3, 7, 1}\nauto it = std::max_element(v.begin(), v.end());\n\nProgramcı v tanımının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"std::vector<int> v = {3, 7, 1};"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2536, .topicId = 95,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir vektörün en büyük elemanını bulup yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"std::cout << *it;\n    return 0;\n}", "std::vector<int> v = {5, 9, 2};\n    auto it = std::max_element(v.begin(), v.end());", "int main() {"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "main açılışı (3), tanım+bulma (2), yazdır+kapanış (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2537, .topicId = 95,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir int vektörü tanımlayın (en az 3 değer); std::max_element ile en büyük elemanı bulun ve dereference ederek ekrana yazdırın.",
        .acceptedAnswers = {"max_element", "algorithm"},
        .explanation = "max_element sonucu dereference edilerek kullanılır.",
        .baseXp = 40,
    });

    // Topic 96: accumulate()
    questions.push_back(Question{
        .id = 2538, .topicId = 96,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::accumulate(first, last, init) ne yapar?",
        .options = {"Bir aralığı sıralar", "Bir aralığı init'ten başlayarak TOPLAR", "Bir aralıktaki en büyük elemanı bulur", "Bir aralığı tersine çevirir"},
        .acceptedAnswers = {"b"},
        .explanation = "std::accumulate bir aralığı toplar.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2539, .topicId = 96,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::vector<int> v = {1, 2, 3};\nint toplam = std::accumulate(v.begin(), v.end(), 0);\nstd::cout << toplam;\nEkran çıktısı nedir?",
        .options = {"0", "3", "6", "Derleme hatası"},
        .acceptedAnswers = {"c"},
        .explanation = "1+2+3=6.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2540, .topicId = 96,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::accumulate, hangi başlığı gerektirir?",
        .options = {"<algorithm>", "<memory>", "<fstream>", "<numeric>"},
        .acceptedAnswers = {"d"},
        .explanation = "std::accumulate <numeric> başlığında tanımlıdır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2541, .topicId = 96,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::accumulate'in üçüncü argümanının (başlangıç değeri) TÜRÜ neyi etkiler?",
        .options = {"Toplama işleminin ÇALIŞMA TÜRÜNÜ (ve dolayısıyla ara sonuçların nasıl kırpılacağını)", "Sadece çıktının biçimini, sonucu etkilemez", "Hiçbir şeyi, her zaman double olarak hesaplanır", "Sadece konteynerin boyutunu"},
        .acceptedAnswers = {"a"},
        .explanation = "Başlangıç değerinin türü, toplama türünü belirler.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2542, .topicId = 96,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<double> v = {1.5, 2.5, 3.0};\nauto toplam = std::accumulate(v.begin(), v.end(), 0);\nstd::cout << toplam;\nEkran çıktısı nedir?",
        .options = {"7", "6", "7.0", "Derleme hatası"},
        .acceptedAnswers = {"b"},
        .explanation = "int başlangıç değeri (0), ara toplamları her adımda int'e kırpar: 6.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2543, .topicId = 96,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<double> v = {1.5, 2.5, 3.0};\nauto toplam = std::accumulate(v.begin(), v.end(), 0.0);\nstd::cout << toplam;\nEkran çıktısı nedir?",
        .options = {"6", "6.0", "7", "Derleme hatası"},
        .acceptedAnswers = {"c"},
        .explanation = "double başlangıç değeri (0.0) doğru toplamı verir: 7.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2544, .topicId = 96,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::vector<double> v = {2.5, 2.5};\nauto toplamYanlis = std::accumulate(v.begin(), v.end(), 0);\nauto toplamDogru = std::accumulate(v.begin(), v.end(), 0.0);\nstd::cout << toplamYanlis << \" \" << toplamDogru;\nEkran çıktısı nedir?",
        .options = {"5 5", "5 4", "4 4", "4 5"},
        .acceptedAnswers = {"d"},
        .explanation = "int başlangıçla: 0+2.5=2(kırpılır); 2+2.5=4(kırpılır). double başlangıçla: 0.0+2.5+2.5=5.0.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2545, .topicId = 96,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::vector<int> v = {1, 2, 3, 4};\nint carpim = std::accumulate(v.begin(), v.end(), 1, std::multiplies<int>());\nstd::cout << carpim;\nEkran çıktısı nedir?",
        .options = {"24", "10", "4", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "accumulate, dördüncü argüman olarak std::multiplies<int>() ile çarpma yapar: 1*1*2*3*4=24.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2546, .topicId = 96,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::accumulate, bir aralığı başlangıç değerinden başlayarak toplar.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2547, .topicId = 96,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::accumulate'in başlangıç değerinin türü, toplama sonucunu ETKİLEMEZ.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: başlangıç değerinin türü toplama sonucunu doğrudan etkiler.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2548, .topicId = 96,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::accumulate, <numeric> başlığını gerektirir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2549, .topicId = 96,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Bir double listesine int (0 gibi) başlangıç değeri vermek, her zaman doğru sonuç verir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: ara toplamlar int'e kırpılabilir, yanlış sonuç verebilir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2550, .topicId = 96,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::accumulate, dördüncü bir argüman olarak özel bir ikili işlem (örneğin çarpma) kabul edebilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2551, .topicId = 96,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::accumulate'in varsayılan işlemi çıkarmadır (subtraction).",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: varsayılan işlem toplamadır (addition).",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2552, .topicId = 96,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir aralığı toplayan STL algoritması std::_____ dir (İngilizce kelime).",
        .acceptedAnswers = {"accumulate"},
        .explanation = "std::accumulate kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2553, .topicId = 96,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::vector<int> v = {2, 3, 5};\nint toplam = std::accumulate(v.begin(), v.end(), 0);\nstd::cout << toplam;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"10"},
        .explanation = "2+3+5=10.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2554, .topicId = 96,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::accumulate'in gerektirdiği başlık dosyası <_____> dir (İngilizce kelime).",
        .acceptedAnswers = {"numeric"},
        .explanation = "<numeric> başlığı gerekir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2555, .topicId = 96,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::accumulate'in başlangıç değeri bir double listesi için _____ (İngilizce kelime, 'int' değil) olmalıdır ki sonuç kırpılmasın.",
        .acceptedAnswers = {"double"},
        .explanation = "double başlangıç değeri kullanılmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2556, .topicId = 96,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<double> v = {1.0, 1.0, 1.0};\nauto toplam = std::accumulate(v.begin(), v.end(), 0);\nstd::cout << toplam;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"3"},
        .explanation = "1.0+1.0+1.0=3 (tam sayı değerler olduğundan kırpılma sonucu etkilemez).",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2557, .topicId = 96,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::accumulate'in dördüncü argümanı, varsayılan toplama yerine özel bir _____ belirtir (Türkçe kelime, 'işlem' anlamında).",
        .acceptedAnswers = {"işlem"},
        .explanation = "Özel bir ikili işlem belirtilebilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2558, .topicId = 96,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {4, 5, 6};\n_____\nstd::cout << toplam;\nv'nin elemanlarını 0'dan başlayarak toplayan satırı yazın.",
        .acceptedAnswers = {"int toplam = std::accumulate(v.begin(), v.end(), 0);"},
        .explanation = "std::accumulate ile toplama yapılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2559, .topicId = 96,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<double> v = {1.1, 2.2};\n_____\nstd::cout << toplam;\nv'nin elemanlarını DOĞRU şekilde (double başlangıç değeriyle) toplayan satırı yazın.",
        .acceptedAnswers = {"auto toplam = std::accumulate(v.begin(), v.end(), 0.0);"},
        .explanation = "double başlangıç değeri doğru toplamı sağlar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2560, .topicId = 96,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {10, 20, 30};\nint toplam = std::accumulate(v.begin(), v.end(), 0);\nstd::cout << toplam;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"60"},
        .explanation = "10+20+30=60.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2561, .topicId = 96,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "std::vector<double> v = {0.5, 0.5, 0.5};\nauto toplamYanlis = std::accumulate(v.begin(), v.end(), 0);\nauto toplamDogru = std::accumulate(v.begin(), v.end(), 0.0);\nstd::cout << toplamYanlis << \" \" << toplamDogru;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"0 1.5"},
        .explanation = "int başlangıçla her adımda 0.5 kırpılıp 0 kalır, sonuç 0; double başlangıçla doğru toplam 1.5.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2562, .topicId = 96,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::vector<double> v = {1.5, 2.5, 3.0};\nauto toplam = std::accumulate(v.begin(), v.end(), 0);\nstd::cout << toplam;\n// Beklenen: 7 (dogru toplam)\n\nBu kod, DOĞRU toplamı (7) DEĞİL YANLIŞ bir sonucu (6) verir çünkü başlangıç değeri (0) bir int'tir ve ara toplamlar her adımda int'e kırpılır. Hatalı satırı, başlangıç değerini 0.0 yaparak düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"auto toplam = std::accumulate(v.begin(), v.end(), 0.0);"},
        .explanation = "double başlangıç değeri kırpılmayı önler.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2563, .topicId = 96,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::vector<int> v = {1, 2, 3};\nint toplam = accumulate(v.begin(), v.end(), 0);\n\nBu kod derlenmez çünkü accumulate, std:: öneki olmadan çağrılamaz. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"int toplam = std::accumulate(v.begin(), v.end(), 0);"},
        .explanation = "std::accumulate öneki gereklidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2564, .topicId = 96,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nstd::vector<int> v = {1, 2, 3}\nint toplam = std::accumulate(v.begin(), v.end(), 0);\n\nProgramcı v tanımının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"std::vector<int> v = {1, 2, 3};"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2565, .topicId = 96,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir vektörün elemanlarını toplayıp yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"std::cout << toplam;\n    return 0;\n}", "std::vector<int> v = {3, 4, 5};\n    int toplam = std::accumulate(v.begin(), v.end(), 0);", "int main() {"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "main açılışı (3), tanım+toplama (2), yazdır+kapanış (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2566, .topicId = 96,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir double vektörü tanımlayın (en az 3 değer); std::accumulate ile elemanları DOĞRU şekilde (uygun başlangıç değeriyle) toplayın ve ekrana yazdırın.",
        .acceptedAnswers = {"accumulate", "numeric"},
        .explanation = "double başlangıç değeriyle doğru toplam elde edilir.",
        .baseXp = 40,
    });

    // Topic 97: Dosyaya yazma
    questions.push_back(Question{
        .id = 2567, .topicId = 97,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::ofstream ne için kullanılır?",
        .options = {"Bir dosyayı silmek", "Bir dosyanın adını değiştirmek", "Bir dosyaya YAZMAK", "Bir dosyayı okumak"},
        .acceptedAnswers = {"c"},
        .explanation = "std::ofstream dosyaya yazmak için kullanılır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2568, .topicId = 97,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::ofstream dosya(\"ad.txt\");\nDosya zaten VARSA ne olur (VARSAYILAN davranış)?",
        .options = {"Yeni içerik dosyanın SONUNA eklenir", "Açma başarısız olur, hata verir", "Dosya yeniden adlandırılır", "Dosyanın mevcut içeriği SİLİNİR (truncate)"},
        .acceptedAnswers = {"d"},
        .explanation = "Varsayılan olarak dosya truncate edilir (içeriği silinir).",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2569, .topicId = 97,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "Var olan bir dosyanın SONUNA eklemek (dosyayı silmeden) için ne kullanılmalıdır?",
        .options = {"std::ofstream dosya(\"ad.txt\", std::ios::app);", "std::ofstream dosya(\"ad.txt\"); (varsayılan)", "std::ifstream dosya(\"ad.txt\");", "Bu C++'ta mümkün değildir"},
        .acceptedAnswers = {"a"},
        .explanation = "std::ios::app modu sonuna ekleme yapar.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2570, .topicId = 97,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "Bir dosyaya yazmadan ÖNCE ne kontrol edilmelidir?",
        .options = {"Dosyanın boyutu", "dosya.is_open() (dosyanın gerçekten açılıp açılamadığı)", "Dosyanın oluşturulma tarihi", "Hiçbir şey, C++ otomatik kontrol eder"},
        .acceptedAnswers = {"b"},
        .explanation = "is_open() ile açılıp açılmadığı kontrol edilmelidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2571, .topicId = 97,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::ofstream dosya(\"gecersiz/yol/ad.txt\");\nif (!dosya.is_open()) {\n    dosya << \"veri\";\n}\nBu kod (açma başarısız olduğunda dosyaya yazmaya çalışmak) ne olur?",
        .options = {"Program çöker", "Bir istisna (exception) fırlatılır", "Yazma SESSİZCE hiçbir şey yapmaz, program normal devam eder", "Derleme hatası oluşur"},
        .acceptedAnswers = {"c"},
        .explanation = "Açılamayan bir akışa yazmak sessizce hiçbir şey yapmaz.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2572, .topicId = 97,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::ofstream, hangi başlığı gerektirir?",
        .options = {"<iostream>", "<sstream>", "<memory>", "<fstream>"},
        .acceptedAnswers = {"d"},
        .explanation = "std::ofstream <fstream> başlığında tanımlıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2573, .topicId = 97,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::ofstream dosya1(\"ornek.txt\");\ndosya1 << \"Birinci\";\ndosya1.close();\nstd::ofstream dosya2(\"ornek.txt\");\ndosya2 << \"Ikinci\";\ndosya2.close();\nBu kodlar çalıştırıldıktan sonra ornek.txt dosyasının içeriği nedir?",
        .options = {"Ikinci", "BirinciIkinci", "Birinci", "Dosya boş kalır"},
        .acceptedAnswers = {"a"},
        .explanation = "İkinci açma dosyayı truncate eder; sadece \"Ikinci\" kalır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2574, .topicId = 97,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::ofstream dosya1(\"ornek2.txt\");\ndosya1 << \"Birinci\";\ndosya1.close();\nstd::ofstream dosya2(\"ornek2.txt\", std::ios::app);\ndosya2 << \"Ikinci\";\ndosya2.close();\nBu kodlar çalıştırıldıktan sonra ornek2.txt dosyasının içeriği nedir?",
        .options = {"Ikinci", "BirinciIkinci", "Birinci", "Dosya boş kalır"},
        .acceptedAnswers = {"b"},
        .explanation = "std::ios::app ile ikinci yazma sonuna eklenir; içerik \"BirinciIkinci\" olur.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2575, .topicId = 97,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::ofstream, bir dosyaya yazmak için kullanılır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2576, .topicId = 97,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::ofstream ile bir dosya açmak, dosya zaten VARSA içeriğinin SONUNA otomatik olarak ekler.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: varsayılan olarak içerik silinir (truncate).",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2577, .topicId = 97,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Var olan bir dosyanın sonuna eklemek için std::ios::app modu kullanılmalıdır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2578, .topicId = 97,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Bir dosyaya yazmadan önce .is_open() ile kontrol yapmak iyi bir uygulamadır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2579, .topicId = 97,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Açılamayan bir dosyaya yazmaya çalışmak, bir istisna (exception) fırlatır (varsayılan olarak).",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: istisna fırlatmaz, sessizce hiçbir şey yapmaz.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2580, .topicId = 97,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::ofstream, <fstream> başlığını gerektirir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2581, .topicId = 97,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir dosyaya yazmak için kullanılan sınıf std::_____ dir (İngilizce kelime).",
        .acceptedAnswers = {"ofstream"},
        .explanation = "std::ofstream kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2582, .topicId = 97,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::ofstream ile bir dosya açmak, dosya zaten varsa içeriğini VARSAYILAN olarak _____ (Türkçe kelime, 'siler' anlamında).",
        .acceptedAnswers = {"siler"},
        .explanation = "Varsayılan olarak içerik silinir (truncate).",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2583, .topicId = 97,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "Var olan bir dosyanın sonuna eklemek için std::ios::_____ modu kullanılır (İngilizce kelime).",
        .acceptedAnswers = {"app"},
        .explanation = "std::ios::app kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2584, .topicId = 97,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "Bir dosyanın başarıyla açılıp açılmadığını kontrol eden üye fonksiyon _____ dir (İngilizce, kelimeler birleşik, alt çizgili).",
        .acceptedAnswers = {"is_open"},
        .explanation = "is_open() kullanılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2585, .topicId = 97,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::ofstream, hangi başlığı gerektirir (İngilizce kelime)?",
        .acceptedAnswers = {"fstream"},
        .explanation = "<fstream> başlığı gerekir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2586, .topicId = 97,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "Açılamayan bir dosyaya yazmak, bir istisna FIRLATMAZ; yazma sessizce hiçbir şey _____ (Türkçe kelime, 'yapmaz' anlamında).",
        .acceptedAnswers = {"yapmaz"},
        .explanation = "Sessizce hiçbir şey yapmaz.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2587, .topicId = 97,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "_____\ndosya << \"veri\";\ndosya.close();\ndosya adlı bir std::ofstream'i \"cikti.txt\" dosyasıyla açan satırı yazın.",
        .acceptedAnswers = {"std::ofstream dosya(\"cikti.txt\");"},
        .explanation = "std::ofstream ile dosya açılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2588, .topicId = 97,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::ofstream dosya(\"cikti.txt\");\n_____\ndosya << \"veri\";\ndosya'nın gerçekten açılıp açılmadığını kontrol eden if satırını yazın.",
        .acceptedAnswers = {"if (dosya.is_open()) {"},
        .explanation = "is_open() ile kontrol edilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2589, .topicId = 97,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "std::ofstream dosya(\"test1.txt\");\nstd::cout << dosya.is_open();\nYukarıdaki kodun ekran çıktısı nedir (dosyanın başarıyla açıldığı varsayılarak)?",
        .acceptedAnswers = {"1"},
        .explanation = "Başarıyla açıldığında is_open() true (1) döner.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2590, .topicId = 97,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "std::ofstream dosya1(\"test2.txt\");\ndosya1 << \"A\";\ndosya1.close();\nstd::ofstream dosya2(\"test2.txt\");\ndosya2 << \"B\";\ndosya2.close();\nstd::ifstream okuyucu(\"test2.txt\");\nstd::string icerik;\nstd::getline(okuyucu, icerik);\nstd::cout << icerik;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"B"},
        .explanation = "İkinci ofstream açması dosyayı truncate eder; sadece \"B\" kalır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2591, .topicId = 97,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::ofstream dosya(\"cikti.txt\");\ndosya << \"veri\";\n\nBu kod ÇALIŞIR ama YANLIŞTIR çünkü dosya.is_open() KONTROL EDİLMEDEN yazılıyor; açma başarısız olursa yazma sessizce hiçbir şey yapmaz ve fark edilmez. Kontrol ekleyerek düzeltilmiş kodu yazın.",
        .acceptedAnswers = {"if (dosya.is_open()) { dosya << \"veri\"; }"},
        .explanation = "is_open() kontrolü eklenmelidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2592, .topicId = 97,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::ofstream dosya1(\"gunluk.txt\");\ndosya1 << \"Ilk kayit\";\ndosya1.close();\nstd::ofstream dosya2(\"gunluk.txt\");\ndosya2 << \"Ikinci kayit\";\ndosya2.close();\n// Beklenen: dosyada hem \"Ilk kayit\" hem \"Ikinci kayit\" olsun\n\nBu kod, İKİNCİ açmanın VARSAYILAN olarak dosyayı KIRPMASI (truncate) nedeniyle \"Ilk kayit\"i SİLER; sadece \"Ikinci kayit\" kalır. İkinci açma satırını, std::ios::app kullanarak düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::ofstream dosya2(\"gunluk.txt\", std::ios::app);"},
        .explanation = "std::ios::app ile içerik silinmez, sonuna eklenir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2593, .topicId = 97,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nstd::ofstream dosya(\"cikti.txt\")\ndosya << \"veri\";\n\nProgramcı dosya tanımının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"std::ofstream dosya(\"cikti.txt\");"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2594, .topicId = 97,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir dosyaya yazan geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"dosya.close();\n    return 0;\n}", "std::ofstream dosya(\"cikti.txt\");\n    dosya << \"veri\";", "int main() {"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "main açılışı (3), tanım+yazma (2), kapanış (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2595, .topicId = 97,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir dosyaya yazan bir program yazın: dosyayı is_open() ile kontrol edin, \"Merhaba\" yazın ve dosyayı kapatın.",
        .acceptedAnswers = {"ofstream", "is_open"},
        .explanation = "Dosya açılıp kontrol edildikten sonra yazılır.",
        .baseXp = 40,
    });
}
