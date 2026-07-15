#include "FnvHash.h"

#include "TestRunner.h"

TEST_CASE(FnvHash_EmptyStringEqualsOffsetBasis) {
    CHECK(fnv1a64("") == 14695981039346656037ULL);
}

TEST_CASE(FnvHash_SameInputProducesSameHash) {
    CHECK(fnv1a64("merhaba") == fnv1a64("merhaba"));
}

TEST_CASE(FnvHash_DifferentInputProducesDifferentHash) {
    CHECK(fnv1a64("merhaba") != fnv1a64("Merhaba"));
}
