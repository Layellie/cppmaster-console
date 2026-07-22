#include "GeneratorCatalog.h"

#include "generators/ArithmeticOperatorPredictGenerator.h"
#include "generators/ArrayElementPredictGenerator.h"
#include "generators/BoolOutputPredictGenerator.h"
#include "generators/ClassMemberPredictGenerator.h"
#include "generators/ForLoopSumPredictGenerator.h"
#include "generators/FunctionReturnPredictGenerator.h"
#include "generators/IfElsePredictGenerator.h"
#include "generators/InheritanceOverridePredictGenerator.h"
#include "generators/IntArithmeticPredictGenerator.h"
#include "generators/MapLookupPredictGenerator.h"
#include "generators/ModOperatorPredictGenerator.h"
#include "generators/PointerDereferencePredictGenerator.h"
#include "generators/SortWithLambdaPredictGenerator.h"
#include "generators/StringConcatPredictGenerator.h"
#include "generators/TryCatchPredictGenerator.h"
#include "generators/VectorPushBackPredictGenerator.h"
#include "generators/WhileLoopCountPredictGenerator.h"

std::vector<std::unique_ptr<IQuestionGenerator>> makeAllGenerators() {
    std::vector<std::unique_ptr<IQuestionGenerator>> generators;
    generators.reserve(17);

    generators.push_back(std::make_unique<IntArithmeticPredictGenerator>());
    generators.push_back(std::make_unique<BoolOutputPredictGenerator>());
    generators.push_back(std::make_unique<ArithmeticOperatorPredictGenerator>());
    generators.push_back(std::make_unique<ModOperatorPredictGenerator>());
    generators.push_back(std::make_unique<IfElsePredictGenerator>());
    generators.push_back(std::make_unique<ForLoopSumPredictGenerator>());
    generators.push_back(std::make_unique<WhileLoopCountPredictGenerator>());
    generators.push_back(std::make_unique<ArrayElementPredictGenerator>());
    generators.push_back(std::make_unique<VectorPushBackPredictGenerator>());
    generators.push_back(std::make_unique<StringConcatPredictGenerator>());
    generators.push_back(std::make_unique<FunctionReturnPredictGenerator>());
    generators.push_back(std::make_unique<PointerDereferencePredictGenerator>());
    generators.push_back(std::make_unique<ClassMemberPredictGenerator>());
    generators.push_back(std::make_unique<InheritanceOverridePredictGenerator>());
    generators.push_back(std::make_unique<MapLookupPredictGenerator>());
    generators.push_back(std::make_unique<SortWithLambdaPredictGenerator>());
    generators.push_back(std::make_unique<TryCatchPredictGenerator>());

    return generators;
}
