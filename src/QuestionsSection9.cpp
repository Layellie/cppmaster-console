#include "QuestionContent.h"

#include "Question.h"

void appendSection9Questions(std::vector<Question>& questions) {
    // Topic 81: pair
    questions.push_back(Question{
        .id = 2103, .topicId = 81,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::pair<T1,T2>'nin amacı nedir?",
        .options = {"Bir konteynerin boyutunu değiştirmek", "İki farklı (veya aynı) türden değeri tek bir nesnede birlikte tutmak", "Bir fonksiyonu virtual yapmak", "Bir döngüyü sonlandırmak"},
        .acceptedAnswers = {"b"},
        .explanation = "std::pair, iki değeri tek bir nesnede birlikte tutar.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2104, .topicId = 81,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::pair<std::string, int> p(\"Ali\", 20); p'nin elemanlarına nasıl erişilir?",
        .options = {"p[0], p[1]", "p.get(0), p.get(1)", "p.first, p.second", "p.a, p.b"},
        .acceptedAnswers = {"c"},
        .explanation = "pair elemanlarına .first ve .second ile erişilir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2105, .topicId = 81,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::pair<std::string, int> p(\"Ali\", 20);\nstd::cout << p.first << p.second;\nEkran çıktısı nedir?",
        .options = {"Ali20", "20Ali", "Derleme hatası", "AliInt"},
        .acceptedAnswers = {"a"},
        .explanation = "p.first (\"Ali\") ve p.second (20) sırayla yazdırılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2106, .topicId = 81,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::make_pair(a, b) fonksiyonu ne yapar?",
        .options = {"Bir pair'i siler", "İki pair'i karşılaştırır", "Bir pair'i sıralar", "Türleri argümanlardan otomatik çıkararak bir pair oluşturur"},
        .acceptedAnswers = {"d"},
        .explanation = "make_pair, argümanların türlerini otomatik çıkarır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2107, .topicId = 81,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::pair<int,int> p(3,4);\np[0] = 5;\nBu kod derlenir mi?",
        .options = {"Evet, p.first 5 olur", "Hayır, pair'in operator[] tanımı yoktur, derleme hatası oluşur", "Evet, yeni bir eleman eklenir", "Evet ama çalışma zamanı hatası verir"},
        .acceptedAnswers = {"b"},
        .explanation = "std::pair'in operator[] tanımı yoktur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2108, .topicId = 81,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::pair<int, double> p(3, 4.5);\nstd::cout << p.first + p.second;\nEkran çıktısı nedir?",
        .options = {"34.5", "7", "7.5", "Derleme hatası"},
        .acceptedAnswers = {"c"},
        .explanation = "3 + 4.5 = 7.5.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2109, .topicId = 81,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::pair<int,int> p1(1,2);\nstd::pair<int,int> p2(1,2);\nstd::cout << (p1 == p2);\nBu kod derlenir mi ve çıktısı nedir?",
        .options = {"Hayır, pair karşılaştırılamaz, derleme hatası", "Evet, çıktı 0'dır", "Evet ama çıktı \"true\" yazısıdır", "Evet, derlenir; çıktı 1'dir (p1 ve p2'nin elemanları eşit)"},
        .acceptedAnswers = {"d"},
        .explanation = "std::pair operator== ile elemanları karşılaştırır; p1 ve p2'nin elemanları eşit olduğundan çıktı 1'dir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2110, .topicId = 81,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::pair<int, std::string> p(5, \"be\");\np.second += \"ş\";\nstd::cout << p.second;\nEkran çıktısı nedir?",
        .options = {"beş", "be", "Derleme hatası", "5be"},
        .acceptedAnswers = {"a"},
        .explanation = "p.second bir std::string'tir; += ile \"ş\" eklenir, sonuç \"beş\".",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2111, .topicId = 81,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::pair, iki farklı türden değeri tek bir nesnede birlikte tutabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2112, .topicId = 81,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "pair elemanlarına .first ve .second ile erişilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2113, .topicId = 81,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::pair, operator[] ile index kullanarak elemanlarına erişime izin verir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: pair'in operator[] tanımı yoktur.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2114, .topicId = 81,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::make_pair, türleri argümanlardan otomatik çıkarır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2115, .topicId = 81,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "İki pair, elemanları eşitse operator== ile karşılaştırılabilir (elemanların türleri karşılaştırmayı destekliyorsa).",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2116, .topicId = 81,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "pair'in .first elemanı her zaman bir sayı türünde olmalıdır.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: .first herhangi bir türde olabilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2117, .topicId = 81,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "İki farklı türden değeri tek bir nesnede birlikte tutan şablon yapıya _____ denir (İngilizce kelime).",
        .acceptedAnswers = {"pair"},
        .explanation = "Bu yapıya pair denir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2118, .topicId = 81,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::pair<std::string,int> p(\"Ayşe\",30);\nstd::cout << p.first;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"Ayşe"},
        .explanation = "p.first, \"Ayşe\" değerini tutar.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2119, .topicId = 81,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "pair'in ikinci elemanına erişmek için _____ üye değişkeni kullanılır (İngilizce kelime).",
        .acceptedAnswers = {"second"},
        .explanation = "second üye değişkeni kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2120, .topicId = 81,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::pair<int,int> p(4,6);\nstd::cout << p.first + p.second;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"10"},
        .explanation = "4 + 6 = 10.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2121, .topicId = 81,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "Türleri argümanlardan otomatik çıkararak bir pair oluşturan fonksiyon std::_____'dur (İngilizce kelime).",
        .acceptedAnswers = {"make_pair"},
        .explanation = "std::make_pair kullanılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2122, .topicId = 81,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "pair'in .first elemanına erişmek için kullanılan üye değişken _____ dir (İngilizce kelime).",
        .acceptedAnswers = {"first"},
        .explanation = "first üye değişkeni kullanılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2123, .topicId = 81,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "_____\nstd::cout << ogrenci.first << \" \" << ogrenci.second;\nogrenci adlı bir pair'i \"Can\" ve 18 değerleriyle tanımlayan satırı yazın.",
        .acceptedAnswers = {"std::pair<std::string, int> ogrenci(\"Can\", 18);"},
        .explanation = "pair, iki değeri birlikte tanımlar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2124, .topicId = 81,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::pair<int,int> p(2, 3);\n_____\np'nin iki elemanının toplamını ekrana yazdıran satırı yazın.",
        .acceptedAnswers = {"std::cout << p.first + p.second;"},
        .explanation = "İki eleman toplanıp yazdırılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2125, .topicId = 81,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "std::pair<int,int> p(7, 3);\nstd::cout << p.first - p.second;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"4"},
        .explanation = "7 - 3 = 4.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2126, .topicId = 81,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "std::pair<int,int> p1(2,3);\nstd::pair<int,int> p2(2,3);\np1.first = 10;\nstd::cout << p1.first << \" \" << p2.first;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"10 2"},
        .explanation = "p1 ve p2 bağımsız kopyalardır; p1'in değişmesi p2'yi etkilemez.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2127, .topicId = 81,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::pair<int,int> p(3,4);\nstd::cout << p[0];\n\nBu kod derlenmez çünkü pair'in operator[] tanımı yoktur. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::cout << p.first;"},
        .explanation = "pair elemanlarına .first/.second ile erişilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2128, .topicId = 81,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::pair<std::string,int> p(\"Ali\", 20);\nstd::cout << p.First;\n\nBu kod derlenmez çünkü üye değişken adı 'first' küçük harfle yazılır, 'First' değil (C++ büyük/küçük harfe duyarlıdır). Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::cout << p.first;"},
        .explanation = "C++ büyük/küçük harfe duyarlıdır; doğru üye adı first'tür.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2129, .topicId = 81,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nstd::pair<int,int> p(3, 4)\nstd::cout << p.first;\n\nProgramcı p tanımının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"std::pair<int,int> p(3, 4);"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2130, .topicId = 81,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir pair tanımlayıp elemanlarını yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"std::cout << p.first << p.second;\n    return 0;\n}", "std::pair<int,int> p(5, 6);", "int main() {"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "main açılışı (3), pair tanımı (2), yazdır+kapanış (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2131, .topicId = 81,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir std::string ve bir int değeri birlikte tutan bir pair tanımlayın; main() içinde .first ve .second elemanlarını ekrana yazdırın.",
        .acceptedAnswers = {"pair", "first", "second"},
        .explanation = "pair, .first/.second ile erişilen iki elemanı tutar.",
        .baseXp = 40,
    });

    // Topic 82: tuple
    questions.push_back(Question{
        .id = 2132, .topicId = 82,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::tuple<...>'ın amacı nedir?",
        .options = {"Bir konteynerin sırasını değiştirmek", "Sadece iki elemanı bir arada tutmak", "İkiden fazla farklı türden değeri tek bir nesnede birlikte tutmak", "Bir sınıfı soyut yapmak"},
        .acceptedAnswers = {"c"},
        .explanation = "tuple, pair'in ikiden fazla elemana genelleştirilmiş halidir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2133, .topicId = 82,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::tuple<int,int,int> t(1,2,3); t'nin ilk elemanına nasıl erişilir?",
        .options = {"t.first", "t[0]", "t.get(0)", "std::get<0>(t)"},
        .acceptedAnswers = {"d"},
        .explanation = "tuple elemanlarına std::get<Index>(t) ile erişilir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2134, .topicId = 82,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::tuple<std::string,int,double> t(\"Can\", 18, 2.5);\nstd::cout << std::get<0>(t);\nEkran çıktısı nedir?",
        .options = {"Can", "18", "2.5", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "std::get<0>(t), tuple'ın ilk elemanına (\"Can\") erişir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2135, .topicId = 82,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::get<Index>(t) çağrısında Index nasıl olmalıdır?",
        .options = {"Çalışma zamanında hesaplanan bir değişken", "Derleme zamanında bilinen bir sabit", "Her zaman 0", "Bir std::string"},
        .acceptedAnswers = {"b"},
        .explanation = "Index, derleme zamanında bilinen bir sabit olmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2136, .topicId = 82,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::tuple<int,int> t(3,4);\nint i = 0;\nstd::cout << std::get<i>(t);\nBu kod derlenir mi?",
        .options = {"Evet, çıktı 3'tür", "Evet, çıktı 4'tür", "Hayır, index derleme zamanı sabiti olmalıdır, derleme hatası oluşur", "Evet ama çalışma zamanı hatası verir"},
        .acceptedAnswers = {"c"},
        .explanation = "std::get<...> çalışma zamanı değişkeniyle kullanılamaz.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2137, .topicId = 82,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::tuple<int,double> t(5, 2.5);\nstd::cout << std::get<0>(t) + std::get<1>(t);\nEkran çıktısı nedir?",
        .options = {"52.5", "5", "2.5", "7.5"},
        .acceptedAnswers = {"d"},
        .explanation = "5 + 2.5 = 7.5.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2138, .topicId = 82,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::tuple<int,int,int> t1(1,2,3);\nstd::tuple<int,int,int> t2(1,2,3);\nstd::cout << (t1 == t2);\nBu kod derlenir mi ve çıktısı nedir?",
        .options = {"Evet, derlenir; çıktı 1'dir (tüm elemanlar eşit)", "Hayır, tuple karşılaştırılamaz", "Evet, çıktı 0'dır", "Evet ama çıktı \"true\" yazısıdır"},
        .acceptedAnswers = {"a"},
        .explanation = "std::tuple operator== ile tüm elemanları sırayla karşılaştırır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2139, .topicId = 82,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::tuple<int,std::string> t(3, \"ba\");\nstd::get<1>(t) += \"lık\";\nstd::cout << std::get<1>(t);\nEkran çıktısı nedir?",
        .options = {"ba", "balık", "Derleme hatası", "3balık"},
        .acceptedAnswers = {"b"},
        .explanation = "std::get<1>(t) bir std::string referansı döndürür; += ile \"lık\" eklenir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2140, .topicId = 82,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::tuple, ikiden fazla farklı türden değeri tek bir nesnede tutabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2141, .topicId = 82,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "tuple elemanlarına std::get<Index> ile erişilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2142, .topicId = 82,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::get<i>(t) çağrısında i, çalışma zamanında değişebilen bir değişken olabilir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: i, derleme zamanı sabiti olmalıdır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2143, .topicId = 82,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::tuple, pair'in ikiden fazla elemana genelleştirilmiş halidir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2144, .topicId = 82,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "İki tuple, tüm elemanları eşitse operator== ile karşılaştırılabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2145, .topicId = 82,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::get<0>(t), her zaman t'nin SON elemanına erişir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: std::get<0> her zaman İLK elemana erişir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2146, .topicId = 82,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "İkiden fazla farklı türden değeri tek bir nesnede tutan şablon yapıya _____ denir (İngilizce kelime).",
        .acceptedAnswers = {"tuple"},
        .explanation = "Bu yapıya tuple denir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2147, .topicId = 82,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::tuple<int,int> t(4,5);\nstd::cout << std::get<0>(t);\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"4"},
        .explanation = "std::get<0>(t) ilk elemana (4) erişir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2148, .topicId = 82,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "tuple elemanlarına erişmek için kullanılan fonksiyon std::_____ dir (İngilizce kelime).",
        .acceptedAnswers = {"get"},
        .explanation = "std::get kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2149, .topicId = 82,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::tuple<int,int,int> t(1,2,3);\nstd::cout << std::get<2>(t);\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"3"},
        .explanation = "std::get<2>(t) üçüncü elemana (3) erişir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2150, .topicId = 82,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::get<Index>(t) çağrısındaki Index, derleme _____ bilinmelidir (Türkçe kelime).",
        .acceptedAnswers = {"zamanında"},
        .explanation = "Index, derleme zamanında bilinmelidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2151, .topicId = 82,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::tuple<int,int> t(2,2);\nstd::cout << std::get<0>(t) * std::get<1>(t);\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"4"},
        .explanation = "2 * 2 = 4.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2152, .topicId = 82,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "_____\nstd::cout << std::get<0>(kayit) << std::get<1>(kayit);\nkayit adlı bir tuple'ı 5 ve 10 değerleriyle tanımlayan satırı yazın.",
        .acceptedAnswers = {"std::tuple<int, int> kayit(5, 10);"},
        .explanation = "tuple, iki değeri birlikte tanımlar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2153, .topicId = 82,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::tuple<int,int,int> t(1,2,3);\n_____\nt'nin üçüncü elemanını ekrana yazdıran satırı yazın.",
        .acceptedAnswers = {"std::cout << std::get<2>(t);"},
        .explanation = "std::get<2>(t) üçüncü elemana erişir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2154, .topicId = 82,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "std::tuple<int,int,int> t(10, 20, 30);\nstd::cout << std::get<0>(t) + std::get<1>(t) + std::get<2>(t);\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"60"},
        .explanation = "10 + 20 + 30 = 60.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2155, .topicId = 82,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "std::tuple<int,double,std::string> t(1, 2.5, \"x\");\nstd::cout << std::get<0>(t) << \" \" << std::get<1>(t) << \" \" << std::get<2>(t);\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"1 2.5 x"},
        .explanation = "Her eleman sırasıyla yazdırılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2156, .topicId = 82,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::tuple<int,int> t(3,4);\nstd::cout << t.first;\n\nBu kod derlenmez çünkü tuple'ın .first üye değişkeni yoktur (bu pair'e özgüdür); tuple elemanlarına std::get<Index>(t) ile erişilir. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::cout << std::get<0>(t);"},
        .explanation = "tuple elemanlarına std::get ile erişilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2157, .topicId = 82,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::tuple<int,int,int> t(1,2,3);\nint i = 1;\nstd::cout << std::get<i>(t);\n\nBu kod derlenmez çünkü std::get<...> içindeki index, çalışma zamanında değişen bir değişken (i) olamaz; derleme zamanı sabiti olmalıdır. Hatalı satırı, sabit bir index kullanarak düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::cout << std::get<1>(t);"},
        .explanation = "Index, derleme zamanı sabiti olmalıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2158, .topicId = 82,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nstd::tuple<int,int> t(3, 4)\nstd::cout << std::get<0>(t);\n\nProgramcı t tanımının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"std::tuple<int,int> t(3, 4);"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2159, .topicId = 82,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir tuple tanımlayıp bir elemanını yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"std::cout << std::get<1>(t);\n    return 0;\n}", "std::tuple<int,int> t(7, 9);", "int main() {"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "main açılışı (3), tuple tanımı (2), yazdır+kapanış (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2160, .topicId = 82,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir int, bir double ve bir std::string değerini birlikte tutan bir tuple tanımlayın; main() içinde std::get ile üçünü de ekrana yazdırın.",
        .acceptedAnswers = {"tuple", "get"},
        .explanation = "tuple elemanlarına std::get ile erişilir.",
        .baseXp = 40,
    });

    // Topic 83: set
    questions.push_back(Question{
        .id = 2161, .topicId = 83,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::set<T>'nin temel özelliği nedir?",
        .options = {"Elemanları ekleme sırasına göre saklar", "Elemanların tekrarına izin verir", "Sadece sayısal türleri destekler", "Tekrarsız elemanları otomatik olarak sıralı (artan) sırada saklar"},
        .acceptedAnswers = {"d"},
        .explanation = "set, tekrarsız elemanları otomatik olarak sıralı tutar.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2162, .topicId = 83,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::set<int> s;\ns.insert(5);\ns.insert(2);\ns.insert(8);\nfor (int x : s) { std::cout << x << \" \"; }\nEkran çıktısı nedir?",
        .options = {"2 5 8", "5 2 8", "8 5 2", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "set, elemanları her zaman artan sırada verir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2163, .topicId = 83,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::set<int> s;\ns.insert(3);\ns.insert(3);\nstd::cout << s.size();\nEkran çıktısı nedir?",
        .options = {"2", "1", "0", "Derleme hatası"},
        .acceptedAnswers = {"b"},
        .explanation = "İkinci insert(3), zaten var olan bir değeri eklemeye çalıştığından yok sayılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2164, .topicId = 83,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::set elemanlarının sırası neye göre belirlenir?",
        .options = {"Ekleme sırasına göre", "Rastgele", "Otomatik olarak artan (sıralı) sıraya göre", "Hash değerine göre"},
        .acceptedAnswers = {"c"},
        .explanation = "set elemanları otomatik olarak sıralıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2165, .topicId = 83,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::set<int> s = {5, 1, 3};\ns.insert(1);\nstd::cout << s.size();\nEkran çıktısı nedir?",
        .options = {"4", "2", "0", "3"},
        .acceptedAnswers = {"d"},
        .explanation = "1 zaten sette olduğundan tekrar eklenmez; size 3 kalır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2166, .topicId = 83,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = ".insert() ile zaten sette bulunan bir değer tekrar eklenirse ne olur?",
        .options = {"Sessizce yok sayılır, set değişmez", "Değer iki kez eklenir", "Derleme hatası oluşur", "Çalışma zamanı hatası (exception) oluşur"},
        .acceptedAnswers = {"a"},
        .explanation = "Tekrar eklenen değer sessizce yok sayılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2167, .topicId = 83,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::set<int> s;\ns.insert(10);\ns.insert(5);\ns.insert(20);\ns.insert(5);\nfor (int x : s) { std::cout << x << \" \"; }\nEkran çıktısı nedir?",
        .options = {"10 5 20", "5 10 20", "20 10 5", "5 5 10 20"},
        .acceptedAnswers = {"b"},
        .explanation = "set, tekrarsız elemanları sıralı verir: 5 10 20.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2168, .topicId = 83,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::set<int> s = {4, 2, 6};\nauto it = s.find(2);\nstd::cout << (it != s.end());\nBu kod derlenir mi ve çıktısı nedir?",
        .options = {"Hayır, set'te find() yoktur", "Evet, çıktı 0'dır", "Evet, çıktı 1'dir (2 sette bulunduğundan)", "Evet ama derleme hatası verir"},
        .acceptedAnswers = {"c"},
        .explanation = "find(2), 2 sette olduğundan onu gösteren bir iterator döndürür; it != end() true (1).",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2169, .topicId = 83,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::set, tekrarsız elemanları otomatik olarak sıralı sırada tutar.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2170, .topicId = 83,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::set'e aynı değeri iki kez insert() etmek, setin boyutunu ikiye katlar.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: tekrar eklenen değer yok sayılır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2171, .topicId = 83,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "set üzerinde bir for döngüsüyle gezinmek, elemanları her zaman artan sırada verir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2172, .topicId = 83,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::set elemanları, ekleme sırasına göre saklanır.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: elemanlar sıralı (artan) sırada saklanır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2173, .topicId = 83,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = ".find() ile bir elemanın sette olup olmadığı kontrol edilebilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2174, .topicId = 83,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::set, aynı değeri birden fazla kez tutabilir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: set tekrarsız elemanlar tutar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2175, .topicId = 83,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Tekrarsız elemanları otomatik olarak sıralı tutan STL konteynerine _____ denir (İngilizce kelime).",
        .acceptedAnswers = {"set"},
        .explanation = "Bu konteynere set denir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2176, .topicId = 83,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::set<int> s;\ns.insert(9);\ns.insert(2);\nfor (int x : s) std::cout << x;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"29"},
        .explanation = "set sıralı verir: 2 sonra 9.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2177, .topicId = 83,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "set'e eleman eklemek için kullanılan üye fonksiyon _____ dir (İngilizce kelime).",
        .acceptedAnswers = {"insert"},
        .explanation = "insert() kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2178, .topicId = 83,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::set<int> s = {1,2,3};\ns.insert(2);\nstd::cout << s.size();\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"3"},
        .explanation = "2 zaten sette olduğundan tekrar eklenmez.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2179, .topicId = 83,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::set elemanları, hangi operatöre göre sıralanır (bir sembol)?",
        .acceptedAnswers = {"<", "operator<"},
        .explanation = "set elemanları operator< kullanılarak sıralanır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2180, .topicId = 83,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "Bir elemanın sette olup olmadığını EKLEME YAPMADAN kontrol etmek için _____ üye fonksiyonu kullanılır (İngilizce kelime).",
        .acceptedAnswers = {"find"},
        .explanation = "find() kullanılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2181, .topicId = 83,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "_____\ns.insert(7);\ns adlı bir int set'i tanımlayan satırı yazın.",
        .acceptedAnswers = {"std::set<int> s;"},
        .explanation = "std::set<int> ile bir int set'i tanımlanır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2182, .topicId = 83,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::set<int> s = {5, 1, 3};\n_____\ns'nin tüm elemanlarını sırayla ekrana yazdıran döngüyü yazın.",
        .acceptedAnswers = {"for (int x : s) { std::cout << x << \" \"; }"},
        .explanation = "range-for ile set elemanları sıralı gezilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2183, .topicId = 83,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "std::set<int> s;\ns.insert(3);\ns.insert(1);\ns.insert(2);\nfor (int x : s) { std::cout << x; }\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"123"},
        .explanation = "set, elemanları artan sırada verir: 1 2 3.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2184, .topicId = 83,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "std::set<int> s = {5, 3, 8, 3, 1};\nstd::cout << s.size() << \" \";\nfor (int x : s) { std::cout << x; }\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"4 1358"},
        .explanation = "Tekrarlı 3 bir kez sayılır (size 4); sıralı çıktı: 1 3 5 8.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2185, .topicId = 83,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::set<int> s;\ns.insert(4);\nstd::cout << s[0];\n\nBu kod derlenmez çünkü std::set'in operator[] tanımı yoktur. Hatalı satırı, elemanlara erişmenin doğru yolunu kullanarak (bir for döngüsüyle) düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"for (int x : s) { std::cout << x; }"},
        .explanation = "set elemanlarına iterasyonla erişilir, index ile değil.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2186, .topicId = 83,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::set<int> s = {3, 1, 2};\nstd::cout << s.at(0);\n\nBu kod derlenmez çünkü std::set'in .at() üye fonksiyonu yoktur (bu vector/map'e özgüdür). Hatalı satırı, elemanları bir for döngüsüyle yazdıracak şekilde düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"for (int x : s) { std::cout << x; }"},
        .explanation = "set'in .at() tanımı yoktur; elemanlara iterasyonla erişilir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2187, .topicId = 83,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nstd::set<int> s\ns.insert(5);\n\nProgramcı s tanımının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"std::set<int> s;"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2188, .topicId = 83,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir set tanımlayıp elemanlarını sıralı şekilde yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"for (int x : s) { std::cout << x; }\n    return 0;\n}", "std::set<int> s = {3, 1, 2};", "int main() {"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "main açılışı (3), set tanımı (2), döngü+kapanış (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2189, .topicId = 83,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir int set'i tanımlayın; sırasız 3 değer ekleyin (biri tekrar eden) ve for döngüsüyle tüm elemanları sıralı şekilde ekrana yazdırın.",
        .acceptedAnswers = {"set", "insert"},
        .explanation = "set, tekrarsız elemanları sıralı olarak tutar.",
        .baseXp = 40,
    });

    // Topic 84: map
    questions.push_back(Question{
        .id = 2190, .topicId = 84,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::map<K,V>'nin temel özelliği nedir?",
        .options = {"Tekrarsız anahtarları bir değerle sıralı şekilde eşleştirir", "Elemanları LIFO sırayla tutar", "Sadece sayısal anahtarları destekler", "Anahtarları hash tablosunda sırasız tutar"},
        .acceptedAnswers = {"a"},
        .explanation = "map, anahtar-değer çiftlerini sıralı şekilde tutar.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2191, .topicId = 84,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::map<std::string,int> m;\nm[\"x\"] = 5;\nstd::cout << m[\"x\"];\nEkran çıktısı nedir?",
        .options = {"0", "5", "Derleme hatası", "x"},
        .acceptedAnswers = {"b"},
        .explanation = "m[\"x\"], 5 değerini döndürür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2192, .topicId = 84,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::map<std::string,int> m;\nm[\"a\"]=1; m[\"b\"]=2;\nstd::cout << m.size();\nEkran çıktısı nedir?",
        .options = {"0", "1", "2", "Derleme hatası"},
        .acceptedAnswers = {"c"},
        .explanation = "İki anahtar eklendi, size 2.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2193, .topicId = 84,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::map<std::string,int> m;\nm[\"a\"]=1;\nstd::cout << m[\"z\"];\nstd::cout << \" \" << m.size();\nEkran çıktısı nedir?",
        .options = {"1 1", "0 1", "Derleme hatası", "0 2"},
        .acceptedAnswers = {"d"},
        .explanation = "m[\"z\"] okuması \"z\"'yi 0 ile ekler (side effect); size 2 olur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2194, .topicId = 84,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "Var olmayan bir anahtarı EKLEME YAPMADAN kontrol etmek için ne kullanılmalıdır?",
        .options = {"m.find(anahtar) == m.end()", "m[anahtar] == 0", "m.size() == 0", "m.at(anahtar) her zaman"},
        .acceptedAnswers = {"a"},
        .explanation = ".find(), anahtarı eklemeden arar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2195, .topicId = 84,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::map<std::string,int> m;\nm[\"a\"]=3; m[\"b\"]=1;\nfor (auto& kv : m) { std::cout << kv.first; }\nEkran çıktısı nedir?",
        .options = {"ba", "ab", "Sırasız, tanımsız", "Derleme hatası"},
        .acceptedAnswers = {"b"},
        .explanation = "map anahtarları alfabetik sıralıdır: \"a\" önce \"b\" sonra.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2196, .topicId = 84,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::map<std::string,int> m;\nm[\"x\"] = 1;\nif (m[\"y\"] > 0) { std::cout << \"var\"; } else { std::cout << \"yok\"; }\nstd::cout << \" \" << m.size();\nEkran çıktısı nedir?",
        .options = {"var 1", "var 2", "yok 2", "yok 1"},
        .acceptedAnswers = {"c"},
        .explanation = "m[\"y\"] okuması \"y\"'yi 0 ile ekler; 0 > 0 yanlış, \"yok\" yazdırılır; size 2 olur.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2197, .topicId = 84,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::map<std::string,int> m = {{\"b\",2},{\"a\",1},{\"c\",3}};\nfor (auto& kv : m) { std::cout << kv.first; }\nEkran çıktısı nedir?",
        .options = {"bac", "cba", "Sırasız, tanımsız", "abc"},
        .acceptedAnswers = {"d"},
        .explanation = "map anahtarları her zaman sıralıdır: a, b, c.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2198, .topicId = 84,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::map, anahtarları otomatik olarak sıralı (artan) sırada tutar.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2199, .topicId = 84,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "operator[] ile olmayan bir anahtarı okumak, o anahtarı map'e otomatik olarak ekler.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2200, .topicId = 84,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = ".find() ile bir anahtarı aramak, o anahtarı map'e ekler.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: .find() anahtarı eklemeden arar.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2201, .topicId = 84,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::map, aynı anahtarı birden fazla kez tutabilir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: map anahtarları tekrarsızdır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2202, .topicId = 84,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::map üzerinde bir for döngüsüyle gezinmek, anahtarları her zaman sıralı (artan) sırada verir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2203, .topicId = 84,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::map'in operator[]'i, sadece OKUMA yapar, asla yeni bir eleman EKLEMEZ.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: olmayan bir anahtarı okumak yeni bir eleman ekler.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2204, .topicId = 84,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Anahtarları sıralı şekilde bir değerle eşleştiren STL konteynerine _____ denir (İngilizce kelime).",
        .acceptedAnswers = {"map"},
        .explanation = "Bu konteynere map denir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2205, .topicId = 84,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::map<std::string,int> m;\nm[\"k\"] = 7;\nstd::cout << m[\"k\"];\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"7"},
        .explanation = "m[\"k\"], 7 değerini döndürür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2206, .topicId = 84,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "Var olmayan bir anahtarı EKLEME YAPMADAN aramak için kullanılan üye fonksiyon _____ dir (İngilizce kelime).",
        .acceptedAnswers = {"find"},
        .explanation = "find() kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2207, .topicId = 84,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::map<std::string,int> m;\nm[\"a\"]=1;\nm[\"b\"];\nstd::cout << m.size();\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"2"},
        .explanation = "m[\"b\"] okuması \"b\"'yi ekler; size 2 olur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2208, .topicId = 84,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "operator[] ile olmayan bir anahtarı okumak, o anahtarı varsayılan değerle map'e otomatik olarak _____ (Türkçe kelime).",
        .acceptedAnswers = {"ekler"},
        .explanation = "Bu bir yan etkidir (side effect).",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2209, .topicId = 84,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::map<std::string,int> m = {{\"z\",1},{\"a\",2}};\nauto it = m.begin();\nstd::cout << it->first;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"a"},
        .explanation = "map sıralı olduğundan begin(), alfabetik olarak en küçük anahtarı (\"a\") gösterir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2210, .topicId = 84,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "_____\nm[\"x\"] = 5;\nm adlı bir std::string-int map'i tanımlayan satırı yazın.",
        .acceptedAnswers = {"std::map<std::string, int> m;"},
        .explanation = "std::map<std::string,int> ile tanımlanır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2211, .topicId = 84,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::map<std::string,int> m;\nm[\"a\"] = 1;\n_____\n\"a\" anahtarının map'te olup olmadığını EKLEME YAPMADAN kontrol eden if satırını yazın.",
        .acceptedAnswers = {"if (m.find(\"a\") != m.end()) {"},
        .explanation = ".find() ile eklemeden kontrol edilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2212, .topicId = 84,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "std::map<std::string,int> m;\nm[\"x\"] = 10;\nm[\"y\"] = 20;\nstd::cout << m[\"x\"] + m[\"y\"];\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"30"},
        .explanation = "10 + 20 = 30.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2213, .topicId = 84,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "std::map<std::string,int> m;\nm[\"a\"] = 5;\nstd::cout << m.size() << \" \";\nm[\"b\"];\nstd::cout << m.size();\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"1 2"},
        .explanation = "İlk size 1; m[\"b\"] okuması \"b\"'yi ekler, size 2 olur.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2214, .topicId = 84,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::map<std::string,int> m;\nm[\"a\"] = 1;\nstd::cout << m.first;\n\nBu kod derlenmez çünkü std::map'in .first üye değişkeni yoktur (bu pair'e özgüdür, map'in kendisine değil). Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::cout << m[\"a\"];"},
        .explanation = "map'in kendisinin .first üyesi yoktur; anahtar ile erişilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2215, .topicId = 84,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::map<std::string,int> m;\nm[\"a\"] = 1;\nif (m[\"b\"] == 1) { std::cout << \"var\"; }\n\nBu kod \"b\" anahtarının var olup olmadığını YANLIŞ kontrol eder çünkü m[\"b\"] okuması \"b\"'yi 0 değeriyle map'e EKLER (side effect); doğru kontrol .find() ile yapılmalıdır. Hatalı if satırını düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"if (m.find(\"b\") != m.end()) {"},
        .explanation = ".find() ile eklemeden kontrol edilir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2216, .topicId = 84,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nstd::map<std::string,int> m\nm[\"a\"] = 1;\n\nProgramcı m tanımının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"std::map<std::string, int> m;"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2217, .topicId = 84,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir map tanımlayıp bir değeri yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"std::cout << m[\"k\"];\n    return 0;\n}", "std::map<std::string,int> m;\n    m[\"k\"] = 42;", "int main() {"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "main açılışı (3), map tanımı+atama (2), yazdır+kapanış (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2218, .topicId = 84,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir std::string anahtar ve int değer tutan bir map tanımlayın; iki anahtar-değer çifti ekleyin ve for döngüsüyle tüm anahtar-değer çiftlerini ekrana yazdırın.",
        .acceptedAnswers = {"map", "first", "second"},
        .explanation = "map elemanları for döngüsünde .first/.second ile erişilen pair'lerdir.",
        .baseXp = 40,
    });
}
