#pragma once

#include "DialogInterface.h" //Интерфейс диалога

#include "../Tests/LoadTests.h" //Нагрузочные тесты
#include <fstream>

template<class TMark, class TRoad, typename TAttributes>
class LoadTestsInterface {
public:
    static void RunCreationLoadTest(){
        int vertexCount = Ask(InterfaceStrings::getVertexCountTitle+InterfaceStrings::askValue, 1, std::numeric_limits<int>::max());
        int edgesCount = Ask(InterfaceStrings::getEdgesCountTitle+" (до "+std::to_string(vertexCount*(vertexCount-1)+1)+")"+InterfaceStrings::askValue, 1, vertexCount*(vertexCount-1) + 1);
        double time = LoadTests<TMark, TRoad, TAttributes>::LoadCreationTest(vertexCount, edgesCount);
        std::cout << "\n[Время выполнения операции: " << time << " мс]\n";
    }
    
    static void RunGetVerticesLoadTest(){
        int vertexCount = Ask(InterfaceStrings::getVertexCountTitle+InterfaceStrings::askValue, 1, std::numeric_limits<int>::max());
        int edgesCount = Ask(InterfaceStrings::getEdgesCountTitle+" (до "+std::to_string(vertexCount*(vertexCount-1)+1)+")"+InterfaceStrings::askValue, 1, vertexCount*(vertexCount-1) + 1);
        double time = LoadTests<TMark, TRoad, TAttributes>::LoadGetVerticesTest(vertexCount, edgesCount);
        std::cout << "\n[Время выполнения операции: " << time << " мс]\n";
    }
    static void RunGetEdgesLoadTest(){
        int vertexCount = Ask(InterfaceStrings::getVertexCountTitle+InterfaceStrings::askValue, 1, std::numeric_limits<int>::max());
        int edgesCount = Ask(InterfaceStrings::getEdgesCountTitle+" (до "+std::to_string(vertexCount*(vertexCount-1)+1)+")"+InterfaceStrings::askValue, 1, vertexCount*(vertexCount-1) + 1);
        double time = LoadTests<TMark, TRoad, TAttributes>::LoadGetEdgesTest(vertexCount, edgesCount);
        std::cout << "\n[Время выполнения операции: " << time << " мс]\n";
    }
    static void RunDijkstraLoadTest(){
        int vertexCount = Ask(InterfaceStrings::getVertexCountTitle+InterfaceStrings::askValue, 1, std::numeric_limits<int>::max());
        int edgesCount = Ask(InterfaceStrings::getEdgesCountTitle+" (до "+std::to_string(vertexCount*(vertexCount-1)+1)+")"+InterfaceStrings::askValue, 1, vertexCount*(vertexCount-1) + 1);
        double time = LoadTests<TMark, TRoad, TAttributes>::LoadDijkstraTest(vertexCount, edgesCount);
        std::cout << "\n[Время выполнения операции: " << time << " мс]\n";
    }
    static void RunBFSLoadTest(){
        int vertexCount = Ask(InterfaceStrings::getVertexCountTitle+InterfaceStrings::askValue, 1, std::numeric_limits<int>::max());
        int edgesCount = Ask(InterfaceStrings::getEdgesCountTitle+" (до "+std::to_string(vertexCount*(vertexCount-1)+1)+")"+InterfaceStrings::askValue, 1, vertexCount*(vertexCount-1) + 1);
        double time = LoadTests<TMark, TRoad, TAttributes>::LoadBFSTest(vertexCount, edgesCount);
        std::cout << "\n[Время выполнения операции: " << time << " мс]\n";
    }
    static void RunDFSLoadTest(){
        int vertexCount = Ask(InterfaceStrings::getVertexCountTitle+InterfaceStrings::askValue, 1, std::numeric_limits<int>::max());
        int edgesCount = Ask(InterfaceStrings::getEdgesCountTitle+" (до "+std::to_string(vertexCount*(vertexCount-1)+1)+")"+InterfaceStrings::askValue, 1, vertexCount*(vertexCount-1) + 1);
        double time = LoadTests<TMark, TRoad, TAttributes>::LoadDFSTest(vertexCount, edgesCount);
        std::cout << "\n[Время выполнения операции: " << time << " мс]\n";
    }
    static void RunAllLoadTests(const std::string& csvFileName = ""){
        
        
        int vertexMaxCount = Ask(InterfaceStrings::getVertexCountTitle+InterfaceStrings::askValue, 1, std::numeric_limits<int>::max());
        int stepCount = Ask(InterfaceStrings::getStepCountTitle+" (до "+std::to_string(vertexMaxCount)+")"+InterfaceStrings::askValue, 1, vertexMaxCount);
        int difficulty = Ask(InterfaceStrings::getDifficultyTitle+" (до 100)"+InterfaceStrings::askValue, 1, 100);
        
        std::string fileName;
        if(csvFileName == ""){
            fileName = "../Data/LoadTestResultsV" + std::to_string(vertexMaxCount) + "S" + std::to_string(stepCount) +"D" + std::to_string(difficulty)+".csv";
        }
        else fileName = csvFileName;
        
        std::ofstream outFile(fileName);
            if (!outFile.is_open()) {
                std::cerr << "Не удалось открыть файл: " << csvFileName << std::endl;
                return;
            }
            
            // Записываем заголовок CSV файла.
            outFile << "VertexCount, EdgesCount, Creation, GetVertices, GetEdges, Dijkstra, BFS, DFS\n";
        
        int vertexStep = std::round(static_cast<double>(vertexMaxCount) / stepCount);
        int vertexCount = 0;
        for(int i = 0; i < stepCount; i++){
            vertexCount += vertexStep;
            int edgesCount = (vertexCount * (vertexCount - 1) * difficulty) / 200;
            double creationTime = LoadTests<TMark, TRoad, TAttributes>::LoadCreationTest(vertexCount, edgesCount);
            double getVerticesTime = LoadTests<TMark, TRoad, TAttributes>::LoadGetVerticesTest(vertexCount, edgesCount);
            double getEdgesTime = LoadTests<TMark, TRoad, TAttributes>::LoadGetEdgesTest(vertexCount, edgesCount);
            double dijkstraTime, bfsTime, dfsTime;
            LoadTests<TMark, TRoad, TAttributes>::LoadAlgorithmsTests(vertexCount, edgesCount, dijkstraTime, bfsTime, dfsTime);
            
            outFile << vertexCount << ", "
                        << edgesCount << ", "
                        << creationTime << ", "
                        << getVerticesTime <<  ", "
                        << getEdgesTime <<  ", "
                        << dijkstraTime <<  ", "
                        << bfsTime <<  ", "
                        << dfsTime <<  "\n";
//            std::cout << vertexCount << ", "
//                        << edgesCount << ", "
//                        << creationTime << ", "
//                        << getVerticesTime <<  ", "
//                        << getEdgesTime <<  ", "
//                        << dijkstraTime <<  ", "
//                        << bfsTime <<  ", "
//                        << dfsTime <<  "\n";
            std::cout << "|";
            
        }
        outFile.close();
        for(int i = 0; i < stepCount; i++) std::cout << "\b";
        std::cout << "\n[Данные успешно сохранены в " << fileName << "]\n";
    }
    void run(){
        bool running = true;
        while(running){
            try {
                int choice = Ask(InterfaceStrings::title + InterfaceStrings::loadTestsMenuTitle + InterfaceStrings::loadTestsMenuOptions + InterfaceStrings::askChoice, 0, 7);
                system("clear");
                switch(choice){
                    case 0:
                        running = false;
                        break;
                    case 1:
                        RunCreationLoadTest();
                        break;
                    case 2:
                        RunGetVerticesLoadTest();
                        break;
                    case 3:
                        RunGetEdgesLoadTest();
                        break;
                    case 4:
                        RunDijkstraLoadTest();
                        break;
                    case 5:
                        RunBFSLoadTest();
                        break;
                    case 6:
                        RunDFSLoadTest();
                        break;
                    case 7:
                        RunAllLoadTests();
                        break;
                    default:
                        break;
                        
                }
            } catch (const std::runtime_error& e) {
                std::cout << "[" << e.what() << "]\n";
            } catch (const std::exception& e) {
                std::cout << "[" << e.what() << "]\n";
            } catch (...) {
                std::cout << "Критическая ошибка! Программа будет завершена.\n";
                running = false;
            }
        }
    }
};

