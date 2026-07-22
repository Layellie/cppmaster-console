# Değişiklik günlüğü / Changelog

Bu dosya [Keep a Changelog](https://keepachangelog.com/tr/1.1.0/)
biçimini, sürüm numaraları ise [Semantic Versioning](https://semver.org/)
kurallarını izler.

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
