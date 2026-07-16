#include "QuestionContent.h"

#include "Question.h"

void appendSection2Questions(std::vector<Question>& questions) {
    // Topic 11: Matematiksel operatörler
    questions.push_back(Question{
        .id = 73, .topicId = 11,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "5 + 3 işleminin sonucu kaçtır?",
        .options = {"7", "8", "9", "15"},
        .acceptedAnswers = {"b"},
        .explanation = "5 + 3 toplamı 8'e eşittir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 74, .topicId = 11,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "10 - 4 * 2 işleminin sonucu kaçtır?",
        .options = {"12", "2", "6", "20"},
        .acceptedAnswers = {"b"},
        .explanation = "Önce çarpma yapılır (4 * 2 = 8), sonra çıkarma yapılır (10 - 8 = 2).",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 75, .topicId = 11,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "İki int değişken bölündüğünde (örneğin 7 / 2) sonuç ne tür olur?",
        .options = {"Ondalıklı (3.5)", "Tam sayı, ondalık atılır (3)", "Hata verir", "Her zaman 0"},
        .acceptedAnswers = {"b"},
        .explanation = "İki tam sayı bölündüğünde sonuç da tam sayıdır; ondalık kısım atılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 76, .topicId = 11,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int a = 9; int b = 4; ifadesinde a / b işleminin sonucu kaçtır?",
        .options = {"2", "2.25", "3", "1"},
        .acceptedAnswers = {"a"},
        .explanation = "9 / 4, tam sayı bölmesiyle 2 eder (2.25 değil, ondalık kısım atılır).",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 77, .topicId = 11,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "2 + 3 * 4 - 1 işleminin sonucu kaçtır?",
        .options = {"13", "19", "24", "9"},
        .acceptedAnswers = {"a"},
        .explanation = "Önce 3 * 4 = 12 hesaplanır, sonra 2 + 12 - 1 = 13 bulunur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 78, .topicId = 11,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "(2 + 3) * 4 işleminin sonucu kaçtır?",
        .options = {"14", "20", "9", "24"},
        .acceptedAnswers = {"b"},
        .explanation = "Parantez içi önce hesaplanır (2 + 3 = 5), sonra 5 * 4 = 20 bulunur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 79, .topicId = 11,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int x = 7; int y = 2; double sonuc = x / y; ifadesinden sonra sonuc değişkeninin değeri kaçtır?",
        .options = {"3.5", "3", "4", "Derleme hatası"},
        .acceptedAnswers = {"b"},
        .explanation = "x / y önce int bölmesi olarak hesaplanır (3 olur), ardından double'a atanır; sonuç 3.5 değil 3'tür.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 80, .topicId = 11,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int a = -7; int b = 2; a / b işleminin sonucu (C++11 ve sonrası standartlara göre) kaçtır?",
        .options = {"-4", "-3", "-3.5", "3"},
        .acceptedAnswers = {"b"},
        .explanation = "C++11'den itibaren tam sayı bölmesi sıfıra doğru yuvarlanır; -7 / 2 sonucu -3.5 değil -3'tür.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 81, .topicId = 11,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "C++'ta * operatörü çarpma işlemi için kullanılır.",
        .acceptedAnswers = {"1"},
        .explanation = "* operatörü iki sayıyı çarpar.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 82, .topicId = 11,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "C++'ta iki tam sayının bölümü her zaman ondalıklı bir sonuç verir.",
        .acceptedAnswers = {"2"},
        .explanation = "İki tam sayının bölümü tam sayı sonucu verir; ondalık kısım atılır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 83, .topicId = 11,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Operatör önceliğine göre çarpma ve bölme, toplama ve çıkarmadan önce yapılır.",
        .acceptedAnswers = {"1"},
        .explanation = "Matematikteki gibi, * ve / işlemleri + ve -'den önce değerlendirilir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 84, .topicId = 11,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Parantez kullanmak, operatör önceliğini değiştirebilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Parantez içindeki ifadeler her zaman önce hesaplanır, bu da önceliği değiştirebilir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 85, .topicId = 11,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "int a = 5; int b = 2; double c = a / b; ifadesinde c'nin değeri 2.5'tir.",
        .acceptedAnswers = {"2"},
        .explanation = "a / b önce int bölmesi olarak hesaplanır (2 olur), sonra double'a atanır; c'nin değeri 2.5 değil 2.0'dır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 86, .topicId = 11,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "C++'ta operatör önceliği matematikteki sıraya (çarpma/bölme önce, toplama/çıkarma sonra) benzer şekilde çalışır.",
        .acceptedAnswers = {"1"},
        .explanation = "C++'ın operatör önceliği kuralları matematikteki geleneksel sırayı takip eder.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 87, .topicId = 11,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int sonuc = 6 _____ 3; ifadesinin sonucu 2 olsun istiyorsunuz. Boşluğa hangi operatör yazılmalı?",
        .acceptedAnswers = {"/"},
        .explanation = "6 / 3 = 2 olduğu için bölme operatörü kullanılmalıdır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 88, .topicId = 11,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int sonuc = 4 _____ 5; ifadesinin sonucu 20 olsun istiyorsunuz. Boşluğa hangi operatör yazılmalı?",
        .acceptedAnswers = {"*"},
        .explanation = "4 * 5 = 20 olduğu için çarpma operatörü kullanılmalıdır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 89, .topicId = 11,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int sonuc = 10 _____ 3; ifadesinin sonucu 7 olsun istiyorsunuz. Boşluğa hangi operatör yazılmalı?",
        .acceptedAnswers = {"-"},
        .explanation = "10 - 3 = 7 olduğu için çıkarma operatörü kullanılmalıdır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 90, .topicId = 11,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int a = 8; int b = 3; int sonuc = a _____ b; ifadesinin sonucu 2 olsun istiyorsunuz (tam sayı bölmesiyle). Boşluğa hangi operatör yazılmalı?",
        .acceptedAnswers = {"/"},
        .explanation = "8 / 3, tam sayı bölmesiyle 2 eder (ondalık kısım atılır).",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 91, .topicId = 11,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int sonuc = 2 + 3 _____ 4; ifadesinin sonucu 14 olması için boşluğa hangi operatör yazılmalı?",
        .acceptedAnswers = {"*"},
        .explanation = "Önce 3 * 4 = 12 hesaplanır, ardından 2 + 12 = 14 bulunur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 92, .topicId = 11,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "double sonuc = _____(7) / 2; ifadesinin sonucu 3.5 olması için boşluğa hangi tür dönüştürme (cast) yazılmalı? (örnek: static_cast<double>)",
        .acceptedAnswers = {"static_cast<double>"},
        .explanation = "7 önce double'a dönüştürülürse bölme ondalıklı yapılır ve sonuç 3.5 olur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 93, .topicId = 11,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int a = 12;\nint b = 5;\nint sonuc = a _____ b;\nYukarıdaki kodun çalışması sonucunda sonuc değişkeninin 7 olması isteniyor. Boşluğa ne yazılmalı?",
        .acceptedAnswers = {"a - b", "a-b"},
        .explanation = "12 - 5 = 7 olduğu için çıkarma işlemi yapılmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 94, .topicId = 11,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int taban = 3;\nint yukseklik = 4;\nint alan = _____;\nBir üçgenin alanını (taban * yükseklik / 2) hesaplayan kodu tamamlayın.",
        .acceptedAnswers = {"taban * yukseklik / 2", "taban*yukseklik/2"},
        .explanation = "Üçgen alanı taban * yükseklik / 2 formülüyle hesaplanır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 95, .topicId = 11,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "int a = 15;\nint b = 4;\nstd::cout << a / b;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"3"},
        .explanation = "15 / 4, tam sayı bölmesiyle 3 eder.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 96, .topicId = 11,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "int a = 2;\nint b = 3;\nint c = 4;\nstd::cout << a + b * c - 1;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"13"},
        .explanation = "Önce b * c = 12 hesaplanır, sonra 2 + 12 - 1 = 13 bulunur.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 97, .topicId = 11,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint sonuc = 10 // 3;\nstd::cout << sonuc;\n\nHatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"int sonuc = 10 / 3;"},
        .explanation = "// bir yorum başlatır ve satırın geri kalanını yok sayar; bölme için tek / kullanılmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 98, .topicId = 11,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\ndouble sonuc = 7 / 2;\nstd::cout << sonuc;\n\nProgramcı sonuc'un 3.5 olmasını bekliyor ama kod 3 veriyor. Hatalı satırı, 3.5 sonucunu verecek şekilde düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"double sonuc = 7.0 / 2;", "double sonuc = static_cast<double>(7) / 2;"},
        .explanation = "7 / 2 önce int bölmesi olarak hesaplandığı için 3 olur; işlenenlerden birini ondalıklı yapmak (7.0) gerçek bölme sonucunu (3.5) verir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 99, .topicId = 11,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nint sonuc = 5 x 3;\nstd::cout << sonuc;\n\nDüzeltilmiş ilk satırı yazın.",
        .acceptedAnswers = {"int sonuc = 5 * 3;"},
        .explanation = "Çarpma işlemi x harfiyle değil * operatörüyle yapılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 100, .topicId = 11,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, iki sayının ortalamasını hesaplayıp yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın, örnek: 1 2 3):",
        .options = {"std::cout << ortalama;", "double ortalama = (a + b) / 2.0;", "int a = 4, b = 6;"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "Önce değişkenler tanımlanır (int a = 4, b = 6;), sonra ortalama hesaplanır, en son yazdırılır: sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 101, .topicId = 11,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Kullanıcıdan iki tam sayı okuyup toplamlarını, farklarını ve çarpımlarını ekrana yazdıran bir program yazın.",
        .acceptedAnswers = {"cin", ">>", "cout", "<<", "+", "-", "*"},
        .explanation = "Program iki sayıyı cin >> ile okumalı, +, - ve * operatörleriyle işlem yapmalı ve cout << ile sonuçları yazdırmalıdır.",
        .baseXp = 40,
    });

    // Topic 12: % mod operatörü
    questions.push_back(Question{
        .id = 102, .topicId = 12,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "10 % 3 işleminin sonucu kaçtır?",
        .options = {"3", "1", "0", "10"},
        .acceptedAnswers = {"b"},
        .explanation = "10'un 3'e bölümünden kalan 1'dir (10 = 3*3 + 1).",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 103, .topicId = 12,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "% operatörü hangi amaçla kullanılır?",
        .options = {"Çarpma", "Bölme", "Bölümden kalanı bulma", "Üs alma"},
        .acceptedAnswers = {"c"},
        .explanation = "% operatörü, bir sayının başka bir sayıya bölümünden kalanı verir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 104, .topicId = 12,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "8 % 2 işleminin sonucu kaçtır?",
        .options = {"4", "0", "2", "8"},
        .acceptedAnswers = {"b"},
        .explanation = "8, 2'ye tam bölündüğü için kalan 0'dır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 105, .topicId = 12,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "% operatörü hangi veri türleriyle kullanılabilir?",
        .options = {"Yalnızca double", "Yalnızca float", "Yalnızca tam sayı (int) türleri", "Her türle"},
        .acceptedAnswers = {"c"},
        .explanation = "% operatörü yalnızca tam sayı türleriyle kullanılabilir; double/float ile kullanılamaz.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 106, .topicId = 12,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "17 % 5 işleminin sonucu kaçtır?",
        .options = {"3", "2", "17", "5"},
        .acceptedAnswers = {"b"},
        .explanation = "17'nin 5'e bölümünden kalan 2'dir (17 = 5*3 + 2).",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 107, .topicId = 12,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "Bir sayının çift olup olmadığını kontrol etmek için hangi ifade kullanılır?",
        .options = {"sayi % 2 == 1", "sayi % 2 == 0", "sayi / 2 == 0", "sayi * 2 == 0"},
        .acceptedAnswers = {"b"},
        .explanation = "Bir sayının 2'ye göre modu sıfırsa, sayı çifttir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 108, .topicId = 12,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "-7 % 2 işleminin C++'taki (C++11 ve sonrası) sonucu kaçtır?",
        .options = {"1", "-1", "3", "-3"},
        .acceptedAnswers = {"b"},
        .explanation = "C++11'den itibaren % işleminin işareti bölünenin (dividend) işaretiyle aynıdır; -7 % 2 sonucu -1'dir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 109, .topicId = 12,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int a = 25; int b = 4; sonuc değişkenine a % b değerinin atanmasıyla sonuc kaç olur?",
        .options = {"6", "1", "6.25", "0"},
        .acceptedAnswers = {"b"},
        .explanation = "25'in 4'e bölümünden kalan 1'dir (25 = 4*6 + 1).",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 110, .topicId = 12,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "% operatörü, bölme işleminden kalanı verir.",
        .acceptedAnswers = {"1"},
        .explanation = "% operatörünün amacı tam olarak budur.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 111, .topicId = 12,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "% operatörü ondalıklı (double) sayılarla doğrudan kullanılabilir.",
        .acceptedAnswers = {"2"},
        .explanation = "% operatörü yalnızca tam sayı türleriyle kullanılabilir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 112, .topicId = 12,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "10 % 2 işleminin sonucu 0'dır.",
        .acceptedAnswers = {"1"},
        .explanation = "10, 2'ye tam bölünür, kalan 0'dır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 113, .topicId = 12,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "7 % 3 işleminin sonucu 2'dir.",
        .acceptedAnswers = {"2"},
        .explanation = "7'nin 3'e bölümünden kalan 1'dir (7 = 3*2 + 1), 2 değil.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 114, .topicId = 12,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Bir sayının 2'ye göre modu (sayi % 2), sayının çift mi tek mi olduğunu anlamak için kullanılabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Sonuç 0 ise sayı çift, 1 ise tektir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 115, .topicId = 12,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "0 % 5 işleminin sonucu 5'tir.",
        .acceptedAnswers = {"2"},
        .explanation = "0'ın 5'e bölümünden kalan 0'dır, 5 değil.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 116, .topicId = 12,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int kalan = 13 _____ 4; ifadesinin sonucu 1 olsun istiyorsunuz. Boşluğa hangi operatör yazılmalı?",
        .acceptedAnswers = {"%"},
        .explanation = "13'ün 4'e bölümünden kalan 1'dir; bu işlem % operatörüyle yapılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 117, .topicId = 12,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "9 % 3 = _____ (sonucu yazın)",
        .acceptedAnswers = {"0"},
        .explanation = "9, 3'e tam bölünür, kalan 0'dır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 118, .topicId = 12,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "15 % 4 = _____ (sonucu yazın)",
        .acceptedAnswers = {"3"},
        .explanation = "15'in 4'e bölümünden kalan 3'tür (15 = 4*3 + 3).",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 119, .topicId = 12,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int sayi = 8; bool ciftMi = (sayi % _____ == 0); ifadesinin sayi'nın çift olup olmadığını kontrol etmesi için boşluğa hangi sayı yazılmalı?",
        .acceptedAnswers = {"2"},
        .explanation = "Bir sayının 2'ye göre modu sıfırsa sayı çifttir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 120, .topicId = 12,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "23 % 5 = _____ (sonucu yazın)",
        .acceptedAnswers = {"3"},
        .explanation = "23'ün 5'e bölümünden kalan 3'tür (23 = 5*4 + 3).",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 121, .topicId = 12,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int a = 100; int b = 7; int kalan = a _____ b; ifadesinin kalan değişkenine 100'ün 7'ye bölümünden kalanı ataması için boşluğa hangi operatör yazılmalı?",
        .acceptedAnswers = {"%"},
        .explanation = "Bölümden kalanı bulmak için % operatörü kullanılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 122, .topicId = 12,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int sayi = 9;\nbool tekMi = _____;\nsayi'nın tek olup olmadığını (sayi % 2 == 1) kontrol eden ifadeyi boşluğa yazın.",
        .acceptedAnswers = {"sayi % 2 == 1", "sayi%2==1"},
        .explanation = "Bir sayının 2'ye göre modu 1 ise sayı tektir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 123, .topicId = 12,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int a = 29;\nint b = 6;\nint kalan = _____;\na'nın b'ye bölümünden kalanı hesaplayan ifadeyi boşluğa yazın.",
        .acceptedAnswers = {"a % b", "a%b"},
        .explanation = "Bölümden kalanı hesaplamak için % operatörü kullanılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 124, .topicId = 12,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "int a = 22;\nint b = 6;\nstd::cout << a % b;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"4"},
        .explanation = "22'nin 6'ya bölümünden kalan 4'tür (22 = 6*3 + 4).",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 125, .topicId = 12,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "int a = 14;\nint b = 4;\nstd::cout << a / b << \" \" << a % b;\nYukarıdaki kodun ekran çıktısı nedir? (aralarında bir boşluk olacak şekilde yazın)",
        .acceptedAnswers = {"3 2"},
        .explanation = "14 / 4 = 3 (tam sayı bölmesi), 14 % 4 = 2 (kalan); çıktı '3 2' olur.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 126, .topicId = 12,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\ndouble kalan = 10.5 % 3;\nstd::cout << kalan;\n\nHatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"int kalan = 10 % 3;"},
        .explanation = "% operatörü ondalıklı sayılarla kullanılamaz; işlenenler tam sayı olmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 127, .topicId = 12,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint kalan = 8 % 0;\nstd::cout << kalan;\n\nBu kod çalışma zamanında (runtime) çökmeye neden olur. Hatalı satırı, 8'in 4'e göre modunu alacak şekilde düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"int kalan = 8 % 4;"},
        .explanation = "0'a mod almak (tıpkı 0'a bölmek gibi) tanımsız davranışa ve çökmeye yol açar.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 128, .topicId = 12,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nint kalan = 20 %% 6;\nstd::cout << kalan;\n\nDüzeltilmiş ilk satırı yazın.",
        .acceptedAnswers = {"int kalan = 20 % 6;"},
        .explanation = "Mod operatörü tek bir % işaretiyle yazılır, %% ile değil.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 129, .topicId = 12,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir sayının çift olup olmadığını kontrol edip yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"std::cout << ciftMi;", "bool ciftMi = (sayi % 2 == 0);", "int sayi = 12;"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "Önce sayi tanımlanır, sonra çiftlik kontrolü yapılır, en son sonuç yazdırılır: sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 130, .topicId = 12,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Kullanıcıdan bir tam sayı okuyup, bu sayının çift mi tek mi olduğunu (mod operatörünü kullanarak) ekrana yazdıran bir program yazın.",
        .acceptedAnswers = {"cin", ">>", "%", "cout", "<<"},
        .explanation = "Program sayıyı cin >> ile okumalı, % 2 ile çift/tek kontrolü yapmalı ve cout << ile sonucu yazdırmalıdır.",
        .baseXp = 40,
    });

    // Topic 13: Kısaltılmış atama operatörleri
    questions.push_back(Question{
        .id = 131, .topicId = 13,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "int a = 5; a += 3; işleminden sonra a kaç olur?",
        .options = {"8", "3", "53", "15"},
        .acceptedAnswers = {"a"},
        .explanation = "a += 3, a = a + 3 ile aynıdır; 5 + 3 = 8.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 132, .topicId = 13,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "a += 5; ifadesi aşağıdakilerden hangisiyle aynı anlama gelir?",
        .options = {"a = 5;", "a = a + 5;", "a = a - 5;", "a += a;"},
        .acceptedAnswers = {"b"},
        .explanation = "+= operatörü, a = a + 5; ifadesinin kısaltılmış halidir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 133, .topicId = 13,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "int a = 10; a -= 4; işleminden sonra a kaç olur?",
        .options = {"14", "6", "-4", "40"},
        .acceptedAnswers = {"b"},
        .explanation = "a -= 4, a = a - 4 ile aynıdır; 10 - 4 = 6.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 134, .topicId = 13,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int a = 4; a *= 3; işleminden sonra a kaç olur?",
        .options = {"7", "12", "1", "34"},
        .acceptedAnswers = {"b"},
        .explanation = "a *= 3, a = a * 3 ile aynıdır; 4 * 3 = 12.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 135, .topicId = 13,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int a = 20; a /= 4; işleminden sonra a kaç olur?",
        .options = {"5", "16", "80", "24"},
        .acceptedAnswers = {"a"},
        .explanation = "a /= 4, a = a / 4 ile aynıdır; 20 / 4 = 5.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 136, .topicId = 13,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int a = 10; a %= 3; işleminden sonra a kaç olur?",
        .options = {"3", "1", "0", "7"},
        .acceptedAnswers = {"b"},
        .explanation = "a %= 3, a = a % 3 ile aynıdır; 10 % 3 = 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 137, .topicId = 13,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int a = 6; a *= 2 + 1; işleminden sonra a kaç olur?",
        .options = {"13", "18", "7", "9"},
        .acceptedAnswers = {"b"},
        .explanation = "a *= 2 + 1, a = a * (2 + 1) anlamına gelir; sağ taraf tamamen hesaplanır (3), sonra 6 * 3 = 18.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 138, .topicId = 13,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int a = 8; a /= 2; a += 3; işlemlerinden sonra a kaç olur?",
        .options = {"7", "11", "4", "8"},
        .acceptedAnswers = {"a"},
        .explanation = "Önce a /= 2 ile a = 4 olur, sonra a += 3 ile a = 7 olur.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 139, .topicId = 13,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "a += 5; ifadesi, a = a + 5; ile aynı işi yapar.",
        .acceptedAnswers = {"1"},
        .explanation = "+= operatörü tam olarak bu anlama gelir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 140, .topicId = 13,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "*= operatörü, bir değişkeni belirtilen değere böler.",
        .acceptedAnswers = {"2"},
        .explanation = "*= operatörü böler değil, çarpar.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 141, .topicId = 13,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Kısaltılmış atama operatörleri kod tekrarını azaltır.",
        .acceptedAnswers = {"1"},
        .explanation = "Değişken adını iki kez yazmak yerine kısaltılmış operatör kullanılabilir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 142, .topicId = 13,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "int a = 5; a -= 2; işleminden sonra a'nın değeri 3'tür.",
        .acceptedAnswers = {"1"},
        .explanation = "5 - 2 = 3.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 143, .topicId = 13,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "int a = 9; a %= 4; işleminden sonra a'nın değeri 2'dir.",
        .acceptedAnswers = {"2"},
        .explanation = "9 % 4 = 1'dir, 2 değil.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 144, .topicId = 13,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "a *= b + 1; ifadesi, a = a * b + 1; ile tamamen aynı sonucu üretir.",
        .acceptedAnswers = {"2"},
        .explanation = "a *= b + 1, a = a * (b + 1) anlamına gelir; bu genellikle a * b + 1'den farklıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 145, .topicId = 13,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int puan = 10; puan _____ 5; ifadesinin puan'ı 15 yapması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"+="},
        .explanation = "10 + 5 = 15 olduğu için += operatörü kullanılmalıdır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 146, .topicId = 13,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int puan = 10; puan _____ 4; ifadesinin puan'ı 6 yapması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"-="},
        .explanation = "10 - 4 = 6 olduğu için -= operatörü kullanılmalıdır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 147, .topicId = 13,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int puan = 5; puan _____ 4; ifadesinin puan'ı 20 yapması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"*="},
        .explanation = "5 * 4 = 20 olduğu için *= operatörü kullanılmalıdır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 148, .topicId = 13,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int puan = 20; puan _____ 5; ifadesinin puan'ı 4 yapması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"/="},
        .explanation = "20 / 5 = 4 olduğu için /= operatörü kullanılmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 149, .topicId = 13,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int puan = 17; puan _____ 5; ifadesinin puan'ı 2 yapması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"%="},
        .explanation = "17 % 5 = 2 olduğu için %= operatörü kullanılmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 150, .topicId = 13,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int a = 6; a += a; işleminden sonra a'nın yeni değeri _____ olur (sayı olarak yazın).",
        .acceptedAnswers = {"12"},
        .explanation = "a += a, a = a + a anlamına gelir; 6 + 6 = 12.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 151, .topicId = 13,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int bakiye = 100;\n_____\nstd::cout << bakiye;\nKullanıcının hesabından 30 birim çekildiğini (bakiye'yi azaltarak) gösteren satırı yazın.",
        .acceptedAnswers = {"bakiye -= 30;"},
        .explanation = "Bakiyeden düşme işlemi -= operatörüyle yapılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 152, .topicId = 13,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int toplam = 0;\nfor (int i = 0; i < 3; i++) {\n    _____\n}\nHer döngüde toplam değişkenine i'nin eklenmesini sağlayan satırı yazın.",
        .acceptedAnswers = {"toplam += i;"},
        .explanation = "toplam += i, toplam = toplam + i anlamına gelir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 153, .topicId = 13,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "int a = 5;\na += 3;\na *= 2;\nstd::cout << a;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"16"},
        .explanation = "5 + 3 = 8, ardından 8 * 2 = 16.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 154, .topicId = 13,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "int a = 10;\na -= 2;\na /= 4;\na += 1;\nstd::cout << a;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"3"},
        .explanation = "10 - 2 = 8, 8 / 4 = 2, 2 + 1 = 3.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 155, .topicId = 13,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint a = 10;\na =+ 5;\nstd::cout << a;\n\nProgramcı a'nın 15 olmasını istiyor ama kod farklı çalışıyor. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"a += 5;"},
        .explanation = "=+ operatörü diye bir şey yoktur; bu aslında a = (+5) anlamına gelir ve a'yı 5 yapar. Doğrusu a += 5;'tir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 156, .topicId = 13,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint a = 5;\na *= 2 + 3;\nstd::cout << a;\n\nProgramcı önce a'yı 2 ile çarpıp sonra 3 eklemek istiyor (sonuç 13 olsun istiyor) ama kod a'yı 5 ile çarpıyor (sonuç 25 oluyor). Hatalı satırı, programcının istediği sonucu (13) verecek şekilde düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"a = a * 2 + 3;"},
        .explanation = "a *= 2 + 3 aslında a = a * (2 + 3) anlamına gelir; istenen sonuç için açıkça a = a * 2 + 3; yazılmalıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 157, .topicId = 13,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nint a = 10;\na =- 3;\nstd::cout << a;\n\nProgramcı a'nın 7 olmasını istiyor. Düzeltilmiş ikinci satırı yazın.",
        .acceptedAnswers = {"a -= 3;"},
        .explanation = "=- operatörü diye bir şey yoktur; bu a = (-3) anlamına gelir. Doğrusu a -= 3;'tür.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 158, .topicId = 13,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir bakiyeye para ekleyip yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"std::cout << bakiye;", "bakiye += 50;", "int bakiye = 100;"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "Önce bakiye tanımlanır, sonra üzerine eklenir, en son yazdırılır: sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 159, .topicId = 13,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Kullanıcıdan bir tam sayı okuyup, bu sayıya kısaltılmış atama operatörlerini (+=, *= gibi) kullanarak önce 10 ekleyen, sonra 2 ile çarpan bir program yazın; sonucu ekrana yazdırın.",
        .acceptedAnswers = {"cin", ">>", "+=", "*=", "cout", "<<"},
        .explanation = "Program sayıyı cin >> ile okumalı, += 10 ve *= 2 işlemlerini uygulamalı, sonucu cout << ile yazdırmalıdır.",
        .baseXp = 40,
    });

    // Topic 14: ++ ve --
    questions.push_back(Question{
        .id = 160, .topicId = 14,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "int a = 5; a++; işleminden sonra a kaç olur?",
        .options = {"5", "6", "4", "55"},
        .acceptedAnswers = {"b"},
        .explanation = "a++, a'yı 1 artırır; 5 + 1 = 6.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 161, .topicId = 14,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "++ operatörü ne işe yarar?",
        .options = {"Değeri 1 azaltır", "Değeri 2 katına çıkarır", "Değeri 1 artırır", "Değeri sıfırlar"},
        .acceptedAnswers = {"c"},
        .explanation = "++ operatörü bir değişkenin değerini 1 artırır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 162, .topicId = 14,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "int a = 5; --a; işleminden sonra a kaç olur?",
        .options = {"4", "5", "6", "-5"},
        .acceptedAnswers = {"a"},
        .explanation = "--a, a'yı 1 azaltır; 5 - 1 = 4.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 163, .topicId = 14,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int a = 5; int b = a++; işleminden sonra b kaç olur?",
        .options = {"5", "6", "4", "0"},
        .acceptedAnswers = {"a"},
        .explanation = "Sondan artırma (a++), b'ye önce a'nın eski değerini (5) atar, sonra a'yı artırır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 164, .topicId = 14,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int a = 5; int b = ++a; işleminden sonra b kaç olur?",
        .options = {"5", "6", "4", "7"},
        .acceptedAnswers = {"b"},
        .explanation = "Önden artırma (++a), önce a'yı artırır (6 olur), sonra bu güncel değeri b'ye atar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 165, .topicId = 14,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int a = 5; int b = a++; işleminden sonra a'nın değeri kaç olur?",
        .options = {"5", "6", "4", "7"},
        .acceptedAnswers = {"b"},
        .explanation = "Sondan artırmada da a'nın kendisi 1 artar; b'nin ne aldığından bağımsız olarak a 6 olur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 166, .topicId = 14,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int a = 10; a--; --a; a++; işlemlerinden sonra a kaç olur?",
        .options = {"9", "8", "10", "11"},
        .acceptedAnswers = {"a"},
        .explanation = "10 - 1 = 9 (a--), 9 - 1 = 8 (--a), 8 + 1 = 9 (a++); üç ayrı işlemden sonra a'nın son değeri 9'dur.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 167, .topicId = 14,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int a = 3;\na++;\na++;\n--a;\nstd::cout << a;\nifadesinin sonucu (a'nın son değeri) kaçtır?",
        .options = {"3", "4", "5", "6"},
        .acceptedAnswers = {"b"},
        .explanation = "3 + 1 = 4, 4 + 1 = 5, 5 - 1 = 4.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 168, .topicId = 14,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "++ operatörü bir değişkenin değerini 1 artırır.",
        .acceptedAnswers = {"1"},
        .explanation = "++ operatörünün işlevi tam olarak budur.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 169, .topicId = 14,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "-- operatörü bir değişkenin değerini 2 azaltır.",
        .acceptedAnswers = {"2"},
        .explanation = "-- operatörü değeri 2 değil, 1 azaltır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 170, .topicId = 14,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Önden artırma (++a) ile sondan artırma (a++), tek başına bir satırda kullanıldıklarında aynı sonucu üretir (a'nın son değeri açısından).",
        .acceptedAnswers = {"1"},
        .explanation = "Her iki durumda da a bir satırın sonunda 1 artmış olur; fark yalnızca ifadenin kendi döndürdüğü değerdedir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 171, .topicId = 14,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "int a = 5; int b = a++; ifadesinde b'nin değeri 6'dır.",
        .acceptedAnswers = {"2"},
        .explanation = "Sondan artırma, eski değeri (5) döndürür; b 6 değil 5 olur.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 172, .topicId = 14,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "int a = 5; int b = ++a; ifadesinde b'nin değeri 6'dır.",
        .acceptedAnswers = {"1"},
        .explanation = "Önden artırma, güncellenmiş değeri (6) döndürür.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 173, .topicId = 14,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Sondan artırma (a++), işlemden önceki değeri döndürür.",
        .acceptedAnswers = {"1"},
        .explanation = "a++ önce mevcut değeri kullanır/döndürür, sonra a'yı artırır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 174, .topicId = 14,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int a = 5; a_____; ifadesinin a'yı 6 yapması için boşluğa ne yazılmalı? (iki karakterlik operatör)",
        .acceptedAnswers = {"++"},
        .explanation = "a++, a'yı 1 artırır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 175, .topicId = 14,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int a = 5; a_____; ifadesinin a'yı 4 yapması için boşluğa ne yazılmalı? (iki karakterlik operatör)",
        .acceptedAnswers = {"--"},
        .explanation = "a--, a'yı 1 azaltır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 176, .topicId = 14,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int a = 5; int b = a_____; ifadesinden sonra b'nin 5, a'nın ise 6 olması isteniyor (sondan artırma). Boşluğa ne yazılmalı?",
        .acceptedAnswers = {"++"},
        .explanation = "Sondan artırma (a++), eski değeri b'ye verir, sonra a'yı artırır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 177, .topicId = 14,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int a = 5; int b = _____a; ifadesinden sonra hem a'nın hem de b'nin 6 olması isteniyor (önden artırma). Boşluğa ne yazılmalı?",
        .acceptedAnswers = {"++"},
        .explanation = "Önden artırma (++a), önce a'yı artırır, sonra bu güncel değeri b'ye de verir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 178, .topicId = 14,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int a = 0; for (int i = 0; i < 5; i_____) { a += i; } ifadesinde döngü sayacının her adımda 1 artması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"++"},
        .explanation = "Döngü sayacı genellikle i++ ile artırılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 179, .topicId = 14,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int a = 8; a_____; a_____; işlemlerinden sonra a'nın 6 olması için boşluğa (iki kez tekrar edilecek) ne yazılmalı?",
        .acceptedAnswers = {"--"},
        .explanation = "8'i iki kez 1 azaltmak 6 verir (8 - 1 - 1 = 6); bu -- operatörüyle yapılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 180, .topicId = 14,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int sayac = 0;\n_____\nstd::cout << sayac;\nsayac değişkenini önden artırma operatörüyle 1 artıran satırı yazın.",
        .acceptedAnswers = {"++sayac;"},
        .explanation = "Önden artırma ++sayac; şeklinde yazılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 181, .topicId = 14,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int i = 10;\nwhile (i > 0) {\n    _____\n}\nHer döngüde i'yi 1 azaltan satırı yazın (sonsuz döngüyü önlemek için gerekli).",
        .acceptedAnswers = {"i--;", "--i;"},
        .explanation = "i'yi 1 azaltmak için i-- veya --i kullanılabilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 182, .topicId = 14,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "int a = 4;\nstd::cout << a++;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"4"},
        .explanation = "Sondan artırma, ekrana yazdırmadan önceki değeri (4) verir; a daha sonra 5 olur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 183, .topicId = 14,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "int a = 4;\nstd::cout << ++a;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"5"},
        .explanation = "Önden artırma, önce a'yı 5 yapar, sonra bu güncel değeri yazdırır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 184, .topicId = 14,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint a = 5;\na++\nstd::cout << a;\n\nHatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"a++;"},
        .explanation = "a++ satırının sonunda noktalı virgül eksik.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 185, .topicId = 14,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint a = 5;\na+;\nstd::cout << a;\n\nProgramcı a'yı 1 artırmak istiyor. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"a++;"},
        .explanation = "a+; geçersiz bir ifadedir; artırma operatörü ++ şeklinde, tek + değil çift + ile yazılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 186, .topicId = 14,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nint a = 10;\na- -;\nstd::cout << a;\n\nProgramcı a'yı 1 azaltmak istiyor. Düzeltilmiş ikinci satırı yazın.",
        .acceptedAnswers = {"a--;"},
        .explanation = "Azaltma operatörü -- şeklinde, arada boşluk olmadan yazılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 187, .topicId = 14,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir sayacı artırıp yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"std::cout << sayac;", "sayac++;", "int sayac = 0;"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "Önce sayac tanımlanır, sonra artırılır, en son yazdırılır: sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 188, .topicId = 14,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "1'den 5'e kadar olan sayıları, bir sayaç değişkenini artırma operatörü (++) ile kullanarak bir döngüde ekrana yazdıran bir program yazın.",
        .acceptedAnswers = {"for", "++", "cout", "<<"},
        .explanation = "Program bir for döngüsü içinde sayacı ++ ile artırmalı ve her adımda cout << ile yazdırmalıdır.",
        .baseXp = 40,
    });
}
