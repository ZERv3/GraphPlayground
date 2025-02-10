#pragma once

#include "../Tests/FuncTests.h"

template<typename TMark, typename TRoad, typename TAttributes>
class FunctionalTestsInterface{
public:
    static void RunTests(){
        FunctionalTests<TMark, TRoad, TAttributes>::FuncLoadFromFileTest();
        FunctionalTests<TMark, TRoad, TAttributes>::FuncCreateVertexTest();
        FunctionalTests<TMark, TRoad, TAttributes>::FuncCreateEdgeTest();
        FunctionalTests<TMark, TRoad, TAttributes>::FuncDijkstraTest();
        FunctionalTests<TMark, TRoad, TAttributes>::FuncBFSTest();
        FunctionalTests<TMark, TRoad, TAttributes>::FuncDFSTest();
        std::cout << "\n[Все тесты успешно пройдены!]\n";
    }
};
