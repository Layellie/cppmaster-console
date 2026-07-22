# CppMaster Console

[![CI](https://github.com/Layellie/cppmaster-console/actions/workflows/ci.yml/badge.svg)](https://github.com/Layellie/cppmaster-console/actions/workflows/ci.yml)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![C++20](https://img.shields.io/badge/C%2B%2B-20-blue.svg)](https://en.cppreference.com/w/cpp/20)

C++ öğrenmek için terminal tabanlı, Türkçe bir alıştırma ve sınav
uygulaması. 100 konuluk tam bir müfredat, 2.682 elle yazılmış soru,
ipucu / konu kilidi / adaptif zorluk sistemleri, kod yazma alıştırmaları,
bölüm sınavları, genel bir final sınavı ve 17 üreticiden oluşan,
aynı soruyu iki kez sormayan dinamik bir soru üretim sistemi içerir.

> **In English:** CppMaster Console is a terminal-based C++ practice app
> with a **Turkish-language interface**. It covers a 100-topic curriculum
> with 2,682 hand-written questions, per-section and final exams,
> code-writing exercises, an XP / level / achievement system, sequential
> topic unlocking, and a dynamic question generator (17 generators, a
> 4-stage escalation strategy) that never asks the same question twice.
> Written in C++20 with CMake and **no third-party dependencies** — the
> unit-test framework is hand-rolled too. Build and test commands are in
> [Geliştirici olarak derleme](#geliştirici-olarak-derleme); they are
> plain CMake, so no Turkish is needed to follow them.

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

## Nasıl görünüyor?

```
========================================
CPPMASTER CONSOLE
========================================

Toplam XP: 75
Seviye: Değişken Ustası (Seviye 2)

1. Konuları Öğren          6. Seviye Sınavı
2. Hızlı Test              7. İstatistiklerim
3. Günlük Tekrar           8. Başarımlar
4. Hatalarımı Çöz          9. Ayarlar
5. Kod Yazma Alıştırmaları 10. İlerlemeyi Sıfırla
0. Çıkış
```

Bir konu testinden kesit — doğru cevap yeşil, yanlış kırmızı gösterilir,
başarımlar sarı:

```
Konu testi başlıyor (8 soru).

cout, kullanıcıdan klavyeden veri okumak için kullanılır.
1. Doğru
2. Yanlış
Cevabın: 2
Doğru! (+5 XP)

Yeni başarım kazandın: İlk Adım
İlk sorunu çözdün.
```

Soru sırasında `ipucu`, `konu`, `ornek`, `gec` ve `cikis` komutları
kullanılabilir; her ipucu kazanılacak XP'yi %25 azaltır.

## Kapsam

- **Konular:** 100 konu, 10 bölüm, hepsinde tam ders içeriği (açıklama,
  sözdizimi, örnek kod, satır satır açıklama, yaygın hatalar).
- **Sorular:** 2.682 elle yazılmış soru (11 soru tipinden 9'u
  kullanılıyor), artı "Hızlı Test" modunda gerçek zamanlı üretilen ve
  hiç tekrar etmeyen sorular (17 üretici, 4 aşamalı üretim algoritması:
  Normal → Genişletilmiş Parametreler → Yapısal Varyasyon → Çapraz Konu).
- **Konu kilidi:** Konular gerçekten kilitli ve sırayla açılıyor — bir
  konuyu tamamlamadan bir sonrakine erişilemez, kilitli konular listede
  hiç görünmez. İlk açılışta seçtiğin deneyim seviyesi başlangıç
  aralığını belirler (yeni başlayan: yalnızca 1. konu; orta seviye:
  1-20; deneyimli: 1-40). Kilit sistemi Ayarlar'dan tamamen
  kapatılabilir.
- **Sınavlar:** Her bölüm için 20 soruluk bir sınav, artı 100 soruluk genel
  final sınavı (%70 geçme notu, konu tamamlama oranına göre kilitli).
- **İpucu sistemi:** Test sırasında `ipucu`/`konu`/`ornek`/`gec`/`cikis`
  komutları; her ipucu seviyesi kazanılan XP'yi azaltır.
- **Adaptif zorluk:** Art arda doğru cevaplar daha zor sorulara atlar; art
  arda yanlışlar otomatik ekstra yardım gösterir.
- **Kod Yazma Alıştırmaları:** 3 seviyede (Başlangıç/Orta/İleri) 25 elle
  yazılmış kod alıştırması; tamamladıkların listede işaretlenir.
- **XP/Seviye/Başarımlar:** 10 seviyelik XP sistemi, açılabilir başarımlar,
  yanlış-tekrar ve günlük tekrar akışları.
- **Kişiselleştirme:** Renkli çıktı (doğru/yanlış/başarım geri bildirimi),
  sesli uyarı, Hızlı Test soru sayısı — hepsi Ayarlar'dan değiştirilebilir.
- **Kalıcı veri:** İlerleme, yanlış kayıtları, başarımlar, üretilen soru
  geçmişi ve ayarlar `data/` klasöründe saklanır (git'e dahil değil).

## Geliştirici olarak derleme

### Gereksinimler

- CMake ≥ 3.20
- C++20 destekleyen bir derleyici — MSVC 2022+, GCC 11+ veya Clang 14+
  (üçü de CI'da doğrulanıyor, bkz. [Platform desteği](#platform-desteği))
- Üçüncü parti bağımlılık **yok**; test çatısı dahil her şey standart
  kütüphaneyle yazıldı

### Derleme

CMake preset'leriyle (önerilen):
```bash
cmake --preset default        # yapılandır
cmake --build --preset default # derle
ctest --preset default         # test et
```

Ya da klasik yöntemle:
```bash
cmake -B build
cmake --build build
```

Bağımsız, dağıtılabilir bir Release derlemesi için:
```bash
cmake --preset release && cmake --build --preset release
```
MSVC'de çalışma zamanı statik bağlanır (`CMakeLists.txt` içindeki
`CMAKE_MSVC_RUNTIME_LIBRARY`), böylece çıkan `.exe` Visual C++
Redistributable kurulu olmayan bir makinede de çalışır — tek bağımlılığı
`KERNEL32.dll`'dir.

### Çalıştırma

Windows/MSVC gibi çok yapılandırmalı CMake generator'lerinde:
```bash
./build/Debug/CppMasterConsole.exe
```
Tek yapılandırmalı CMake generator'lerinde (Makefiles, Ninja):
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
.github/workflows/ CI: derleme, test ve GitHub Release otomasyonu
install.ps1       Tek satırlık kurulum/başlatma script'i
```

## Mimari notlar

Projenin teknik olarak en ilginç parçası **dinamik soru üretim sistemi**.
Amaç, kullanıcıya aynı soruyu iki kez sormadan sınırsız pratik sağlamak:

- Her üretici (`src/generators/`) tek bir konudan sorumludur ve
  `IQuestionGenerator` arayüzünü uygular.
- Üretilen her soru iki imza taşır: **exact** (tüm parametreler, kozmetik
  değişken adı dahil) ve **semantic** (kozmetik farklar hariç). İkisi de
  FNV-1a ile hash'lenip `QuestionHistory`'de saklanır; böylece "aynı soru,
  farklı değişken adıyla" tekrar sorulmaz.
- `QuestionGenerationEngine` 4 aşamalı bir tırmanma uygular: **Normal →
  Genişletilmiş Parametreler → Yapısal Varyasyon**, hepsi tükenirse
  **Çapraz Konu** yedeği (başarı oranına göre sıralanmış diğer üreticiler).
  Her aşamaya 20 deneme bütçesi verilir.
- `GeneratorScoring` her üreticinin başarı oranını takip eder;
  `GeneratedQuestionValidator` üretilen sorunun yapısal geçerliliğini
  bağımsız olarak doğrular.

Bu sistem 10.000 iterasyonluk bir stres testiyle doğrulanıyor: sıfır
tekrar, sıfır geçersiz soru, %100 üretim başarısı
(`tests/StressTests/`).

Diğer tasarım kararları:

- `src/` içindeki her şey **bağımlılıksız ve saf**: iş mantığı
  (`QuizEngine`, `LevelSystem`, `TopicLock`, `AdaptiveDifficulty`) konsol
  G/Ç'sinden ayrıdır, bu yüzden tamamı birim testiyle kapsanabiliyor.
- Kalıcı veri düz metin dosyalarında tutulur; her yükleyici bozuk dosyayı
  algılayıp yedekler ve varsayılanlara döner (`*_corrupted_backup.txt`).
- Ders ve soru içeriği koda gömülüdür (`LessonContentSectionN.cpp`,
  `QuestionsSectionN.cpp`) — uygulamanın tek dosya olarak dağıtılabilmesi
  ve harici veri dosyası gerektirmemesi için bilinçli bir tercih.

## Test kapsamı hakkında

`src/` altındaki saf mantık ve dosya-kalıcılık sınıflarının tamamı birim
testleriyle kapsanır. `Application` ve `ConsoleUI` (etkileşimli, klavyeden
girdi bekleyen kısımlar) bilinçli olarak birim testi kapsamı dışında
bırakıldı — bunlar, geliştirme sürecinde elle hazırlanmış giriş
senaryolarıyla uçtan uca doğrulanmaya devam ediyor
(`docs/superpowers/plans/` içindeki her fazın planında görülebilir).

## Platform desteği

Her push ve pull request'te üç yapılandırma CI'da derlenip test ediliyor:

| Platform | Derleyici | Durum |
|---|---|---|
| Windows | MSVC (`/W4 /permissive-`) | ✅ derleme + testler + stres testleri, **0 uyarı** |
| Linux | GCC (`-Wall -Wextra -Wpedantic -Wconversion -Wshadow`) | ✅ derleme + testler + stres testleri, **0 uyarı** |
| Linux | Clang (aynı bayraklar) | ✅ derleme + testler + stres testleri, **0 uyarı** |

Platforma özgü tek davranış `src/ConsoleUI.cpp` içinde `#ifdef _WIN32` ile
izole edilmiştir: konsol temizleme komutu, UTF-8 kod sayfası ayarı ve ANSI
renk desteği için `ENABLE_VIRTUAL_TERMINAL_PROCESSING`. Renk desteği
açılamazsa çıktı sessizce renksize düşer, bozuk kaçış dizileri basılmaz.

macOS ayrıca test edilmiyor (GitHub Actions'ta ücretsiz runner maliyetini
artırmamak için), ancak Linux/Clang ile aynı kod yollarını kullandığından
çalışması bekleniyor.

## Katkıda bulunma

Katkılar memnuniyetle karşılanır — kod, ders içeriği veya soru
düzeltmeleri. Ayrıntılar için [CONTRIBUTING.md](CONTRIBUTING.md)'ye bakın.
Güvenlikle ilgili konular için [SECURITY.md](SECURITY.md).

## Sürüm geçmişi

Sürümler arası değişiklikler için [CHANGELOG.md](CHANGELOG.md).

## Lisans

[MIT](LICENSE) — Copyright (c) 2026 Samet Kaşmer.
