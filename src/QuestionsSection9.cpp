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

    // Topic 85: unordered_map
    questions.push_back(Question{
        .id = 2219, .topicId = 85,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::unordered_map<K,V> ile std::map<K,V> arasındaki temel fark nedir?",
        .options = {"unordered_map anahtarları sıralı tutar, map tutmaz", "unordered_map anahtarları hash tablosunda sırasız tutar, map ise sıralı tutar", "unordered_map sadece int anahtarları destekler", "İkisi arasında fark yoktur"},
        .acceptedAnswers = {"b"},
        .explanation = "unordered_map hash tabanlıdır ve sıralama garantisi vermez; map sıralıdır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2220, .topicId = 85,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::unordered_map<std::string,int> m;\nm[\"a\"] = 5;\nstd::cout << m[\"a\"];\nEkran çıktısı nedir?",
        .options = {"0", "a", "5", "Derleme hatası"},
        .acceptedAnswers = {"c"},
        .explanation = "m[\"a\"], 5 değerini döndürür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2221, .topicId = 85,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::unordered_map, iç yapı olarak neyi kullanır?",
        .options = {"Sıralı bir ağaç (sorted tree)", "Bağlı liste (linked list)", "Dizi (array), sıralı tutar", "Hash tablosu (hash table)"},
        .acceptedAnswers = {"d"},
        .explanation = "unordered_map bir hash tablosu kullanır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2222, .topicId = 85,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::unordered_map<std::string,int> m;\nm[\"x\"]=1; m[\"y\"]=2; m[\"z\"]=3;\nfor (auto& kv : m) { ... }\nBu döngünün elemanları gezme sırası hakkında ne söylenebilir?",
        .options = {"Sıra tanımsızdır (implementation-defined); ekleme sırasıyla veya alfabetik sırayla eşleşeceği varsayılamaz", "Her zaman ekleme sırasıyla aynıdır", "Her zaman alfabetik sıradadır", "Her zaman ekleme sırasının tersidir"},
        .acceptedAnswers = {"a"},
        .explanation = "unordered_map iterasyon sırası implementation-defined'dır, hiçbir sıra varsayılamaz.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2223, .topicId = 85,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::unordered_map ile anahtar bazlı arama (.find()/operator[]) ortalama hangi sürede çalışır?",
        .options = {"O(n)", "O(1)", "O(log n)", "O(n^2)"},
        .acceptedAnswers = {"b"},
        .explanation = "Hash tabanlı arama ortalama O(1) sürer.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2224, .topicId = 85,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::map'te anahtar bazlı arama ortalama hangi sürede çalışır?",
        .options = {"O(1)", "O(n)", "O(log n)", "O(n^2)"},
        .acceptedAnswers = {"c"},
        .explanation = "map, dengeli bir ağaç kullandığından arama O(log n) sürer.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2225, .topicId = 85,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::unordered_map<std::string,int> m;\nm[\"a\"] = 1;\nstd::cout << m[\"b\"];\nstd::cout << \" \" << m.size();\nEkran çıktısı nedir?",
        .options = {"1 1", "Derleme hatası", "0 1", "0 2"},
        .acceptedAnswers = {"d"},
        .explanation = "m[\"b\"] okuması, map'teki ile aynı şekilde \"b\"'yi 0 ile ekler; size 2 olur.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2226, .topicId = 85,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "Sıralı gezinme (alfabetik/artan sırayla) gerektiren bir program için hangi konteyner tercih edilmelidir?",
        .options = {"std::map (sıralı garanti verir)", "std::unordered_map (daha hızlı olduğundan her zaman tercih edilir)", "İkisi de aynıdır, fark etmez", "std::unordered_map (sıralı garanti verir)"},
        .acceptedAnswers = {"a"},
        .explanation = "Sıralı gezinme garantisi gereken durumlarda std::map tercih edilmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2227, .topicId = 85,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::unordered_map, anahtarları bir hash tablosunda tutar.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2228, .topicId = 85,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::unordered_map, std::map gibi anahtarları sıralı (artan) tutar.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: unordered_map sıralama garantisi vermez.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2229, .topicId = 85,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::unordered_map üzerinde iterasyon sırası tanımsızdır (implementation-defined).",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2230, .topicId = 85,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::unordered_map'te anahtar bazlı erişim (operator[]/.find()), ortalama olarak std::map'ten daha YAVAŞTIR.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: unordered_map ortalama O(1), map ise O(log n) sürer; unordered_map genellikle daha hızlıdır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2231, .topicId = 85,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::unordered_map'in operator[]'i de, std::map gibi, olmayan bir anahtarı okurken onu otomatik olarak ekler.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2232, .topicId = 85,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Sıralı gezinme gerektiren bir uygulamada std::unordered_map, std::map'ten daha uygun bir seçimdir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: sıralama garantisi olmadığından std::map daha uygundur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2233, .topicId = 85,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Anahtarları bir hash tablosunda sırasız tutan STL konteynerine _____ denir (İngilizce iki kelime, alt çizgiyle).",
        .acceptedAnswers = {"unordered_map"},
        .explanation = "Bu konteynere unordered_map denir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2234, .topicId = 85,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::unordered_map<std::string,int> m;\nm[\"p\"] = 9;\nstd::cout << m[\"p\"];\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"9"},
        .explanation = "m[\"p\"], 9 değerini döndürür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2235, .topicId = 85,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "unordered_map'in iç yapısı bir _____ tablosudur (İngilizce kelime).",
        .acceptedAnswers = {"hash"},
        .explanation = "unordered_map bir hash tablosu kullanır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2236, .topicId = 85,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "unordered_map'te anahtar bazlı erişim ortalama _____ sürede çalışır (Büyük O gösterimi, örn. O(1)).",
        .acceptedAnswers = {"O(1)"},
        .explanation = "Hash tabanlı erişim ortalama O(1) sürer.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2237, .topicId = 85,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::map'te anahtar bazlı erişim ortalama _____ sürede çalışır (Büyük O gösterimi).",
        .acceptedAnswers = {"O(log n)"},
        .explanation = "Ağaç tabanlı erişim O(log n) sürer.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2238, .topicId = 85,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "unordered_map üzerinde iterasyon sırası _____ (Türkçe kelime, 'belirsiz/tanımsız' anlamında).",
        .acceptedAnswers = {"tanımsızdır", "tanımsız"},
        .explanation = "İterasyon sırası implementation-defined'dır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2239, .topicId = 85,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "_____\nm[\"kalem\"] = 3;\nm adlı bir std::string-int unordered_map tanımlayan satırı yazın.",
        .acceptedAnswers = {"std::unordered_map<std::string, int> m;"},
        .explanation = "unordered_map, hash tabanlı bir anahtar-değer konteyneridir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2240, .topicId = 85,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::unordered_map<std::string,int> m;\nm[\"a\"] = 1;\n_____\n\"a\" anahtarının değerini ekrana yazdıran satırı yazın.",
        .acceptedAnswers = {"std::cout << m[\"a\"];"},
        .explanation = "operator[] ile anahtarın değerine erişilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2241, .topicId = 85,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "std::unordered_map<std::string,int> m;\nm[\"x\"] = 4;\nm[\"y\"] = 6;\nstd::cout << m[\"x\"] + m[\"y\"];\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"10"},
        .explanation = "4 + 6 = 10.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2242, .topicId = 85,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "std::unordered_map<std::string,int> m;\nm[\"a\"] = 2;\nstd::cout << m.size() << \" \";\nm[\"b\"];\nstd::cout << m.size();\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"1 2"},
        .explanation = "İlk size 1; m[\"b\"] okuması \"b\"'yi ekler, size 2 olur.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2243, .topicId = 85,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::unordered_map<std::string,int> m;\nm[\"a\"] = 1;\nstd::cout << m.first;\n\nBu kod derlenmez çünkü std::unordered_map'in .first üye değişkeni yoktur (bu pair'e özgüdür, konteynerin kendisine değil). Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::cout << m[\"a\"];"},
        .explanation = "unordered_map'in kendisinin .first üyesi yoktur; anahtar ile erişilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2244, .topicId = 85,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::unordered_map<std::string,int> m;\nm[\"a\"] = 1;\nif (m[\"b\"] == 1) { std::cout << \"var\"; }\n\nBu kod \"b\" anahtarının var olup olmadığını YANLIŞ kontrol eder çünkü m[\"b\"] okuması \"b\"'yi 0 değeriyle map'e EKLER (side effect, std::map'teki ile aynı davranış); doğru kontrol .find() ile yapılmalıdır. Hatalı if satırını düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"if (m.find(\"b\") != m.end()) {"},
        .explanation = ".find() ile eklemeden kontrol edilir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2245, .topicId = 85,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nstd::unordered_map<std::string,int> m\nm[\"a\"] = 1;\n\nProgramcı m tanımının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"std::unordered_map<std::string, int> m;"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2246, .topicId = 85,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir unordered_map tanımlayıp bir değeri yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"std::cout << m[\"k\"];\n    return 0;\n}", "std::unordered_map<std::string,int> m;\n    m[\"k\"] = 8;", "int main() {"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "main açılışı (3), tanım+atama (2), yazdır+kapanış (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2247, .topicId = 85,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir std::string anahtar ve int değer tutan bir unordered_map tanımlayın; bir anahtar-değer çifti ekleyin ve o anahtarın değerini ekrana yazdırın.",
        .acceptedAnswers = {"unordered_map"},
        .explanation = "unordered_map, hash tabanlı bir anahtar-değer konteyneridir.",
        .baseXp = 40,
    });

    // Topic 86: stack
    questions.push_back(Question{
        .id = 2248, .topicId = 86,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::stack<T>'nin çalışma mantığı nedir?",
        .options = {"FIFO (ilk giren ilk çıkar)", "Elemanları sıralı (artan) tutar", "LIFO (son giren ilk çıkar)", "Elemanları hash tablosunda tutar"},
        .acceptedAnswers = {"c"},
        .explanation = "std::stack LIFO mantığıyla çalışır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2249, .topicId = 86,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::stack<int> s;\ns.push(1);\ns.push(2);\nstd::cout << s.top();\nEkran çıktısı nedir?",
        .options = {"1", "0", "Derleme hatası", "2"},
        .acceptedAnswers = {"d"},
        .explanation = "top(), en son eklenen (2) elemanı döndürür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2250, .topicId = 86,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::stack<int> s;\ns.push(1);\ns.push(2);\ns.pop();\nstd::cout << s.top();\nEkran çıktısı nedir?",
        .options = {"1", "2", "0", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "pop(), en üstteki (2) elemanı kaldırır; yeni tepe 1 olur.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2251, .topicId = 86,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::stack<int> s;\ns.push(5);\nfor (int x : s) { std::cout << x; }\nBu kod derlenir mi?",
        .options = {"Evet, çıktı 5'tir", "Hayır, std::stack'in begin()/end() tanımı yoktur, derleme hatası oluşur", "Evet ama çıktı boştur", "Evet, çıktı 0'dır"},
        .acceptedAnswers = {"b"},
        .explanation = "std::stack begin()/end() sunmaz, range-for derlenmez.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2252, .topicId = 86,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::stack<int> s;\ns.push(3); s.push(6); s.push(9);\nstd::cout << s.top();\ns.pop();\nstd::cout << \" \" << s.top();\ns.pop();\nstd::cout << \" \" << s.top();\nEkran çıktısı nedir?",
        .options = {"3 6 9", "9 9 9", "9 6 3", "Derleme hatası"},
        .acceptedAnswers = {"c"},
        .explanation = "LIFO sırayla en son eklenenden başlanarak: 9, 6, 3.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2253, .topicId = 86,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::stack, hangi konteyner tarafından desteklenen (varsayılan olarak) bir adaptördür?",
        .options = {"std::vector", "std::set", "std::map", "std::deque"},
        .acceptedAnswers = {"d"},
        .explanation = "std::stack'in varsayılan alttaki konteyneri std::deque'dur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2254, .topicId = 86,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::stack<int> s;\nstd::cout << s.empty();\ns.push(1);\nstd::cout << \" \" << s.empty();\nEkran çıktısı nedir?",
        .options = {"1 0", "0 1", "true false", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "İlk empty() true (1); push sonrası empty() false (0).",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2255, .topicId = 86,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::stack<int> s1;\ns1.push(1);\ns1.push(2);\nstd::stack<int> s2 = s1;\ns2.pop();\nstd::cout << s1.top() << \" \" << s2.top();\nEkran çıktısı nedir?",
        .options = {"1 2", "2 1", "2 2", "Derleme hatası"},
        .acceptedAnswers = {"b"},
        .explanation = "s2, s1'in bağımsız bir kopyasıdır; s2.pop() s1'i etkilemez.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2256, .topicId = 86,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::stack, LIFO (son giren ilk çıkar) mantığıyla çalışır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2257, .topicId = 86,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::stack, begin()/end() sunar ve for döngüsüyle doğrudan gezilebilir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: std::stack begin()/end() sunmaz.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2258, .topicId = 86,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::stack'te top(), en üstteki elemanı kaldırmadan döndürür.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2259, .topicId = 86,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::stack'te pop(), en üstteki elemanı döndürür.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: pop() void döndürür, sadece elemanı kaldırır; değere bakmak için top() kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2260, .topicId = 86,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::stack kopyalandığında, kopya bağımsız bir yığındır; birini değiştirmek diğerini etkilemez.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2261, .topicId = 86,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::stack, varsayılan olarak std::vector tarafından desteklenir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: varsayılan alttaki konteyner std::deque'dur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2262, .topicId = 86,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "LIFO (son giren ilk çıkar) mantığıyla çalışan konteyner adaptörüne _____ denir (İngilizce kelime).",
        .acceptedAnswers = {"stack"},
        .explanation = "Bu adaptöre stack denir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2263, .topicId = 86,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::stack<int> s;\ns.push(7);\nstd::cout << s.top();\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"7"},
        .explanation = "top(), en üstteki (7) elemanı döndürür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2264, .topicId = 86,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "stack'in en üstteki elemanını kaldıran (ama döndürmeyen) üye fonksiyon _____ dir (İngilizce kelime).",
        .acceptedAnswers = {"pop"},
        .explanation = "pop() kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2265, .topicId = 86,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::stack<int> s;\ns.push(1); s.push(2); s.push(3);\ns.pop();\nstd::cout << s.top();\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"2"},
        .explanation = "pop(), en üstteki (3) elemanı kaldırır; yeni tepe 2 olur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2266, .topicId = 86,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::stack'in begin()/end() tanımı olmadığından, elemanlarına sadece top()/pop() ile _____ erişilebilir (Türkçe kelime, 'teker teker/sırayla' anlamında).",
        .acceptedAnswers = {"sırayla"},
        .explanation = "Elemanlara sadece sırayla erişilebilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2267, .topicId = 86,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::stack, varsayılan olarak std::_____ tarafından desteklenir (İngilizce kelime).",
        .acceptedAnswers = {"deque"},
        .explanation = "Varsayılan alttaki konteyner std::deque'dur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2268, .topicId = 86,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "_____\ns.push(4);\ns adlı bir int stack'i tanımlayan satırı yazın.",
        .acceptedAnswers = {"std::stack<int> s;"},
        .explanation = "std::stack<int> ile bir int stack'i tanımlanır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2269, .topicId = 86,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::stack<int> s;\ns.push(1);\ns.push(2);\n_____\nyığının en üstteki elemanını ekrana yazdıran satırı yazın.",
        .acceptedAnswers = {"std::cout << s.top();"},
        .explanation = "top(), en üstteki elemanı döndürür.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2270, .topicId = 86,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "std::stack<int> s;\ns.push(2);\ns.push(4);\ns.push(6);\nstd::cout << s.top();\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"6"},
        .explanation = "En son eklenen (6), en üstte olur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2271, .topicId = 86,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "std::stack<int> s;\ns.push(1);\ns.push(2);\ns.push(3);\nint toplam = 0;\nwhile (!s.empty()) {\n    toplam += s.top();\n    s.pop();\n}\nstd::cout << toplam;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"6"},
        .explanation = "1 + 2 + 3 = 6 (sıra LIFO olsa da toplam aynıdır).",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2272, .topicId = 86,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::stack<int> s;\ns.push(5);\nfor (int x : s) { std::cout << x; }\n\nBu kod derlenmez çünkü std::stack'in begin()/end() tanımı yoktur. Hatalı satırı, top()/pop() kullanarak düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::cout << s.top();"},
        .explanation = "stack elemanlarına top()/pop() ile erişilir, iterasyonla değil.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2273, .topicId = 86,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::stack<int> s;\ns.push(3);\nint deger = s.pop();\n\nBu kod derlenmez çünkü std::stack::pop(), void döndürür (bir değer döndürmez); önce top() ile değere bakılıp SONRA pop() çağrılmalıdır. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"int deger = s.top();"},
        .explanation = "pop() void döndürür; değere top() ile bakılmalıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2274, .topicId = 86,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nstd::stack<int> s\ns.push(1);\n\nProgramcı s tanımının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"std::stack<int> s;"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2275, .topicId = 86,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir stack tanımlayıp en üstteki elemanı yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"std::cout << s.top();\n    return 0;\n}", "std::stack<int> s;\n    s.push(11);", "int main() {"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "main açılışı (3), tanım+push (2), yazdır+kapanış (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2276, .topicId = 86,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir int stack'i tanımlayın; üç değer push edin ve top()/pop() kullanarak elemanları LIFO sırayla (son eklenen ilk) ekrana yazdırın.",
        .acceptedAnswers = {"stack", "push", "pop"},
        .explanation = "stack, LIFO sırayla erişim sağlar.",
        .baseXp = 40,
    });

    // Topic 87: queue
    questions.push_back(Question{
        .id = 2277, .topicId = 87,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::queue<T>'nin çalışma mantığı nedir?",
        .options = {"LIFO (son giren ilk çıkar)", "Elemanları sıralı (artan) tutar", "Elemanları hash tablosunda tutar", "FIFO (ilk giren ilk çıkar)"},
        .acceptedAnswers = {"d"},
        .explanation = "std::queue FIFO mantığıyla çalışır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2278, .topicId = 87,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::queue<int> q;\nq.push(1);\nq.push(2);\nstd::cout << q.front();\nEkran çıktısı nedir?",
        .options = {"1", "2", "0", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "front(), en önce eklenen (1) elemanı döndürür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2279, .topicId = 87,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::queue<int> q;\nq.push(1);\nq.push(2);\nstd::cout << q.back();\nEkran çıktısı nedir?",
        .options = {"1", "2", "0", "Derleme hatası"},
        .acceptedAnswers = {"b"},
        .explanation = "back(), en son eklenen (2) elemanı döndürür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2280, .topicId = 87,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::queue<int> q;\nq.push(5);\nfor (int x : q) { std::cout << x; }\nBu kod derlenir mi?",
        .options = {"Evet, çıktı 5'tir", "Evet ama çıktı boştur", "Hayır, std::queue'nun begin()/end() tanımı yoktur, derleme hatası oluşur", "Evet, çıktı 0'dır"},
        .acceptedAnswers = {"c"},
        .explanation = "std::queue begin()/end() sunmaz, range-for derlenmez.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2281, .topicId = 87,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::queue<int> q;\nq.push(1); q.push(2); q.push(3);\nq.pop();\nstd::cout << q.front();\nEkran çıktısı nedir?",
        .options = {"1", "3", "0", "2"},
        .acceptedAnswers = {"d"},
        .explanation = "pop(), en öndeki (1) elemanı kaldırır; yeni ön 2 olur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2282, .topicId = 87,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::queue, hangi konteyner tarafından desteklenen (varsayılan olarak) bir adaptördür?",
        .options = {"std::deque", "std::vector", "std::set", "std::list"},
        .acceptedAnswers = {"a"},
        .explanation = "std::queue'nun varsayılan alttaki konteyneri std::deque'dur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2283, .topicId = 87,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::queue<int> q;\nq.push(1); q.push(2); q.push(3);\nstd::cout << q.front() << \" \" << q.back();\nEkran çıktısı nedir?",
        .options = {"3 1", "1 3", "1 1", "Derleme hatası"},
        .acceptedAnswers = {"b"},
        .explanation = "front() ilk eklenen (1), back() son eklenen (3) elemanı döndürür.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2284, .topicId = 87,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::queue<int> q1;\nq1.push(1);\nq1.push(2);\nstd::queue<int> q2 = q1;\nq2.pop();\nstd::cout << q1.front() << \" \" << q2.front();\nEkran çıktısı nedir?",
        .options = {"2 2", "1 1", "1 2", "Derleme hatası"},
        .acceptedAnswers = {"c"},
        .explanation = "q2, q1'in bağımsız bir kopyasıdır; q2.pop() q1'i etkilemez.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2285, .topicId = 87,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::queue, FIFO (ilk giren ilk çıkar) mantığıyla çalışır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2286, .topicId = 87,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::queue, begin()/end() sunar ve for döngüsüyle doğrudan gezilebilir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: std::queue begin()/end() sunmaz.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2287, .topicId = 87,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::queue'da front(), en öndeki elemana bakar (kaldırmaz).",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2288, .topicId = 87,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::queue'da back(), en öndeki elemana bakar.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: back(), en SONDAKİ elemana bakar.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2289, .topicId = 87,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::queue kopyalandığında, kopya bağımsız bir kuyruktur.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2290, .topicId = 87,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::queue, varsayılan olarak std::vector tarafından desteklenir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: varsayılan alttaki konteyner std::deque'dur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2291, .topicId = 87,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "FIFO (ilk giren ilk çıkar) mantığıyla çalışan konteyner adaptörüne _____ denir (İngilizce kelime).",
        .acceptedAnswers = {"queue"},
        .explanation = "Bu adaptöre queue denir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2292, .topicId = 87,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::queue<int> q;\nq.push(8);\nstd::cout << q.front();\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"8"},
        .explanation = "front(), tek eleman olan 8'i döndürür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2293, .topicId = 87,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "kuyruğun en öndeki elemanını kaldıran (ama döndürmeyen) üye fonksiyon _____ dir (İngilizce kelime).",
        .acceptedAnswers = {"pop"},
        .explanation = "pop() kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2294, .topicId = 87,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::queue<int> q;\nq.push(1); q.push(2); q.push(3);\nq.pop();\nq.pop();\nstd::cout << q.front();\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"3"},
        .explanation = "İki pop, 1 ve 2'yi sırayla kaldırır; kalan front 3'tür.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2295, .topicId = 87,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "kuyruğun en sondaki elemanına bakmak için kullanılan üye fonksiyon _____ dir (İngilizce kelime).",
        .acceptedAnswers = {"back"},
        .explanation = "back() kullanılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2296, .topicId = 87,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::queue, varsayılan olarak std::_____ tarafından desteklenir (İngilizce kelime).",
        .acceptedAnswers = {"deque"},
        .explanation = "Varsayılan alttaki konteyner std::deque'dur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2297, .topicId = 87,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "_____\nq.push(5);\nq adlı bir int kuyruğu tanımlayan satırı yazın.",
        .acceptedAnswers = {"std::queue<int> q;"},
        .explanation = "std::queue<int> ile bir int kuyruğu tanımlanır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2298, .topicId = 87,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::queue<int> q;\nq.push(1);\nq.push(2);\n_____\nkuyruğun en öndeki elemanını ekrana yazdıran satırı yazın.",
        .acceptedAnswers = {"std::cout << q.front();"},
        .explanation = "front(), en öndeki elemanı döndürür.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2299, .topicId = 87,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "std::queue<int> q;\nq.push(3);\nq.push(6);\nq.push(9);\nstd::cout << q.front();\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"3"},
        .explanation = "En önce eklenen (3), front olur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2300, .topicId = 87,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "std::queue<int> q;\nq.push(1);\nq.push(2);\nq.push(3);\nint toplam = 0;\nwhile (!q.empty()) {\n    toplam += q.front();\n    q.pop();\n}\nstd::cout << toplam;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"6"},
        .explanation = "1 + 2 + 3 = 6.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2301, .topicId = 87,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::queue<int> q;\nq.push(5);\nfor (int x : q) { std::cout << x; }\n\nBu kod derlenmez çünkü std::queue'nun begin()/end() tanımı yoktur. Hatalı satırı, front() kullanarak düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::cout << q.front();"},
        .explanation = "queue elemanlarına front()/pop() ile erişilir, iterasyonla değil.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2302, .topicId = 87,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::queue<int> q;\nq.push(3);\nint deger = q.pop();\n\nBu kod derlenmez çünkü std::queue::pop(), void döndürür (bir değer döndürmez); önce front() ile değere bakılıp SONRA pop() çağrılmalıdır. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"int deger = q.front();"},
        .explanation = "pop() void döndürür; değere front() ile bakılmalıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2303, .topicId = 87,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nstd::queue<int> q\nq.push(1);\n\nProgramcı q tanımının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"std::queue<int> q;"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2304, .topicId = 87,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir kuyruk tanımlayıp en öndeki elemanı yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"std::cout << q.front();\n    return 0;\n}", "std::queue<int> q;\n    q.push(13);", "int main() {"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "main açılışı (3), tanım+push (2), yazdır+kapanış (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2305, .topicId = 87,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir int kuyruğu tanımlayın; üç değer push edin ve front()/pop() kullanarak elemanları FIFO sırayla (ilk eklenen ilk) ekrana yazdırın.",
        .acceptedAnswers = {"queue", "push", "pop"},
        .explanation = "queue, FIFO sırayla erişim sağlar.",
        .baseXp = 40,
    });

    // Topic 88: deque
    questions.push_back(Question{
        .id = 2306, .topicId = 88,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::deque<T>'nin (double-ended queue) temel özelliği nedir?",
        .options = {"Hem başa hem sona ekleme/çıkarma yapılabilir, ayrıca tam iterasyon desteklenir", "Sadece sona ekleme yapılabilir", "Elemanları sıralı (artan) tutar", "Sadece başa ekleme yapılabilir"},
        .acceptedAnswers = {"a"},
        .explanation = "deque hem çift yönlü ekleme/çıkarma hem de tam iterasyon destekler.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2307, .topicId = 88,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::deque<int> d;\nd.push_back(1);\nd.push_back(2);\nd.push_front(0);\nfor (int x : d) { std::cout << x; }\nEkran çıktısı nedir?",
        .options = {"120", "012", "210", "Derleme hatası"},
        .acceptedAnswers = {"b"},
        .explanation = "push_back(1), push_back(2), push_front(0) sırasıyla [1],[1,2],[0,1,2] durumlarını üretir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2308, .topicId = 88,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::deque, begin()/end() sunar mı?",
        .options = {"Hayır, sadece stack/queue gibi push/pop sunar", "Sadece begin() sunar, end() sunmaz", "Evet, tam iterasyon desteklenir", "Sadece belirli koşullarda sunar"},
        .acceptedAnswers = {"c"},
        .explanation = "deque, begin()/end() ile tam iterasyon destekler.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2309, .topicId = 88,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::deque<int> d = {1,2,3};\nstd::cout << d[1];\nBu kod derlenir mi ve çıktısı nedir?",
        .options = {"Hayır, derleme hatası", "Evet, çıktı 1'dir", "Evet, çıktı 3'tür", "Evet, çıktı 2'dir"},
        .acceptedAnswers = {"d"},
        .explanation = "deque operator[] ile rastgele erişimi destekler; d[1] ikinci elemandır (2).",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2310, .topicId = 88,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::deque<int> d;\nd.push_back(5);\nd.push_back(10);\nd.pop_front();\nstd::cout << d.size();\nEkran çıktısı nedir?",
        .options = {"1", "2", "0", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "pop_front(), 5'i kaldırır; kalan tek eleman (10) size 1 yapar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2311, .topicId = 88,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::deque ile std::stack/std::queue arasındaki temel fark nedir?",
        .options = {"deque sadece tek yönlü ekleme yapar, stack/queue çift yönlü yapar", "deque hem çift yönlü ekleme/çıkarma yapar hem de iterasyona izin verir; stack/queue sadece belirli uçlara erişim sunar ve iterasyona izin vermez", "Aralarında fark yoktur", "stack/queue rastgele erişime izin verir, deque vermez"},
        .acceptedAnswers = {"b"},
        .explanation = "deque, stack/queue'nun aksine hem çift yönlü erişim hem de iterasyon sağlar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2312, .topicId = 88,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::deque<int> d;\nd.push_back(1);\nd.push_front(2);\nd.push_back(3);\nd.push_front(4);\nfor (int x : d) { std::cout << x; }\nEkran çıktısı nedir?",
        .options = {"1234", "4321", "4213", "Derleme hatası"},
        .acceptedAnswers = {"c"},
        .explanation = "Sırasıyla [1],[2,1],[2,1,3],[4,2,1,3] durumları oluşur.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2313, .topicId = 88,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::deque<int> d = {10,20,30};\nd.pop_back();\nd.pop_front();\nstd::cout << d.size() << \" \" << d[0];\nEkran çıktısı nedir?",
        .options = {"2 10", "2 20", "1 10", "1 20"},
        .acceptedAnswers = {"d"},
        .explanation = "pop_back() 30'u, pop_front() 10'u kaldırır; kalan {20}, size 1, d[0]=20.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2314, .topicId = 88,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::deque, hem başa hem sona ekleme/çıkarma destekler.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2315, .topicId = 88,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::deque, std::stack gibi begin()/end() sunmaz.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: deque begin()/end() sunar.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2316, .topicId = 88,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::deque, operator[] ile rastgele erişime (random access) izin verir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2317, .topicId = 88,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::deque, sadece sona ekleme (push_back) destekler, başa ekleme desteklemez.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: deque push_front() ile başa eklemeyi de destekler.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2318, .topicId = 88,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::deque üzerinde range-for döngüsüyle gezinmek mümkündür.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2319, .topicId = 88,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::deque, elemanları otomatik olarak sıralı (artan) tutar (std::set gibi).",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: deque elemanları ekleme sırasına göre tutar, otomatik sıralamaz.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2320, .topicId = 88,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Hem başa hem sona ekleme/çıkarma yapılabilen çift uçlu kuyruğa _____ denir (İngilizce kelime).",
        .acceptedAnswers = {"deque"},
        .explanation = "Bu yapıya deque denir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2321, .topicId = 88,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::deque<int> d;\nd.push_back(5);\nstd::cout << d[0];\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"5"},
        .explanation = "d[0], tek eleman olan 5'e erişir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2322, .topicId = 88,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "deque'nin başına eleman eklemek için kullanılan üye fonksiyon _____ dir (İngilizce iki kelime, alt çizgiyle).",
        .acceptedAnswers = {"push_front"},
        .explanation = "push_front() kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2323, .topicId = 88,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::deque<int> d;\nd.push_back(1);\nd.push_front(2);\nstd::cout << d[0] << d[1];\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"21"},
        .explanation = "push_front(2) sonrası deque [2,1] olur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2324, .topicId = 88,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "deque'nin sonundan eleman çıkarmak için kullanılan üye fonksiyon _____ dir (İngilizce iki kelime, alt çizgiyle).",
        .acceptedAnswers = {"pop_back"},
        .explanation = "pop_back() kullanılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2325, .topicId = 88,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::deque, hem push_back/push_front hem de operator[] ile _____ erişime izin verir (İngilizce iki kelime).",
        .acceptedAnswers = {"random access"},
        .explanation = "deque, random access destekler.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2326, .topicId = 88,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "_____\nd.push_back(1);\nd adlı bir int deque'si tanımlayan satırı yazın.",
        .acceptedAnswers = {"std::deque<int> d;"},
        .explanation = "std::deque<int> ile bir int deque'si tanımlanır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2327, .topicId = 88,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::deque<int> d;\nd.push_back(2);\n_____\nd'nin başına 1 ekleyen satırı yazın.",
        .acceptedAnswers = {"d.push_front(1);"},
        .explanation = "push_front(1), 1'i başa ekler.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2328, .topicId = 88,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "std::deque<int> d;\nd.push_back(7);\nd.push_back(8);\nd.push_front(6);\nfor (int x : d) { std::cout << x; }\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"678"},
        .explanation = "push_front(6), 6'yı başa ekler: [6,7,8].",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2329, .topicId = 88,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "std::deque<int> d = {1,2,3,4};\nd.pop_front();\nd.push_back(5);\nfor (int x : d) { std::cout << x; }\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"2345"},
        .explanation = "pop_front() 1'i kaldırır, push_back(5) 5'i ekler: [2,3,4,5].",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2330, .topicId = 88,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::deque<int> d;\nd.push_back(1);\nd.push_front(2);\nstd::cout << d.first;\n\nBu kod derlenmez çünkü std::deque'nin .first üye değişkeni yoktur (bu pair'e özgüdür). Hatalı satırı, deque'nin ilk elemanına doğru şekilde erişerek düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::cout << d[0];"},
        .explanation = "deque elemanlarına operator[] ile erişilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2331, .topicId = 88,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::deque<int> d;\nd.push_back(1);\nd.push(2);\n\nBu kod derlenmez çünkü std::deque'nin push() üye fonksiyonu yoktur (bu stack/queue'ya özgüdür); deque'de push_back()/push_front() kullanılır. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"d.push_back(2);"},
        .explanation = "deque'de push_back()/push_front() kullanılır, push() değil.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2332, .topicId = 88,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nstd::deque<int> d\nd.push_back(1);\n\nProgramcı d tanımının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"std::deque<int> d;"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2333, .topicId = 88,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir deque tanımlayıp elemanlarını yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"for (int x : d) { std::cout << x; }\n    return 0;\n}", "std::deque<int> d;\n    d.push_back(2);\n    d.push_front(1);", "int main() {"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "main açılışı (3), tanım+ekleme (2), döngü+kapanış (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2334, .topicId = 88,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir int deque'si tanımlayın; başa ve sona birer değer ekleyin (push_front/push_back) ve for döngüsüyle tüm elemanları ekrana yazdırın.",
        .acceptedAnswers = {"deque", "push_front", "push_back"},
        .explanation = "deque, hem başa hem sona ekleme ve tam iterasyon destekler.",
        .baseXp = 40,
    });

    // Topic 89: priority_queue
    questions.push_back(Question{
        .id = 2335, .topicId = 89,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::priority_queue<T>, varsayılan olarak nasıl davranır?",
        .options = {"Min-heap gibi davranır, en küçük elemanı verir", "Max-heap gibi davranır, en büyük elemanı verir", "FIFO sırayla davranır", "Elemanları ekleme sırasıyla verir"},
        .acceptedAnswers = {"b"},
        .explanation = "priority_queue varsayılan olarak max-heap gibi davranır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2336, .topicId = 89,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::priority_queue<int> pq;\npq.push(4);\npq.push(9);\npq.push(1);\nstd::cout << pq.top();\nEkran çıktısı nedir?",
        .options = {"4", "1", "9", "Derleme hatası"},
        .acceptedAnswers = {"c"},
        .explanation = "top(), varsayılan olarak en büyük elemanı (9) verir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2337, .topicId = 89,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::priority_queue'da top(), hangi elemanı verir?",
        .options = {"İlk eklenen elemanı", "Son eklenen elemanı", "En küçük elemanı (varsayılan olarak)", "En büyük elemanı (varsayılan olarak)"},
        .acceptedAnswers = {"d"},
        .explanation = "top(), varsayılan olarak en büyük elemanı verir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2338, .topicId = 89,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::priority_queue<int> pq;\npq.push(5);\npq.push(2);\npq.push(8);\npq.pop();\nstd::cout << pq.top();\nEkran çıktısı nedir?",
        .options = {"5", "2", "8", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "pop(), en büyük elemanı (8) kaldırır; kalan en büyük 5 olur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2339, .topicId = 89,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "Min-heap davranışı (en küçük elemanı top() ile almak) için ne kullanılmalıdır?",
        .options = {"std::priority_queue<T> (varsayılan haliyle)", "std::priority_queue<T, std::vector<T>, std::greater<T>>", "std::priority_queue<T, std::vector<T>, std::less<T>>", "std::stack<T>"},
        .acceptedAnswers = {"b"},
        .explanation = "std::greater<T> üçüncü şablon argümanı min-heap davranışı sağlar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2340, .topicId = 89,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::priority_queue, begin()/end() sunar mı?",
        .options = {"Evet, tam iterasyon desteklenir", "Sadece begin() sunar", "Hayır, stack/queue gibi iterasyon desteklemez", "Sadece end() sunar"},
        .acceptedAnswers = {"c"},
        .explanation = "priority_queue, diğer konteyner adaptörleri gibi iterasyon desteklemez.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2341, .topicId = 89,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::priority_queue<int> pq;\npq.push(3);\npq.push(7);\npq.push(1);\npq.push(9);\nstd::cout << pq.top();\npq.pop();\nstd::cout << \" \" << pq.top();\npq.pop();\nstd::cout << \" \" << pq.top();\nEkran çıktısı nedir?",
        .options = {"3 7 9", "1 3 7", "9 1 3", "9 7 3"},
        .acceptedAnswers = {"d"},
        .explanation = "top()/pop() sırasıyla en büyükten küçüğe doğru verir: 9, 7, 3.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2342, .topicId = 89,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::priority_queue<int, std::vector<int>, std::greater<int>> pq;\npq.push(5);\npq.push(1);\npq.push(9);\nstd::cout << pq.top();\nEkran çıktısı nedir?",
        .options = {"1", "9", "5", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "std::greater<int> ile min-heap davranışı: top() en küçüğü (1) verir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2343, .topicId = 89,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::priority_queue, varsayılan olarak bir max-heap gibi davranır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2344, .topicId = 89,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::priority_queue'da top(), varsayılan olarak en küçük elemanı verir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: varsayılan olarak en büyük elemanı verir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2345, .topicId = 89,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Min-heap davranışı için std::greater<T> üçüncü şablon argümanı olarak verilmelidir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2346, .topicId = 89,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::priority_queue, begin()/end() sunar ve iterasyona izin verir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: priority_queue iterasyon desteklemez.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2347, .topicId = 89,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::priority_queue'da pop(), en yüksek öncelikli (varsayılan olarak en büyük) elemanı kaldırır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2348, .topicId = 89,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::priority_queue, elemanları ekleme sırasında tutar.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: elemanlar öncelik sırasına (varsayılan olarak büyükten küçüğe) göre tutulur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2349, .topicId = 89,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Varsayılan olarak max-heap gibi davranan konteyner adaptörüne _____ denir (İngilizce iki kelime, alt çizgiyle).",
        .acceptedAnswers = {"priority_queue"},
        .explanation = "Bu adaptöre priority_queue denir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2350, .topicId = 89,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::priority_queue<int> pq;\npq.push(3);\npq.push(8);\nstd::cout << pq.top();\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"8"},
        .explanation = "top(), en büyük elemanı (8) verir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2351, .topicId = 89,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "priority_queue'da en yüksek öncelikli elemanı (kaldırmadan) döndüren üye fonksiyon _____ dir (İngilizce kelime).",
        .acceptedAnswers = {"top"},
        .explanation = "top() kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2352, .topicId = 89,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "Min-heap davranışı için üçüncü şablon argümanı olarak std::_____ kullanılır (İngilizce kelime).",
        .acceptedAnswers = {"greater"},
        .explanation = "std::greater<T> kullanılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2353, .topicId = 89,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::priority_queue<int> pq;\npq.push(2); pq.push(7); pq.push(4);\npq.pop();\nstd::cout << pq.top();\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"4"},
        .explanation = "pop(), en büyük (7) elemanı kaldırır; kalan en büyük 4 olur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2354, .topicId = 89,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "priority_queue, std::stack/std::queue gibi begin()/end() _____ (Türkçe kelime, 'sunmaz' anlamında).",
        .acceptedAnswers = {"sunmaz"},
        .explanation = "priority_queue iterasyon desteklemez.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2355, .topicId = 89,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "_____\npq.push(5);\npq adlı bir int priority_queue'su tanımlayan satırı yazın.",
        .acceptedAnswers = {"std::priority_queue<int> pq;"},
        .explanation = "std::priority_queue<int> ile tanımlanır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2356, .topicId = 89,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::priority_queue<int> pq;\npq.push(3);\npq.push(9);\n_____\nen büyük elemanı ekrana yazdıran satırı yazın.",
        .acceptedAnswers = {"std::cout << pq.top();"},
        .explanation = "top(), en büyük elemanı döndürür.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2357, .topicId = 89,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "std::priority_queue<int> pq;\npq.push(6);\npq.push(2);\npq.push(10);\nstd::cout << pq.top();\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"10"},
        .explanation = "top(), en büyük elemanı (10) verir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2358, .topicId = 89,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "std::priority_queue<int> pq;\npq.push(4);\npq.push(1);\npq.push(7);\nint toplam = 0;\nwhile (!pq.empty()) {\n    toplam += pq.top();\n    pq.pop();\n}\nstd::cout << toplam;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"12"},
        .explanation = "4 + 1 + 7 = 12.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2359, .topicId = 89,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::priority_queue<int> pq;\npq.push(3);\nfor (int x : pq) { std::cout << x; }\n\nBu kod derlenmez çünkü std::priority_queue'nun begin()/end() tanımı yoktur. Hatalı satırı, top() kullanarak düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::cout << pq.top();"},
        .explanation = "priority_queue elemanlarına top()/pop() ile erişilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2360, .topicId = 89,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::priority_queue<int> pq;\npq.push(5);\npq.push(1);\npq.push(9);\nstd::cout << pq.top();\n// Beklenen: en küçük eleman (1)\n\nBu kod, en küçük elemanı DEĞİL en büyük elemanı (9) verir çünkü std::priority_queue VARSAYILAN olarak max-heap'tir; min-heap için üçüncü şablon argümanı olarak std::greater<int> belirtilmelidir. Hatalı tanım satırını düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::priority_queue<int, std::vector<int>, std::greater<int>> pq;"},
        .explanation = "std::greater<int> ile min-heap davranışı elde edilir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2361, .topicId = 89,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nstd::priority_queue<int> pq\npq.push(5);\n\nProgramcı pq tanımının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"std::priority_queue<int> pq;"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2362, .topicId = 89,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir priority_queue tanımlayıp en büyük elemanı yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"std::cout << pq.top();\n    return 0;\n}", "std::priority_queue<int> pq;\n    pq.push(4);\n    pq.push(12);", "int main() {"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "main açılışı (3), tanım+ekleme (2), yazdır+kapanış (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2363, .topicId = 89,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir int priority_queue'su tanımlayın; üç değer push edin ve top()/pop() kullanarak elemanları büyükten küçüğe ekrana yazdırın.",
        .acceptedAnswers = {"priority_queue", "push", "pop"},
        .explanation = "priority_queue, varsayılan olarak büyükten küçüğe erişim sağlar.",
        .baseXp = 40,
    });

    // Topic 90: Iterator
    questions.push_back(Question{
        .id = 2364, .topicId = 90,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "Iterator (begin()/end()) kavramının amacı nedir?",
        .options = {"Bir konteyneri sıralamak", "Bir konteynerin boyutunu değiştirmek", "Herhangi bir STL konteynerini tek tip bir şekilde gezmenin (traverse etmenin) yolunu sağlamak", "Bir fonksiyonu virtual yapmak"},
        .acceptedAnswers = {"c"},
        .explanation = "Iterator'lar, konteynerleri tek tip bir şekilde gezmeyi sağlar.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2365, .topicId = 90,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::vector<int> v = {1,2,3};\nauto it = v.begin();\nstd::cout << *it;\nEkran çıktısı nedir?",
        .options = {"3", "0", "Derleme hatası", "1"},
        .acceptedAnswers = {"d"},
        .explanation = "begin(), ilk elemanı (1) gösterir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2366, .topicId = 90,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "v.end(), neyi gösterir?",
        .options = {"Son elemandan SONRAKİ (var olmayan) konumu", "Son elemanın kendisini", "İlk elemanı", "v'nin boyutunu"},
        .acceptedAnswers = {"a"},
        .explanation = "end(), son elemandan sonraki (var olmayan) konumu gösterir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2367, .topicId = 90,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "for (int x : v) döngüsü ile for (auto it = v.begin(); it != v.end(); ++it) döngüsü arasındaki ilişki nedir?",
        .options = {"Birbirinden tamamen farklı, farklı sonuçlar üretirler", "range-for, açık iterator döngüsünün kısa yazımıdır (syntactic sugar), aynı çıktıyı üretir", "range-for daha yavaş çalışır", "Sadece range-for derlenir, diğeri derlenmez"},
        .acceptedAnswers = {"b"},
        .explanation = "range-for, iterator döngüsünün syntactic sugar'ıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2368, .topicId = 90,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {5, 10, 15};\nauto it = v.begin();\n++it;\nstd::cout << *it;\nEkran çıktısı nedir?",
        .options = {"5", "15", "10", "Derleme hatası"},
        .acceptedAnswers = {"c"},
        .explanation = "begin() ilk elemanı (5) gösterir; ++it ikinci elemana (10) ilerler.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2369, .topicId = 90,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "*v.end() ifadesini okumaya çalışmak ne tür bir sorundur?",
        .options = {"Derleme hatasıdır", "Her zaman 0 döndürür", "Otomatik olarak son elemanı döndürür", "Tanımsız davranıştır (undefined behavior); derleme hatası DEĞİLDİR"},
        .acceptedAnswers = {"d"},
        .explanation = "*v.end(), tanımsız davranıştır; derleme hatası değildir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2370, .topicId = 90,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::vector<int> v = {1,2,3,4};\nint toplam = 0;\nfor (auto it = v.begin(); it != v.end(); ++it) {\n    toplam += *it;\n}\nstd::cout << toplam;\nEkran çıktısı nedir?",
        .options = {"10", "4", "0", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "1 + 2 + 3 + 4 = 10.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2371, .topicId = 90,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::vector<int> v = {2,4,6};\nfor (auto it = v.begin(); it != v.end(); ++it) { std::cout << *it; }\nfor (int x : v) { std::cout << x; }\nEkran çıktısı nedir?",
        .options = {"246642", "246246", "642642", "Derleme hatası"},
        .acceptedAnswers = {"b"},
        .explanation = "Her iki döngü de aynı sırayla aynı elemanları yazdırır: 246246.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2372, .topicId = 90,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Iterator'lar, STL konteynerlerini tek tip bir şekilde gezmenin yoludur.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2373, .topicId = 90,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "v.end(), konteynerin gerçek son elemanını gösterir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: end(), son elemandan sonraki (var olmayan) konumu gösterir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2374, .topicId = 90,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "range-for döngüsü, açık bir iterator döngüsünün kısa yazımıdır (syntactic sugar).",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2375, .topicId = 90,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "*v.end() ifadesini okumak bir derleme hatasıdır.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: derleme hatası değil, tanımsız davranıştır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2376, .topicId = 90,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Bir iterator'a ++ uygulamak, onu bir sonraki elemana ilerletir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2377, .topicId = 90,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "range-for döngüsü ve açık iterator döngüsü, aynı konteyner üzerinde FARKLI sırayla gezinir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: ikisi de aynı sırayla gezinir, çıktıları aynıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2378, .topicId = 90,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir konteynerin ilk elemanını gösteren iterator'ı döndüren üye fonksiyon _____ dir (İngilizce kelime).",
        .acceptedAnswers = {"begin"},
        .explanation = "begin() kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2379, .topicId = 90,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::vector<int> v = {7,8,9};\nauto it = v.begin();\nstd::cout << *it;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"7"},
        .explanation = "begin(), ilk elemanı (7) gösterir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2380, .topicId = 90,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "Bir iterator'ın gösterdiği elemana erişmek için kullanılan operatör _____ dir (bir sembol).",
        .acceptedAnswers = {"*"},
        .explanation = "Dereference operatörü (*) kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2381, .topicId = 90,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "Son elemandan SONRAKİ (var olmayan) konumu gösteren iterator'ı döndüren üye fonksiyon _____ dir (İngilizce kelime).",
        .acceptedAnswers = {"end"},
        .explanation = "end() kullanılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2382, .topicId = 90,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "*v.end() ile bu konumu okumaya çalışmak _____ davranıştır (Türkçe iki kelime, 'tanımsız davranış' anlamında).",
        .acceptedAnswers = {"tanımsız davranış", "tanımsız"},
        .explanation = "Bu, tanımsız davranıştır (UB).",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2383, .topicId = 90,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {3,6,9};\nauto it = v.begin();\n++it;\n++it;\nstd::cout << *it;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"9"},
        .explanation = "begin() -> 3, ++it -> 6, ++it -> 9.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2384, .topicId = 90,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "_____\nstd::cout << *it;\nv adlı bir vektörün ilk elemanını gösteren it adlı bir iterator tanımlayan satırı yazın.",
        .acceptedAnswers = {"auto it = v.begin();"},
        .explanation = "begin(), ilk elemanı gösteren iterator'ı döndürür.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2385, .topicId = 90,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {1,2,3};\nfor (auto it = v.begin(); it != v.end(); ++it) {\n_____\n}\nit'nin gösterdiği elemanı ekrana yazdıran satırı yazın.",
        .acceptedAnswers = {"std::cout << *it;"},
        .explanation = "*it, iterator'ın gösterdiği elemana erişir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2386, .topicId = 90,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {4,8,12};\nfor (auto it = v.begin(); it != v.end(); ++it) {\n    std::cout << *it << \" \";\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"4 8 12 "},
        .explanation = "Her eleman sırasıyla yazdırılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2387, .topicId = 90,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "std::vector<int> v = {1,2,3};\nint carpim = 1;\nfor (auto it = v.begin(); it != v.end(); ++it) {\n    carpim *= *it;\n}\nstd::cout << carpim;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"6"},
        .explanation = "1 * 2 * 3 = 6.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2388, .topicId = 90,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::vector<int> v = {1,2,3};\nstd::cout << *v.end();\n\nBu kod derlenir AMA tanımsız davranışa (undefined behavior) yol açar çünkü v.end(), gerçek bir elemanı göstermez (son elemandan bir sonraki konumdur); bu konumu dereference etmek TANIMSIZDIR. v'nin GERÇEK son elemanına erişen doğru satırı yazın.",
        .acceptedAnswers = {"std::cout << v.back();"},
        .explanation = "v.back(), konteynerin gerçek son elemanına erişir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2389, .topicId = 90,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::vector<int> v = {1,2,3};\nfor (auto it = v.begin(); it != v.end(); it) {\n    std::cout << *it;\n}\n\nBu kod SONSUZ DÖNGÜYE girer çünkü it, döngü içinde HİÇBİR ZAMAN artırılmıyor (++it eksik); it != v.end() koşulu hep doğru kalır. Hatalı for satırını düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"for (auto it = v.begin(); it != v.end(); ++it) {"},
        .explanation = "++it eklenmeden döngü asla sonlanmaz.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2390, .topicId = 90,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nstd::vector<int> v = {1,2,3};\nauto it = v.begin()\nstd::cout << *it;\n\nProgramcı it tanımının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"auto it = v.begin();"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2391, .topicId = 90,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir vektör tanımlayıp iterator ile ilk elemanını yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"auto it = v.begin();\n    std::cout << *it;\n    return 0;\n}", "std::vector<int> v = {5, 10, 15};", "int main() {"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "main açılışı (3), vektör tanımı (2), iterator+yazdır+kapanış (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2392, .topicId = 90,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir int vektörü tanımlayın; hem açık bir iterator döngüsüyle (begin()/end()) hem de bir range-for döngüsüyle tüm elemanlarını ekrana yazdırın.",
        .acceptedAnswers = {"begin", "end", "for"},
        .explanation = "İki döngü de aynı elemanları aynı sırayla yazdırır.",
        .baseXp = 40,
    });
}
