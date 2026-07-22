#include "generators/MapLookupPredictGenerator.h"

#include <array>
#include <random>
#include <string>

#include "TestRunner.h"

namespace {

int parseField(const std::string& signature, const std::string& field) {
    const std::string marker = field + "=";
    const std::size_t start = signature.find(marker) + marker.size();
    const std::size_t end = signature.find(';', start);
    const std::string token =
        end == std::string::npos ? signature.substr(start) : signature.substr(start, end - start);
    return std::stoi(token);
}

}  // namespace

TEST_CASE(MapLookupPredictGenerator_TopicIdIsEightyFour) {
    MapLookupPredictGenerator generator;
    CHECK(generator.topicId() == 84);
}

TEST_CASE(MapLookupPredictGenerator_FixedSeedIsDeterministic) {
    MapLookupPredictGenerator generator;
    std::mt19937_64 engineA{14141ULL};
    std::mt19937_64 engineB{14141ULL};
    const auto first = generator.generate(engineA, GenerationStage::Normal);
    const auto second = generator.generate(engineB, GenerationStage::Normal);
    CHECK(first.has_value());
    CHECK(second.has_value());
    CHECK(first->exactSignature == second->exactSignature);
}

TEST_CASE(MapLookupPredictGenerator_NormalStageIndexShapeMatchesSlotRule) {
    MapLookupPredictGenerator generator;
    std::mt19937_64 engine{5ULL};
    for (int iteration = 0; iteration < 300; ++iteration) {
        const auto candidate = generator.generate(engine, GenerationStage::Normal);
        CHECK(candidate.has_value());
        CHECK(candidate->question.topicId == 84);
        CHECK(candidate->exactSignature.find(";shape=index;") != std::string::npos);

        const int slot = parseField(candidate->exactSignature, "slot");
        CHECK(slot >= 0);
        CHECK(slot <= 3);
        const int answer = std::stoi(candidate->question.acceptedAnswers.front());
        if (slot == 3) {
            CHECK(answer == 0);
        } else {
            const std::array<int, 3> values = {
                parseField(candidate->exactSignature, "v0"), parseField(candidate->exactSignature, "v1"),
                parseField(candidate->exactSignature, "v2")};
            CHECK(answer == values[static_cast<std::size_t>(slot)]);
        }
    }
}

TEST_CASE(MapLookupPredictGenerator_StructuralVariationFindShapeMatchesSlotRule) {
    MapLookupPredictGenerator generator;
    std::mt19937_64 engine{99ULL};
    for (int iteration = 0; iteration < 300; ++iteration) {
        const auto candidate = generator.generate(engine, GenerationStage::StructuralVariation);
        CHECK(candidate.has_value());
        CHECK(candidate->exactSignature.find(";shape=find;") != std::string::npos);

        const int slot = parseField(candidate->exactSignature, "slot");
        const std::string answer = candidate->question.acceptedAnswers.front();
        if (slot == 3) {
            CHECK(answer == "bulunamadi");
        } else {
            CHECK(answer == "bulundu");
        }
    }
}

TEST_CASE(MapLookupPredictGenerator_SemanticSignatureExcludesVariableNameOnly) {
    MapLookupPredictGenerator generator;
    std::mt19937_64 engine{7ULL};
    const auto candidate = generator.generate(engine, GenerationStage::Normal);
    CHECK(candidate.has_value());
    CHECK(candidate->exactSignature.find("var=") != std::string::npos);
    CHECK(candidate->semanticSignature.find("var=") == std::string::npos);
}
