# CppMaster Console

C++ öğrenmek için terminal tabanlı, Türkçe bir alıştırma ve sınav
uygulaması. 100 konuluk bir müfredat, 11 farklı soru tipi, XP/seviye
sistemi, başarımlar, yanlış-tekrar ve günlük tekrar akışları, bir bölüm
sınavı ve gerçek zamanlı, tekrarsız soru üretimi ("Hızlı Test") içerir.

## Mevcut durum

- **Konular:** 100 konu, 10 bölüme ayrılmış durumda. Şu an yalnızca ilk 10
  konu (Bölüm 1: "Giriş, çıkış ve değişkenler") tam ders içeriğine sahip;
  geri kalan 90 konu müfredatta yer alıyor ama ders içeriği henüz eklenmedi
  (uygulama bunu dürüstçe "bu sürümde henüz eklenmedi" diyerek belirtir).
- **Sorular:** 72 elle yazılmış soru (ilk 10 konu için), artı "Hızlı Test"
  modunda gerçek zamanlı üretilen, hiç tekrar etmeyen sorular.
- **Kalıcı veri:** İlerleme, yanlış kayıtları, başarımlar ve üretilen soru
  geçmişi `data/` klasöründe saklanır (bu klasör git'e dahil değildir).

## Gereksinimler

- CMake ≥ 3.20
- C++20 destekleyen bir derleyici (bu proje şu ana kadar yalnızca MSVC ile
  derlenip test edildi — aşağıdaki "Cross-Platform Notlar" bölümüne bakın)

## Derleme

```bash
cmake -B build
cmake --build build
```

## Çalıştırma

Windows/MSVC (çok yapılandırmalı generator) üzerinde:
```bash
./build/Debug/CppMasterConsole.exe
```
Tek yapılandırmalı generatorlerde (Makefiles, Ninja):
```bash
./build/CppMasterConsole
```

## Testleri çalıştırma

```bash
ctest --test-dir build --output-on-failure
```
veya test binary'sini doğrudan çalıştırarak:
```bash
./build/Debug/CppMasterConsoleTests.exe
```

Test paketi standart kütüphane dışında hiçbir bağımlılık kullanmaz; kendi
kendini kaydeden (`TEST_CASE`), basit bir test çatısı `tests/TestRunner.h`
içinde tanımlıdır.

## Proje yapısı

```
src/              Uygulama kaynak kodu (CppMasterConsoleLib statik kütüphanesi + main.cpp)
tests/            Birim testleri (CppMasterConsoleTests hedefi)
data/             Kullanıcının ilerleme/istatistik dosyaları (git'e dahil değil)
docs/superpowers/ Geliştirme süreci: tasarım dokümanları (specs/) ve uygulama planları (plans/)
```

## Test kapsamı hakkında

`src/` altındaki saf mantık ve dosya-kalıcılık sınıflarının tamamı (ör.
`QuizEngine`, `LevelSystem`, `UserProgress`, `ProgressManager`,
`MistakeTracker`, `AchievementTracker`, `QuestionHistory`,
`QuestionGenerationEngine`, her iki soru üreteci, `QuestionManager`,
`LessonManager`) birim testleriyle kapsanır. `Application` ve `ConsoleUI`
(etkileşimli, klavyeden girdi bekleyen kısımlar) bilinçli olarak birim
testi kapsamı dışında bırakıldı — bunlar, projenin geliştirme sürecinde her
fazda kullanılan, tam beklenen çıktıyı önceden hesaplayarak doğrulayan elle
hazırlanmış giriş senaryolarıyla (`docs/superpowers/plans/` içindeki her
fazın planında görülebilir) doğrulanmaya devam ediyor.

## Cross-Platform Notlar

Bu proje şu ana kadar yalnızca MSVC/Windows ortamında derlenip
çalıştırıldı. Kod, bilinen hiçbir MSVC'ye özgü yapı kullanmıyor ve tek
platforma özgü davranışını (`konsolu temizleme komutu` ve UTF-8 kod
sayfası ayarı, `src/ConsoleUI.cpp`) `#ifdef _WIN32` ile izole ediyor;
GCC/Clang veya Linux/macOS uyumluluğu ise kod incelemesiyle değerlendirildi
ama bu geliştirme ortamında böyle bir derleyici/işletim sistemi bulunmadığı
için gerçek bir derlemeyle doğrulanmadı.
