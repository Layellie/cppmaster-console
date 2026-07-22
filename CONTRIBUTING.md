# Katkıda bulunma / Contributing

_Türkçe aşağıda — English below._

---

## Türkçe

Katkılar memnuniyetle karşılanır. Küçük düzeltmeler için doğrudan pull
request açabilirsin; büyük değişiklikler için önce bir issue açıp fikri
tartışmak zaman kaybını önler.

### Geliştirme ortamı

- CMake ≥ 3.20
- C++20 destekleyen bir derleyici (MSVC 2022+, GCC 11+, Clang 14+)

```bash
cmake -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

### Pull request açmadan önce

1. **Derleme uyarısız olmalı.** Proje MSVC'de `/W4 /permissive-`,
   GCC/Clang'de `-Wall -Wextra -Wpedantic -Wconversion -Wshadow` ile
   derlenir. Yeni uyarı eklemeyin.
2. **Tüm testler geçmeli:** `ctest --test-dir build --output-on-failure`
3. **Yeni davranış için test ekleyin.** Saf mantık ve dosya-kalıcılık
   sınıflarının tamamı test kapsamındadır; yeni bir kural/hesaplama
   ekliyorsanız testi de gelmelidir.
4. **Soru üreticisi eklediyseniz**, ayrıca stres testini çalıştırın:
   `./build/Debug/CppMasterConsoleStressTests.exe`

### Kod stili

`.clang-format` dosyası projenin stilini tanımlar (4 boşluk girinti, 100
karakter satır sınırı, Google tabanlı). Editörünüz destekliyorsa
formatlamayı ona bırakın.

- Sınıf üyeleri sonda alt çizgi: `questions_`
- Sabitler `k` öneki: `kExamPassThreshold`
- Kullanıcıya görünen tüm metinler **Türkçe**; kod içi yorumlar **İngilizce**
- Yorumlar "ne" değil "neden" anlatmalı — kodun kendisi zaten "ne"yi söyler

### İçerik katkısı (ders/soru)

Ders içerikleri `src/LessonContentSectionN.cpp`, sorular
`src/QuestionsSectionN.cpp` dosyalarında. Her konunun **en az 29 sorusu**
olmalı ve soru id'leri boşluksuz/tekrarsız olmalıdır — bunu doğrulayan
testler mevcuttur, eklemeden önce çalıştırın.

---

## English

Contributions are welcome. For small fixes, open a pull request directly;
for larger changes, please open an issue first to discuss the idea.

### Development setup

- CMake ≥ 3.20
- A C++20 compiler (MSVC 2022+, GCC 11+, Clang 14+)

```bash
cmake -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

### Before opening a pull request

1. **The build must be warning-free.** The project compiles with
   `/W4 /permissive-` on MSVC and
   `-Wall -Wextra -Wpedantic -Wconversion -Wshadow` on GCC/Clang.
2. **All tests must pass:** `ctest --test-dir build --output-on-failure`
3. **Add tests for new behavior.** All pure-logic and persistence classes
   are covered; new rules or calculations should arrive with tests.
4. **If you added a question generator**, also run the stress suite:
   `./build/Debug/CppMasterConsoleStressTests.exe`

### Code style

`.clang-format` defines the project style (4-space indent, 100-column
limit, Google-based). Let your editor apply it if it can.

- Class members use a trailing underscore: `questions_`
- Constants use a `k` prefix: `kExamPassThreshold`
- All user-facing strings are **Turkish**; code comments are **English**
- Comments should explain *why*, not *what* — the code already says what

### Content contributions (lessons/questions)

Lesson content lives in `src/LessonContentSectionN.cpp` and questions in
`src/QuestionsSectionN.cpp`. Every topic needs **at least 29 questions**,
and question ids must stay contiguous and unique — tests enforce both, so
run them before submitting.
