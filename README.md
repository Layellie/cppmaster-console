# CppMaster Console

C++ öğrenmek için terminal tabanlı, Türkçe bir alıştırma ve sınav
uygulaması. 100 konuluk tam bir müfredat, 2600'den fazla soru, hint/kilit/
adaptif-zorluk sistemleri, kod yazma alıştırmaları, bölüm sınavları, bir
genel final sınavı ve 17 üreticili, tekrarsız bir dinamik soru üretim
sistemi içerir.

## Hızlı kurulum (Windows)

Derleyici veya CMake kurmana gerek yok — tek satırlık komutla önceden
derlenmiş, bağımsız bir `.exe` indirilip çalıştırılır:

```powershell
irm https://raw.githubusercontent.com/Layellie/cppmaster-console/master/install.ps1 | iex
```

Bu, en son `master` commit'inden otomatik derlenen sürümü
`%LOCALAPPDATA%\CppMasterConsole` altına indirir ve başlatır; ilerlemen
sonraki çalıştırmalarda aynı klasörde saklanır. Derlenen `.exe`, MSVC
çalışma zamanına statik olarak bağlıdır — Visual C++ Redistributable
kurulu olmasa bile çalışır.

> Not: Bu repo şu an private; yukarıdaki komut yalnızca repo public
> olduğunda (veya kimlik doğrulamalı bir istekle) çalışır.

## Kapsam

- **Konular:** 100 konu, 10 bölüm, hepsinde tam ders içeriği (açıklama,
  sözdizimi, örnek kod, satır satır açıklama, yaygın hatalar).
- **Sorular:** 2600'den fazla elle yazılmış soru (11 soru tipinden 9'u
  kullanılıyor), artı "Hızlı Test" modunda gerçek zamanlı, tekrarsız
  üretilen sorular (17 üretici, 4 aşamalı üretim algoritması: Normal →
  Genişletilmiş Parametreler → Yapısal Varyasyon → Çapraz Konu).
- **Konu kilidi:** Konular gerçekten kilitli ve sırayla açılıyor — bir
  konuyu tamamlamadan bir sonrakine erişilemez. İlk açılışta seçtiğin
  deneyim seviyesine göre başlangıç aralığı değişir (yeni başlayan: sadece
  1. konu; orta seviye: 1-20; deneyimli: 1-40).
  Ayarlar'dan tamamen kapatılabilir.
- **Sınavlar:** Her bölüm için 20 soruluk bir sınav, artı 100 soruluk genel
  final sınavı (%70 geçme notu, konu tamamlama oranına göre kilitli).
- **Hint sistemi:** Quiz sırasında `ipucu`/`konu`/`ornek`/`gec`/`cikis`
  komutları; her ipucu seviyesi kazanılan XP'yi azaltır.
- **Adaptif zorluk:** Art arda doğru cevaplar daha zor sorulara atlar; art
  arda yanlışlar otomatik ekstra yardım gösterir.
- **Kod Yazma Alıştırmaları:** 3 seviyede (Başlangıç/Orta/İleri) 25 elle
  yazılmış kod alıştırması.
- **XP/Seviye/Başarımlar:** 10 seviyelik XP sistemi, açılabilir başarımlar,
  yanlış-tekrar ve günlük tekrar akışları.
- **Kişiselleştirme:** Renkli çıktı (doğru/yanlış/başarım geri bildirimi),
  sesli uyarı, Hızlı Test soru sayısı — hepsi Ayarlar'dan değiştirilebilir.
