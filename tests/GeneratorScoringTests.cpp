#include "GeneratorScoring.h"

#include "TestRunner.h"

TEST_CASE(GeneratorScoring_UntriedGeneratorReturnsNeutralPrior) {
    GeneratorScoring scoring;
    CHECK(scoring.successRate("NeverTried") == 0.5);
}

TEST_CASE(GeneratorScoring_TracksSuccessRateCorrectly) {
    GeneratorScoring scoring;
    scoring.recordAttempt("GenA", true);
    scoring.recordAttempt("GenA", true);
    scoring.recordAttempt("GenA", true);
    scoring.recordAttempt("GenA", false);
    CHECK(scoring.successRate("GenA") == 0.75);
}

TEST_CASE(GeneratorScoring_DifferentGeneratorsTrackedIndependently) {
    GeneratorScoring scoring;
    scoring.recordAttempt("GenA", true);
    scoring.recordAttempt("GenB", false);
    CHECK(scoring.successRate("GenA") == 1.0);
    CHECK(scoring.successRate("GenB") == 0.0);
}
