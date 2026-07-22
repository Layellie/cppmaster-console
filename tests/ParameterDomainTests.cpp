#include "ParameterDomain.h"

#include "TestRunner.h"

TEST_CASE(ParameterDomain_DrawStaysWithinBounds) {
    ParameterDomain domain{5, 10};
    std::mt19937_64 randomEngine(42);
    for (int i = 0; i < 200; ++i) {
        const int value = domain.draw(randomEngine);
        CHECK(value >= 5);
        CHECK(value <= 10);
    }
}

TEST_CASE(ParameterDomain_ExpandedCoversAndExceedsOriginalRange) {
    ParameterDomain domain{5, 10};
    const ParameterDomain expanded = domain.expanded();
    CHECK(expanded.min < domain.min);
    CHECK(expanded.max > domain.max);
}

TEST_CASE(ParameterDomain_ExpandedOfSinglePointDomainStillWidens) {
    ParameterDomain domain{7, 7};
    const ParameterDomain expanded = domain.expanded();
    CHECK(expanded.min < 7);
    CHECK(expanded.max > 7);
}