- **Kalıcı veri:** İlerleme, yanlış kayıtları, başarımlar, üretilen soru
  geçmişi ve ayarlar `data/` klasöründe saklanır (git'e dahil değil).

## Geliştirici olarak derleme

### Gereksinimler

- CMake ≥ 3.20
- C++20 destekleyen bir derleyici (bu proje şu ana kadar yalnızca MSVC ile
  derlenip test edildi — aşağıdaki "Cross-Platform Notlar" bölümüne bakın)

### Derleme

```bash
cmake -B build
cmake --build build
```

Bağımsız, dağıtılabilir bir Release derlemesi için:
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```
(MSVC çalışma zamanı statik olarak bağlanır — bkz. `CMakeLists.txt`'teki
`CMAKE_MSVC_RUNTIME_LIBRARY` ayarı — böylece çıkan `.exe` başka bir
makinede Redistributable kurulu olmadan da çalışır.)

### Çalıştırma

Windows/MSVC (çok yapılandırmalı generator) üzerinde:
```bash
./build/Debug/CppMasterConsole.exe
```
Tek yapılandırmalı generatorlerde (Makefiles, Ninja):
```bash
./build/CppMasterConsole
```

### Testleri çalıştırma

```bash
ctest --test-dir build --output-on-failure
```
veya test binary'sini doğrudan çalıştırarak:
```bash
./build/Debug/CppMasterConsoleTests.exe
```

Test paketi standart kütüphane dışında hiçbir bağımlılık kullanmaz; kendi
kendini kaydeden (`TEST_CASE`), basit bir test çatısı `tests/TestRunner.h`
içinde tanımlıdır. Ayrıca, dinamik soru üretim sistemini 10.000+
iterasyonda stres testinden geçiren ayrı bir `CppMasterConsoleStressTests`
hedefi var (bilinçli olarak `ctest`'e dahil değil, çünkü ~10-15 saniye
sürüyor — hızlı test döngüsünü yavaşlatmaması için elle çalıştırılır):
```bash
./build/Debug/CppMasterConsoleStressTests.exe
```

### Otomatik derleme ve dağıtım

`.github/workflows/release.yml`, `master`'a her push'ta Release modunda
derler, testleri çalıştırır ve bağımsız `.exe`'yi repo'nun "latest"
GitHub Release'ine yükler — `install.ps1`'in indirdiği sürüm budur.

## Proje yapısı

```
src/              Uygulama kaynak kodu (CppMasterConsoleLib statik kütüphanesi + main.cpp)
src/generators/   Dinamik soru üreticileri (17 adet, her biri kendi .h/.cpp'sinde)
tests/            Birim testleri (CppMasterConsoleTests hedefi)
tests/Generators/ Her üretici için ayrı test dosyaları
tests/StressTests/ 10.000+ iterasyonluk üretim stres testleri (ayrı hedef)
data/             Kullanıcının ilerleme/istatistik/ayar dosyaları (git'e dahil değil)
docs/superpowers/ Geliştirme süreci: tasarım dokümanları (specs/), uygulama planları (plans/), roadmap.md
.github/workflows/ CI: derleme, test, ve GitHub Release otomasyonu
install.ps1       Tek satırlık kurulum/başlatma script'i
```

## Test kapsamı hakkında

`src/` altındaki saf mantık ve dosya-kalıcılık sınıflarının tamamı birim
testleriyle kapsanır. `Application` ve `ConsoleUI` (etkileşimli, klavyeden
girdi bekleyen kısımlar) bilinçli olarak birim testi kapsamı dışında
bırakıldı — bunlar, geliştirme sürecinde elle hazırlanmış giriş
senaryolarıyla uçtan uca doğrulanmaya devam ediyor
(`docs/superpowers/plans/` içindeki her fazın planında görülebilir).

## Cross-Platform Notlar

Bu proje şu ana kadar yalnızca MSVC/Windows ortamında derlenip
çalıştırıldı. Kod, bilinen hiçbir MSVC'ye özgü yapı kullanmıyor ve tek
platforma özgü davranışını (`konsolu temizleme komutu`, UTF-8 kod sayfası
ayarı, ANSI renk desteği için `ENABLE_VIRTUAL_TERMINAL_PROCESSING`,
`src/ConsoleUI.cpp`) `#ifdef _WIN32` ile izole ediyor; GCC/Clang veya
Linux/macOS uyumluluğu ise kod incelemesiyle değerlendirildi ama bu
geliştirme ortamında böyle bir derleyici/işletim sistemi bulunmadığı için
gerçek bir derlemeyle doğrulanmadı.
