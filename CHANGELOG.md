# Değişiklik günlüğü / Changelog

Bu dosya [Keep a Changelog](https://keepachangelog.com/tr/1.1.0/)
biçimini, sürüm numaraları ise [Semantic Versioning](https://semver.org/)
kurallarını izler.

## [1.1.0] - 2026-11-24

### Eklenenler

- Bölüm 1 içeriği genişletilerek toplam soru bankası 2.908 elle yazılmış soruya
  çıkarıldı.
- Ana menü 3 sütunlu düzene geçirildi ve terminal renk paleti tüm ekranlara
  yayıldı.
- Doğru/Yanlış sorularında `A`/`B` yanıtları kabul edilir hale getirildi; aynı
  konu bilgisinin art arda sorulması engellendi.
- `ConsoleUI` için birim testleri eklendi (toplam 259 birim testi).

### Düzeltilenler

- İlerleme, ayarlar, yanlışlar, başarımlar ve üretilen soru geçmişi artık geçici
  dosyaya yazılıp atomik yeniden adlandırma (`AtomicFileWrite`) ile kaydediliyor;
  yazma hataları sessizce yutulmak yerine kullanıcıya bildiriliyor.
- `ConsoleUI::clearScreen` içindeki `std::system("cls"/"clear")` çağrısı
  kaldırıldı; ANSI VT kaçış dizisi ve Windows için Win32 Console API yedeği
  eklendi.
- Windows tarafında MSVC `/utf-8` bayrağı eklendi, konsol UTF-8 kod sayfası
  çıkışta eski haline döndürülüyor ve etkileşimli Türkçe girdi `ReadConsoleW`
  ile okunuyor.
- Menü, test ve ayar ekranlarında `stdin` EOF/`badbit` durumları temiz şekilde
  ele alınıyor.
- `std::sto*` çağrıları ortak `std::from_chars` yardımcılarıyla değiştirildi;
  bozuk veya taşmış sayaç değerleri yükleme sırasında yakalanıyor.
- `QuizEngine::correctAnswerDisplay` boş `acceptedAnswers` koruması,
  `quizSize == 0` seçimi, `SortWithLambdaPredictGenerator` eşit uzaklık
  belirsizliği, `StringConcatPredictGenerator` geçersiz string birleştirme,
  üretilen soru ID çakışmaları, konu durumu düşüşleri ve günlük tekrarda kaçan
  başarım kontrolleri düzeltildi.

### İyileştirilenler

- `QuestionManager` ve `LessonManager` için kopyasız `std::span` / `const*`
  okuma yolları, `GeneratorScoring` için transparent lookup ve `MistakeTracker`
  için `O(1)` sayım eklendi.
- `Application.cpp` sorumluluklarına göre `MenuFormatting`, `SettingsScreen`,
  `CodeExerciseSession`, `QuizSession`, `ExamSession` ve `AppContext`
  dosyalarına bölündü.
- `clang-tidy-21` uyarıları temizlendi ve İngilizce/Türkçe `README.md` mevcut
  mimariyle eşitlendi.

## [1.0.0] — 2026-07-22

İlk sürüm. Uygulamanın tamamı bu sürümde hazır durumda.

### Eklenenler

- **Müfredat:** 10 bölüme ayrılmış 100 konu; her konuda açıklama,
  sözdizimi, örnek kod, satır satır açıklama ve yaygın hatalar.
- **Soru bankası:** 2.682 elle yazılmış soru, 9 farklı soru tipinde.
- **Dinamik soru üretimi:** 17 üretici ve 4 aşamalı üretim algoritması
  (Normal → Genişletilmiş Parametreler → Yapısal Varyasyon → Çapraz Konu);
  üretilen sorular exact/semantic imza karşılaştırmasıyla hiç tekrar
  etmiyor.
- **Sınavlar:** Her bölüm için 20 soruluk sınav ve 100 soruluk genel final
  sınavı (%70 geçme notu, konu tamamlama oranına göre kilitli).
- **Konu kilidi:** Konular sırayla açılır; ilk açılıştaki seviye seçimi
  başlangıç aralığını belirler. Ayarlar'dan kapatılabilir.
- **İpucu sistemi:** Test sırasında `ipucu`, `konu`, `ornek`, `gec` ve
  `cikis` komutları; her ipucu seviyesi kazanılan XP'yi %25 azaltır.
- **Adaptif zorluk:** Art arda doğru cevaplarda daha zor sorulara geçiş,
  art arda yanlışlarda otomatik ek yardım.
- **Kod yazma alıştırmaları:** 3 seviyede toplam 25 alıştırma.
- **İlerleme:** XP/seviye sistemi (10 seviye), başarımlar, yanlış-tekrar ve
  günlük tekrar akışları, dışa/içe aktarma.
- **Kişiselleştirme:** ANSI renkli çıktı, sesli uyarı, Hızlı Test soru
  sayısı ve diğer ayarlar.
- **Dağıtım:** Tek satırlık PowerShell kurulumu (`install.ps1`) ve her
  `master` push'unda otomatik derlenip yayınlanan bağımsız `.exe`.

### Teknik notlar

- C++20, CMake ≥ 3.20, üçüncü parti bağımlılık yok (birim test çatısı
  dahil).
- Windows/MSVC, Linux/GCC ve Linux/Clang yapılandırmalarının üçü de CI'da
  uyarısız derleniyor ve testleri geçiyor.
- Bozuk kalıcı veri dosyaları otomatik yedeklenip varsayılanlara
  dönülüyor.
