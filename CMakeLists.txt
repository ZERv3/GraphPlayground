cmake_minimum_required(VERSION 3.28)
project(untitled3)

set(CMAKE_CXX_STANDARD 23)

add_executable(graph_play sources/main.cpp
        include/Sequences/Sequence.h
            include/Sequences/BinaryHeap.hpp
            include/Sequences/DynamicArray.hpp
            include/Sequences/LinkedList.hpp
            include/Sequences/PriorityQueue.hpp
            include/Sequences/Queue.hpp
            include/Sequences/PriorityQueue.hpp
        include/Hash/Functional.h
        include/Hash/HashTable.h
        include/Hash/HashTableIO.h
        include/ObjectClasses/Attribute/Attribute.h
        include/ObjectClasses/Attribute/AttributeGen.h
        include/ObjectClasses/Attribute/AttributeIO.h
        include/ObjectClasses/Attribute/Time/Time.h
        include/ObjectClasses/Attribute/Time/TimeTypes.h
        include/ObjectClasses/Attribute/Metrics/Metrics.h
        include/ObjectClasses/Attribute/Metrics/MetricsTypes.h
        include/ObjectClasses/Attribute/Currency/Currency.h
        include/ObjectClasses/Attribute/Currency/CurrencyTypes.h
        include/Graph/Edge/Edge.h
        include/Graph/Edge/EdgeIO.h
        include/Graph/Graph/DirectedGraph.h
        include/Graph/Graph/GraphVis.h
        include/Graph/Graph/IGraph.h
        include/Sequences/LinkedListIO.hpp
        include/Graph/Algorithms/Algorithms.h
        include/Generators/GraphGen.h
        include/Interface/Dialog/IDialog.h
        include/Interface/Dialog/MacOSDialog.h
        include/Interface/Dialog/TerminalDialog.h
        include/Interface/DialogInterface.h
        include/Interface/FuncTestsInterface.h
        include/Interface/GraphFileInterface.h
        include/Interface/GraphHandInterface.h
        include/Interface/GraphHandWrite.h
        include/Interface/Interface.h
        include/Tests/LoadTests.h
        include/Tests/FuncTests.h
        include/Interface/InterfaceStrings.h
        include/Interface/LoadTestsInterface.h
        sources/CTMMap.cpp
        sources/InterfaceStrings.cpp
        sources/TransportIO.cpp
)
