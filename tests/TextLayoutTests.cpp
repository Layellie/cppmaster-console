#include "TextLayout.h"

#include <string>

#include "TestRunner.h"

TEST_CASE(TextLayout_AsciiWidthMatchesByteCount) {
    CHECK(displayWidth("") == 0);
    CHECK(displayWidth("Ayarlar") == 7);
    CHECK(displayWidth("1. Test") == 7);
}

TEST_CASE(TextLayout_TurkishCharactersCountAsOneColumnNotTwoBytes) {
    // The reason this file exists: these strings are longer in bytes than on
    // screen, and the menu columns are aligned by the on-screen width.
    const std::string label = "Konuları Öğren";
    CHECK(label.size() > 14);      // 17 bytes
    CHECK(displayWidth(label) == 14);

    CHECK(displayWidth("Çıkış") == 5);
    CHECK(displayWidth("İstatistiklerim") == 15);
    CHECK(displayWidth("Günlük Tekrar") == 13);
    CHECK(displayWidth("Hatalarımı Çöz") == 14);
}

TEST_CASE(TextLayout_PadsToTheRequestedColumnWidth) {
    CHECK(padToWidth("abc", 6) == "abc   ");
    CHECK(displayWidth(padToWidth("Çıkış", 10)) == 10);
    CHECK(displayWidth(padToWidth("Konuları Öğren", 20)) == 20);
}

TEST_CASE(TextLayout_LongerTextIsLeftAloneRatherThanTruncated) {
    // A label wider than its column should push the layout, not lose
    // characters — losing them would silently corrupt a menu entry.
    CHECK(padToWidth("Kod Yazma Alıştırmaları", 5) == "Kod Yazma Alıştırmaları");
    CHECK(padToWidth("abc", 3) == "abc");
}
