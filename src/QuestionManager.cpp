#include "QuestionManager.h"

#include <algorithm>

#include "QuestionContent.h"

QuestionManager::QuestionManager() {
    questions_.reserve(2102);

    // Topic 1: cout
    questions_.push_back(Question{
        .id = 1, .topicId = 1,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "Aşağıdakilerden hangisi ekrana yazı yazdırmak için kullanılır?",
        .options = {"cin", "cout", "endl", "return"},
        .acceptedAnswers = {"b"},
        .explanation = "cout, ekrana veri yazdırmak için kullanılan çıktı akışıdır; cin ise klavyeden veri okumak için kullanılır.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 2, .topicId = 1,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::cout << \"Merhaba\"; satırı hangi kütüphane olmadan derlenemez?",
        .options = {"<string>", "<vector>", "<iostream>", "<cmath>"},
        .acceptedAnswers = {"c"},
        .explanation = "cout, <iostream> kütüphanesinde tanımlıdır; bu kütüphane eklenmeden kullanılamaz.",
        .baseXp = 20,
    });
    questions_.push_back(Question{
        .id = 3, .topicId = 1,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "cout, kullanıcıdan klavyeden veri okumak için kullanılır.",
        .acceptedAnswers = {"2"},
        .explanation = "cout çıktı (ekrana yazdırma) içindir; veri okumak için cin kullanılır.",
        .baseXp = 5,
    });
    questions_.push_back(Question{
        .id = 4, .topicId = 1,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "cout kullanmak için <iostream> kütüphanesinin eklenmesi gerekir.",
        .acceptedAnswers = {"1"},
        .explanation = "cout, <iostream> kütüphanesinde tanımlıdır; kullanmak için bu kütüphane eklenmelidir.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 5, .topicId = 1,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::_____ << \"Merhaba\";",
        .acceptedAnswers = {"cout"},
        .explanation = "Ekrana yazdırmak için std::cout kullanılır.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 6, .topicId = 1,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "cout kullanmak için eklenmesi gereken kütüphane: #include <_____>",
        .acceptedAnswers = {"iostream"},
        .explanation = "cout, <iostream> kütüphanesinde tanımlıdır.",
        .baseXp = 20,
    });

    // Topic 2: \n
    questions_.push_back(Question{
        .id = 7, .topicId = 2,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "Aşağıdakilerden hangisi bir sonraki satıra geçmeyi sağlayan kaçış dizisidir?",
        .options = {"\\t", "\\n", "\\\\", "\\0"},
        .acceptedAnswers = {"b"},
        .explanation = "\\n, metin içinde yeni satıra geçişi sağlayan kaçış dizisidir; \\t ise yatay sekme (tab) boşluğu ekler.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 8, .topicId = 2,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::cout << \"A\\nB\"; ifadesinin ekran çıktısı nasıl görünür?",
        .options = {"A ve B aynı satırda yan yana", "Önce A, alt satırda B", "Sadece B yazılır", "Derleme hatası oluşur"},
        .acceptedAnswers = {"b"},
        .explanation = "\\n, A'dan sonra imleci yeni satıra taşır, bu yüzden B bir alt satırda görünür.",
        .baseXp = 20,
    });
    questions_.push_back(Question{
        .id = 9, .topicId = 2,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "\\n ifadesi çift tırnak içinde kullanılır.",
        .acceptedAnswers = {"1"},
        .explanation = "\\n bir dize (string) içinde, çift tırnaklar arasında yazılır.",
        .baseXp = 5,
    });
    questions_.push_back(Question{
        .id = 10, .topicId = 2,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "\\n kullanmak için ekstra bir kütüphane eklemek gerekir.",
        .acceptedAnswers = {"2"},
        .explanation = "\\n, dil düzeyinde bir kaçış dizisidir; başlı başına ekstra bir kütüphane istemez.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 11, .topicId = 2,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "Yeni satıra geçmek için kullanılan kaçış dizisinin harfi: \\_____ (ters slash zaten verilmiştir, sadece harfi yazınız)",
        .acceptedAnswers = {"n"},
        .explanation = "\\n, ters slash ve n harfinden oluşan, yeni satıra geçişi sağlayan kaçış dizisidir.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 12, .topicId = 2,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::cout << \"A_____B\"; kodunun çalışması sonucunda A ve B farklı satırlarda görünsün istiyorsunuz. Boşluğa (ters slash dahil, tam olarak) ne yazmalısınız?",
        .acceptedAnswers = {"\\n"},
        .explanation = "\\n, metin içinde yeni satıra geçişi sağlayan kaçış dizisidir.",
        .baseXp = 20,
    });

    // Topic 3: endl
    questions_.push_back(Question{
        .id = 13, .topicId = 3,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::endl ne işe yarar?",
        .options = {"Sadece metni büyük harfe çevirir", "Yeni satıra geçer ve çıktı tamponunu boşaltır", "Programı sonlandırır", "Bir sayıyı yuvarlar"},
        .acceptedAnswers = {"b"},
        .explanation = "endl, satırı bitirir ve ayrıca çıktı tamponunu (buffer) hemen boşaltır.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 14, .topicId = 3,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "\\n ile std::endl arasındaki temel fark nedir?",
        .options = {"Aralarında fark yoktur", "endl ayrıca çıktı tamponunu boşaltır (flush)", "\\n sadece sayılarda kullanılır", "endl yalnızca dosyalarda çalışır"},
        .acceptedAnswers = {"b"},
        .explanation = "endl, satırı bitirmenin yanında çıktı tamponunu da boşaltır; \\n bunu yapmaz.",
        .baseXp = 20,
    });
    questions_.push_back(Question{
        .id = 15, .topicId = 3,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::endl kullanmak için başında std:: öneki gereklidir (using namespace std; yoksa).",
        .acceptedAnswers = {"1"},
        .explanation = "using namespace std; kullanılmıyorsa endl için std:: öneki gerekir.",
        .baseXp = 5,
    });
    questions_.push_back(Question{
        .id = 16, .topicId = 3,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::endl, \\n'den daha hızlıdır çünkü tamponu boşaltmaz.",
        .acceptedAnswers = {"2"},
        .explanation = "Tam tersi: endl tamponu boşalttığı için \\n'den biraz daha yavaştır.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 17, .topicId = 3,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::cout << \"Merhaba\" << std::_____;",
        .acceptedAnswers = {"endl"},
        .explanation = "Satırı bitirip tamponu boşaltmak için std::endl kullanılır.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 18, .topicId = 3,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "endl kelimesi İngilizce 'end line' ifadesinin kısaltmasıdır ve satırı bitirmenin yanında çıktı ______'ini de boşaltır (İngilizce teknik terim).",
        .acceptedAnswers = {"buffer"},
        .explanation = "endl, çıktı tamponunu (buffer) hemen boşaltır (flush eder).",
        .baseXp = 20,
    });

    // Topic 4: cin
    questions_.push_back(Question{
        .id = 19, .topicId = 4,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "cin hangi işlem için kullanılır?",
        .options = {"Ekrana yazı yazdırmak", "Klavyeden veri okumak", "Dosya silmek", "Bir döngüyü durdurmak"},
        .acceptedAnswers = {"b"},
        .explanation = "cin, klavyeden veri okumak için kullanılan giriş akışıdır.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 20, .topicId = 4,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "cin ile bir int değişkenine değer okurken hangi operatör kullanılır?",
        .options = {"<<", "+=", "==", ">>"},
        .acceptedAnswers = {"d"},
        .explanation = "cin ile okuma yaparken >> operatörü kullanılır.",
        .baseXp = 20,
    });
    questions_.push_back(Question{
        .id = 21, .topicId = 4,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "cin, kullanıcıdan klavye aracılığıyla veri almak için kullanılır.",
        .acceptedAnswers = {"1"},
        .explanation = "cin, klavyeden veri okumak için kullanılan giriş akışıdır.",
        .baseXp = 5,
    });
    questions_.push_back(Question{
        .id = 22, .topicId = 4,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "cin, boşluk içeren tüm bir cümleyi tek seferde okuyabilir.",
        .acceptedAnswers = {"2"},
        .explanation = "cin >> yalnızca ilk boşluğa kadar olan kısmı okur; tam bir cümle için getline() kullanılmalıdır.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 23, .topicId = 4,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int yas;\nstd::_____ >> yas;",
        .acceptedAnswers = {"cin"},
        .explanation = "Klavyeden okumak için std::cin kullanılır.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 24, .topicId = 4,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "Klavyeden bir değeri bir değişkene aktarmak için cin ile birlikte kullanılan operatör: __ (iki karakter)",
        .acceptedAnswers = {">>"},
        .explanation = "cin ile okuma yaparken >> operatörü kullanılır.",
        .baseXp = 20,
    });

    // Topic 5: getline()
    questions_.push_back(Question{
        .id = 25, .topicId = 5,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "getline() fonksiyonu ne işe yarar?",
        .options = {"Sadece tek bir karakter okur", "Boşluk içeren tüm bir satırı okur", "Bir dosyayı siler", "Bir sayıyı yuvarlar"},
        .acceptedAnswers = {"b"},
        .explanation = "getline(), boşluklar dahil tüm bir satırı okur.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 26, .topicId = 5,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::getline(std::cin, isim); satırında isim değişkeninin türü ne olmalıdır?",
        .options = {"int", "double", "std::string", "bool"},
        .acceptedAnswers = {"c"},
        .explanation = "getline(), sonucu bir std::string değişkenine yazar.",
        .baseXp = 20,
    });
    questions_.push_back(Question{
        .id = 27, .topicId = 5,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "getline() kullanmak için <string> kütüphanesinin eklenmesi gerekir.",
        .acceptedAnswers = {"1"},
        .explanation = "getline() ve std::string, <string> kütüphanesinde tanımlıdır.",
        .baseXp = 5,
    });
    questions_.push_back(Question{
        .id = 28, .topicId = 5,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "cin >> ile getline() tamamen aynı şekilde çalışır.",
        .acceptedAnswers = {"2"},
        .explanation = "cin >> ilk boşluğa kadar okur, getline() ise boşluklar dahil tüm satırı okur.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 29, .topicId = 5,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::string isim;\nstd::_____(std::cin, isim);",
        .acceptedAnswers = {"getline"},
        .explanation = "Boşluklu bir satırı okumak için std::getline kullanılır.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 30, .topicId = 5,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "getline fonksiyonunun ilk parametresi genellikle _____ olur (giriş akışının adı).",
        .acceptedAnswers = {"cin"},
        .explanation = "getline(std::cin, degisken); şeklinde ilk parametre giriş akışıdır.",
        .baseXp = 20,
    });

    // Topic 6: int
    questions_.push_back(Question{
        .id = 31, .topicId = 6,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "Aşağıdakilerden hangisi tam sayı değerleri saklamak için kullanılan veri türüdür?",
        .options = {"char", "int", "bool", "string"},
        .acceptedAnswers = {"b"},
        .explanation = "int, tam sayı (ondalıksız) değerleri saklamak için kullanılan veri türüdür.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 32, .topicId = 6,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int yas = 25; satırında yas değişkenine hangi tür değer atanabilir?",
        .options = {"Sadece ondalık sayılar", "Sadece metinler", "Tam sayılar", "Sadece true/false değerleri"},
        .acceptedAnswers = {"c"},
        .explanation = "int, tam sayı değerleri saklar.",
        .baseXp = 20,
    });
    questions_.push_back(Question{
        .id = 33, .topicId = 6,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "int veri türü, ondalıklı sayıları tam olarak saklayabilir.",
        .acceptedAnswers = {"2"},
        .explanation = "int yalnızca tam sayıları saklar; ondalıklı sayılar için double kullanılır.",
        .baseXp = 5,
    });
    questions_.push_back(Question{
        .id = 34, .topicId = 6,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "int sayi = 5; satırı geçerli bir C++ tanımlamasıdır.",
        .acceptedAnswers = {"1"},
        .explanation = "Bu, geçerli bir int değişken tanımlama ve atama işlemidir.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 35, .topicId = 6,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "_____ sayi = 5; (tam sayı türü)",
        .acceptedAnswers = {"int"},
        .explanation = "Tam sayılar için int veri türü kullanılır.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 36, .topicId = 6,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int sayi = 7.9; satırı çalıştırıldığında sayi değişkeninde saklanan değer kaç olur (ondalık kısım atılarak)?",
        .acceptedAnswers = {"7"},
        .explanation = "int, ondalık kısmı saklamaz; 7.9 değeri 7 olarak kesilir.",
        .baseXp = 20,
    });

    // Topic 7: double
    questions_.push_back(Question{
        .id = 37, .topicId = 7,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "Ondalıklı (kesirli) sayıları saklamak için hangi veri türü kullanılır?",
        .options = {"int", "char", "double", "bool"},
        .acceptedAnswers = {"c"},
        .explanation = "double, ondalıklı sayıları saklamak için kullanılan veri türüdür.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 38, .topicId = 7,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "double fiyat = 19.99; satırında ondalık ayıracı olarak ne kullanılmalıdır?",
        .options = {"Virgül (,)", "Nokta (.)", "İki nokta (:)", "Yıldız (*)"},
        .acceptedAnswers = {"b"},
        .explanation = "C++'ta ondalık ayıracı nokta (.) işaretidir.",
        .baseXp = 20,
    });
    questions_.push_back(Question{
        .id = 39, .topicId = 7,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "double veri türü, ondalıklı sayıları saklayabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "double, ondalıklı (kesirli) sayıları saklamak için kullanılır.",
        .baseXp = 5,
    });
    questions_.push_back(Question{
        .id = 40, .topicId = 7,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "double bir değişkene tam sayı atanamaz.",
        .acceptedAnswers = {"2"},
        .explanation = "double bir değişkene tam sayı da atanabilir; sayı otomatik olarak ondalıklı forma çevrilir (örn. 5 -> 5.0).",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 41, .topicId = 7,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "_____ fiyat = 19.99; (ondalıklı sayı türü)",
        .acceptedAnswers = {"double"},
        .explanation = "Ondalıklı sayılar için double veri türü kullanılır.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 42, .topicId = 7,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "double sayi1 = 3.5;\ndouble sayi2 = 2.5;\nstd::cout << sayi1 + sayi2;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"6", "6.0"},
        .explanation = "3.5 ile 2.5 toplanınca 6.0 elde edilir; cout bunu sondaki sıfırları göstermeden 6 olarak yazdırır.",
        .baseXp = 20,
    });

    // Topic 8: char
    questions_.push_back(Question{
        .id = 43, .topicId = 8,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "Tek bir karakteri saklamak için hangi veri türü kullanılır?",
        .options = {"string", "char", "int", "double"},
        .acceptedAnswers = {"b"},
        .explanation = "char, tek bir karakteri saklamak için kullanılan veri türüdür.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 44, .topicId = 8,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "char harf = 'A'; satırında 'A' değerinin etrafında hangi işaret kullanılmalıdır?",
        .options = {"Çift tırnak (\")", "Tek tırnak (')", "Köşeli parantez ([])", "Süslü parantez ({})"},
        .acceptedAnswers = {"b"},
        .explanation = "char değerleri tek tırnak (') içinde yazılır.",
        .baseXp = 20,
    });
    questions_.push_back(Question{
        .id = 45, .topicId = 8,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "char veri türü yalnızca tek bir karakter saklayabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "char, tek bir karakter saklamak için tasarlanmıştır.",
        .baseXp = 5,
    });
    questions_.push_back(Question{
        .id = 46, .topicId = 8,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "char harf = \"A\"; şeklindeki tanımlama (çift tırnaklı) doğrudur.",
        .acceptedAnswers = {"2"},
        .explanation = "char için tek tırnak ('A') kullanılmalıdır; çift tırnak string ifade eder.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 47, .topicId = 8,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "_____ harf = 'A'; (tek karakter türü)",
        .acceptedAnswers = {"char"},
        .explanation = "Tek bir karakter için char veri türü kullanılır.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 48, .topicId = 8,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "Bir char değişkenine değer atarken kullanılması gereken tırnak türü: _____ tırnak (örnek: tek/çift)",
        .acceptedAnswers = {"tek"},
        .explanation = "char değerleri tek tırnak (') içinde yazılır; çift tırnak (\") string ifade eder.",
        .baseXp = 20,
    });

    // Topic 9: bool
    questions_.push_back(Question{
        .id = 49, .topicId = 9,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "bool veri türü hangi iki değerden birini alabilir?",
        .options = {"0 ve 100", "true ve false", "A ve B", "int ve double"},
        .acceptedAnswers = {"b"},
        .explanation = "bool, true (doğru) veya false (yanlış) değerlerinden birini saklar.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 50, .topicId = 9,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::cout << true; ifadesi ekrana ne yazdırır?",
        .options = {"true", "1", "doğru", "evet"},
        .acceptedAnswers = {"b"},
        .explanation = "cout, varsayılan olarak true değerini 1 olarak yazdırır.",
        .baseXp = 20,
    });
    questions_.push_back(Question{
        .id = 51, .topicId = 9,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "bool veri türü yalnızca true veya false değerlerini saklar.",
        .acceptedAnswers = {"1"},
        .explanation = "bool, yalnızca true veya false değerlerinden birini saklar.",
        .baseXp = 5,
    });
    questions_.push_back(Question{
        .id = 52, .topicId = 9,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "cout ile bir bool değişken yazdırıldığında ekranda \"true\" veya \"false\" kelimeleri görünür.",
        .acceptedAnswers = {"2"},
        .explanation = "Varsayılan olarak cout, bool değerlerini true için 1, false için 0 şeklinde yazdırır.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 53, .topicId = 9,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "_____ aktif = true; (mantıksal veri türü)",
        .acceptedAnswers = {"bool"},
        .explanation = "Mantıksal (true/false) değerler için bool veri türü kullanılır.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 54, .topicId = 9,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::cout << false; ifadesinin ekran çıktısı: _____ (rakam)",
        .acceptedAnswers = {"0"},
        .explanation = "cout, false değerini 0 olarak yazdırır.",
        .baseXp = 20,
    });

    // Topic 10: const
    questions_.push_back(Question{
        .id = 55, .topicId = 10,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "const anahtar kelimesi ne işe yarar?",
        .options = {"Bir döngüyü sonlandırır", "Bir değişkenin değerinin değiştirilmesini engeller", "Bir fonksiyonu siler", "Bir dosyayı açar"},
        .acceptedAnswers = {"b"},
        .explanation = "const, bir değişkenin değerinin tanımlandıktan sonra değiştirilemeyeceğini belirtir.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 56, .topicId = 10,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "const int MAKS = 100; tanımlandıktan sonra MAKS = 200; satırı çalıştırılırsa ne olur?",
        .options = {"Program çalışır, MAKS 200 olur", "Derleme hatası oluşur", "MAKS otomatik olarak 300 olur", "Hiçbir şey olmaz, satır yok sayılır"},
        .acceptedAnswers = {"b"},
        .explanation = "const bir değişkene yeniden değer atamaya çalışmak derleme hatasına yol açar.",
        .baseXp = 20,
    });
    questions_.push_back(Question{
        .id = 57, .topicId = 10,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "const olarak tanımlanan bir değişkenin değeri sonradan değiştirilebilir.",
        .acceptedAnswers = {"2"},
        .explanation = "const bir değişkenin değeri tanımlandıktan sonra değiştirilemez.",
        .baseXp = 5,
    });
    questions_.push_back(Question{
        .id = 58, .topicId = 10,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "const bir değişken tanımlanırken başlangıç değeri verilmesi gerekir.",
        .acceptedAnswers = {"1"},
        .explanation = "const değişkenler tanımlandığı anda bir başlangıç değeri almalıdır.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 59, .topicId = 10,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "_____ double PI = 3.14; (değeri değiştirilemeyen anlamına gelen anahtar kelime)",
        .acceptedAnswers = {"const"},
        .explanation = "Değeri değiştirilemeyen değişkenler için const kullanılır.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 60, .topicId = 10,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "const int X = 5;\nX = 10;\nYukarıdaki ikinci satır çalıştırılmaya çalışıldığında ne oluşur? (Türkçe kelime: hata/uyarı)",
        .acceptedAnswers = {"hata"},
        .explanation = "const olarak tanımlanmış bir değişkene yeniden değer atamaya çalışmak derleme hatasına yol açar.",
        .baseXp = 20,
    });

    // Phase 3: richer question types (ids 61-72)

    questions_.push_back(Question{
        .id = 61, .topicId = 6,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Easy,
        .prompt = "int toplam = 10;\ntoplam = ______;\ncout << toplam;\nYukarıdaki kodun çalışması sonucunda toplam değişkeninin 15 olması isteniyor. toplam değişkenini kullanarak boşluğa ne yazılmalı?",
        .acceptedAnswers = {"toplam + 5", "toplam+5"},
        .explanation = "toplam değişkenine 5 eklenirse (toplam + 5), 10 + 5 = 15 elde edilir.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 62, .topicId = 4,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int a;\nint b;\ncin >> a >> ______;\nİki değişkeni tek satırda okumak istiyorsunuz. Boşluğa ne yazılmalı?",
        .acceptedAnswers = {"b"},
        .explanation = "cin >> a >> b; şeklinde birden fazla değişken art arda >> ile okunabilir.",
        .baseXp = 20,
    });
    questions_.push_back(Question{
        .id = 63, .topicId = 6,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Easy,
        .prompt = "int sayi = 5;\nsayi = sayi + 3;\nstd::cout << sayi;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"8"},
        .explanation = "sayi başlangıçta 5'tir; sayi + 3 işlemiyle 8 olur ve ekrana 8 yazdırılır.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 64, .topicId = 9,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "bool durum = false;\nstd::cout << durum;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"0"},
        .explanation = "cout, bool değerlerini varsayılan olarak 1 (true) veya 0 (false) şeklinde yazdırır.",
        .baseXp = 20,
    });
    questions_.push_back(Question{
        .id = 65, .topicId = 1,
        .type = QuestionType::FindError, .difficulty = Difficulty::Easy,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint yas = 20\n\nstd::cout << yas;\n\nHatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"int yas = 20;"},
        .explanation = "int yas = 20 satırının sonunda noktalı virgül (;) eksik; doğrusu int yas = 20; şeklindedir.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 66, .topicId = 8,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nchar harf = \"A\";\nstd::cout << harf;\n\nHatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"char harf = 'A';"},
        .explanation = "char için çift tırnak değil tek tırnak kullanılmalıdır; doğrusu char harf = 'A'; şeklindedir.",
        .baseXp = 20,
    });
    questions_.push_back(Question{
        .id = 67, .topicId = 7,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodu düzeltin:\n\ndouble ortalama = 87,5;\nstd::cout << ortalama;\n\nDüzeltilmiş ilk satırı yazın.",
        .acceptedAnswers = {"double ortalama = 87.5;"},
        .explanation = "C++'ta ondalık ayıracı virgül değil noktadır; doğrusu double ortalama = 87.5; şeklindedir.",
        .baseXp = 20,
    });
    questions_.push_back(Question{
        .id = 68, .topicId = 4,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nint yas;\ncin > yas;\n\nDüzeltilmiş ikinci satırı yazın.",
        .acceptedAnswers = {"cin >> yas;"},
        .explanation = "cin ile okuma yaparken tek > değil çift >> operatörü kullanılmalıdır; doğrusu cin >> yas; şeklindedir.",
        .baseXp = 20,
    });
    questions_.push_back(Question{
        .id = 69, .topicId = 4,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Easy,
        .prompt = "Aşağıdaki satırları geçerli ve mantıklı bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın, örnek: 1 2 3):",
        .options = {"cout << yas;", "int yas;", "cin >> yas;"},
        .acceptedAnswers = {"2 3 1"},
        .explanation = "Önce değişken tanımlanır (int yas;), sonra değer okunur (cin >> yas;), en son yazdırılır (cout << yas;): sıra 2 3 1.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 70, .topicId = 1,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları geçerli bir C++ programı oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"return 0;", "std::cout << \"Merhaba\";", "int main() {", "}"},
        .acceptedAnswers = {"3 2 1 4"},
        .explanation = "Program int main() { ile başlar, içinde yazdırma ve return 0; yer alır, } ile kapanır: sıra 3 2 1 4.",
        .baseXp = 20,
    });
    questions_.push_back(Question{
        .id = 71, .topicId = 6,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Kullanıcıdan bir tam sayı okuyup ekrana yazdıran bir program yazın. (Kodunuzu birden fazla satırda yazabilirsiniz.)",
        .acceptedAnswers = {"cin", ">>", "cout", "<<"},
        .explanation = "Program bir tam sayıyı cin >> ile okumalı ve cout << ile ekrana yazdırmalıdır.",
        .baseXp = 40,
    });
    questions_.push_back(Question{
        .id = 72, .topicId = 10,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "PI için 3.14 değerinde, değeri değiştirilemeyen bir sabit tanımlayıp ekrana yazdıran bir program yazın.",
        .acceptedAnswers = {"const", "cout", "<<", "3.14"},
        .explanation = "Değeri değiştirilemeyen bir değişken const ile tanımlanır ve cout << ile ekrana yazdırılır.",
        .baseXp = 40,
    });

    appendSection2Questions(questions_);
    appendSection3Questions(questions_);
    appendSection4Questions(questions_);
    appendSection5Questions(questions_);
    appendSection6Questions(questions_);
    appendSection7Questions(questions_);
    appendSection8Questions(questions_);
}

std::vector<Question> QuestionManager::questionsForTopic(int topicId) const {
    std::vector<Question> result;
    for (const Question& question : questions_) {
        if (question.topicId == topicId) {
            result.push_back(question);
        }
    }
    return result;
}

std::optional<Question> QuestionManager::findById(int questionId) const {
    const auto it = std::ranges::find_if(
        questions_, [questionId](const Question& question) { return question.id == questionId; });
    if (it == questions_.end()) {
        return std::nullopt;
    }
    return *it;
}
