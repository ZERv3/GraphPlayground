#pragma once

#include <iostream>
#include <limits>
#include <variant>
#include <cstdlib>

#include "DialogInterface.h"
#include "GraphFileInterface.h"

//Подключение графа
#include "GraphHandWrite.h" //Графовая структура и внутренний интерфейс
#include "../Graph/Graph/GraphVis.h" //Рендер графа с опцией выделения пути
#include "../Graph/Algorithms/Algorithms.h" //Для алгоритма дийкстры

#include "../Generators/GraphGen.h" //Генератор графа

template<class TMark, class TRoad, typename TAttributes>
class GraphHandInterface{
private:
    DirectedGraph<TMark, TRoad> graph;
    HashTable<std::pair<std::string, std::string>, TMark*> vertices;
    DialogType dialog;
    
public:
    DirectedGraph<TMark, TRoad> GetGraph() const {
        return graph;
    }
    
    static bool isConvertibleToDouble(const std::string& str) {
        std::istringstream iss(str);
        double value;
        
        // Попытка считать число
        iss >> std::noskipws >> value;

        // Проверяем, успешно ли считалось число и нет ли лишних символов
        if (iss.fail() || !iss.eof()) {
            return false;
        }

        // Проверка на положительное значение
        return value >= 0;
    }
    
    GraphHandInterface():
        graph(DirectedGraph<TMark, TRoad>()),
        vertices(HashTable<std::pair<std::string, std::string>, TMark*>()), dialog(DialogType::Terminal){}
    
    static void CheckMarkName(std::string& name) {
        if (name.find('"') != -1 || name.find('<') != -1 || name.find('>') != -1)
            throw std::runtime_error(InterfaceStrings::usedKeySymbols);
    }

    static void CheckMarkType(std::string& type) {
        if (type.find('"') != -1 || type.find('<') != -1 || type.find('>') != -1)
            throw std::runtime_error(InterfaceStrings::usedKeySymbols);
        if (!isValidGroupType(type))
            throw std::runtime_error(InterfaceStrings::objectTypeNotExists);
    }

    void CheckMarkInput(std::string& inputName,std::string& inputType, bool exists = false) {
        CheckMarkName(inputName);
        CheckMarkType(inputType);

        std::pair<std::string, std::string> inputPair = {inputName, inputType};
        if (vertices.Contains(inputPair) && !exists)
            throw std::runtime_error(InterfaceStrings::objectExists);
        if (!vertices.Contains(inputPair) && exists)
            throw std::runtime_error(InterfaceStrings::objectNotExists);
    }

    void GetMarkInput(std::string& name, std::string& type, TMark& markCreated) {
        Get(type, CheckMarkType, InterfaceStrings::getObjectTypeTitle + "\n" + InterfaceStrings::markTypes);
        Get(name, CheckMarkName, InterfaceStrings::getObjectNameTitle);

        CheckMarkInput(name, type);

        std::pair<std::string, std::string> inputPair = {name, type};
        std::string input = "(<" + type + ">," + name + ")";
        std::istringstream(input) >> markCreated;
    }

    TMark* GetMarkInput() {
        std::string inputType, inputName;
        Get(inputType, CheckMarkType, InterfaceStrings::getObjectTypeTitle + "\n" + InterfaceStrings::markTypes);
        Get(inputName, CheckMarkName, InterfaceStrings::getObjectNameTitle);

        CheckMarkInput(inputName, inputType, true);

        std::pair<std::string, std::string> inputPair = {inputName, inputType};
        return vertices.GetValue(inputPair);
    }

    TMark* GetMarkInput(std::string& name, std::string& type) {
        Get(type, CheckMarkType, InterfaceStrings::getObjectTypeTitle + "\n" + InterfaceStrings::markTypes);
        Get(name, CheckMarkName, InterfaceStrings::getObjectNameTitle);

        CheckMarkInput(name, type, true);

        std::pair<std::string, std::string> inputPair = {name, type};
        return vertices.GetValue(inputPair);
    }
    
    static void CheckRoadType(std::string& type) {
        if (type.find('"') != -1 || type.find('<') != -1 || type.find('>') != -1)
            throw std::runtime_error(InterfaceStrings::usedKeySymbols);
        if (!isValidLineType(type))
            throw std::runtime_error(InterfaceStrings::objectTypeNotExists);
    }

    static void CheckRoadValue(std::string& value) {
        if (!isConvertibleToDouble(value))
            throw std::runtime_error(InterfaceStrings::incorrectInput);
    }

    void GetRoadInput(TRoad& roadCreated) {
        std::string inputType, inputDistance, inputTime, inputCost;

        // Получение типа дороги
        Get(inputType, CheckRoadType, InterfaceStrings::getObjectTypeTitle + "\n" + InterfaceStrings::roadTypes);
        
        // Получение числовых значений
        Get(inputDistance, CheckRoadValue, "Введите дальность перемещения");
        Get(inputTime, CheckRoadValue, "Введите длительность перемещения");

        if (inputType == "Пеший маршрут") {
            inputCost = "0"; // Бесплатный вариант
        } else {
            Get(inputCost, CheckRoadValue, "Введите стоимость");
        }

        // Формируем строку и парсим в объект TRoad
        std::string input = "(<" + inputType + ">," + inputCost + ", " + inputDistance + ", " + inputTime + ")";
        std::istringstream(input) >> roadCreated;
    }
    
    void GetRoadInputToDel(TRoad& roadToDelete) {
        std::string inputType;

        // Получение типа дороги через Get
        Get(inputType, CheckRoadType, InterfaceStrings::getObjectTypeTitle + "\n" + InterfaceStrings::roadTypes);

        // Создание строки ввода для парсинга
        std::string input = "(<" + inputType + ">, 0, 0, 0)";

        // Парсим в объект TRoad
        std::istringstream(input) >> roadToDelete;
    }
    
    static void CheckRoadAttribute(std::string& attr) {
        if (attr.find('"') != -1 || attr.find('<') != -1 || attr.find('>') != -1)
            throw std::runtime_error(InterfaceStrings::usedKeySymbols);
        if (!isValidAttribute(attr)) throw std::runtime_error(InterfaceStrings::objectTypeNotExists);
    }
    
    CTMAttributes GetRoadAttributeToCompare(){
        std::string inputAttr;
        Get(inputAttr, CheckRoadAttribute, InterfaceStrings::getAttributeTitle + "\n" + InterfaceStrings::attributes);
        return ParseAttribute(inputAttr);
    }
//----------------------------------------------------------------------------
    void CreatePoint(){
        std::string inputType, inputName;
        TMark newMark;
        
        GetMarkInput(inputName, inputType, newMark);
        
        //Добавление метки в граф и хэш-таблицу меток
        TMark* markInternalPtr = CreateMark(graph, newMark);
        vertices.Add(std::pair<std::string, std::string>({inputName, inputType}), markInternalPtr);
    
    }
    
    void RemovePoint(){
        std::string inputType, inputName;
        TMark* delMark = GetMarkInput(inputType, inputName);
        
        //Удаление метки
        RemoveMark(graph, *delMark);
        vertices.Remove(std::pair<std::string, std::string>({inputName, inputType}));
    
    }
    
    void ConnectPoints(){
        TMark* sourceMark = GetMarkInput();
        TMark* destMark = GetMarkInput();
        TRoad road;
        
        if(sourceMark == destMark) throw std::runtime_error(InterfaceStrings::objectAimsSelf);
        
        GetRoadInput(road);
        
        ConnectMarks(graph, sourceMark, destMark, road);
    }
    
    void DisconnectPoints(){
        TRoad road;
        TMark* sourceMark = GetMarkInput();
        TMark* destMark = GetMarkInput();
        
        GetRoadInputToDel(road);
        
        DisconnectMarks(graph, sourceMark, destMark, road);
    }
    //---------------------------
    
    void FindShortestPath(){
        TMark* sourceMark = GetMarkInput();
        TMark* destMark = GetMarkInput();
        TRoad road;
        
        DynamicArray<Edge<TMark, TRoad>> path;
        
        CTMAttributes attribute = GetRoadAttributeToCompare();
        switch (attribute) {
            case 0:
                path = Dijkstra<CompareByCost<TAttributes, TransportLine>> ::template FindShortestPath<TMark, TRoad, TAttributes>(graph, *sourceMark, *destMark);
                break;
            case 1:
                path = Dijkstra<CompareByMetrics<TAttributes, TransportLine>> ::template FindShortestPath<TMark, TRoad, TAttributes>(graph, *sourceMark, *destMark);
                break;
            case 2:
                path = Dijkstra<CompareByTime<TAttributes, TransportLine>> ::template FindShortestPath<TMark, TRoad, TAttributes>(graph, *sourceMark, *destMark);
                break;
            default:
                break;
        }
        
        std::string outputName = "Data/GRAPH_PATH_" + ToString(attribute);
        
        RenderGraph(graph, outputName, path);
    }
    
    void GenGraph(){
        int vertexCount = Ask(InterfaceStrings::getVertexCountTitle+InterfaceStrings::askValue, 1, std::numeric_limits<int>::max());
        int edgesCount = Ask(InterfaceStrings::getEdgesCountTitle+" (до "+std::to_string(vertexCount*(vertexCount-1) + 1)+")"+InterfaceStrings::askValue, 1, vertexCount*(vertexCount-1) + 1);
        
        auto genGraph = GenerateGraph<TAttributes>(vertexCount, edgesCount);
        
        GraphFileInterface<TMark, TRoad, TAttributes>::SaveGraphToFile(genGraph, "Data/generated.txt");
        GraphFileInterface<TMark, TRoad, TAttributes>::LoadGraphFromFile(graph, vertices, "Data/generated.txt");
    }
    
    void run(){
//        int inputDialogType = Ask(InterfaceStrings::getDialogTypeTitle+InterfaceStrings::askChoice, 1, 2);
//        switch(inputDialogType){
//            case 1:
//                dialog = DialogType::Terminal;
//                break;
//            case 2:
//                dialog = DialogType::MacOS;
//                break;
//        }
        bool running = true;
        while(running){
            try {
                
                int choice = Ask(InterfaceStrings::title + InterfaceStrings::handMenuTitle + InterfaceStrings::handMenuOptions + InterfaceStrings::askChoice, 0, 9);
                system("clear");
                
                switch(choice){
                    case 1:
                        CreatePoint();
                        break;
                    case 2:
                        ConnectPoints();
                        break;
                    case 3:
                        RemovePoint();
                        break;
                    case 4:
                        DisconnectPoints();
                        break;
                    case 5:
                        FindShortestPath();
                        break;
                    case 6:
                        GraphFileInterface<TMark, TRoad, TAttributes>::SaveGraphToFile(graph, "../Data/input.txt");
                        break;
                    case 7:
                        GraphFileInterface<TMark, TRoad, TAttributes>::LoadGraphFromFile(graph, vertices, "../Data/input.txt");
                        break;
                    case 8:
                        GenGraph();
                        break;
                    case 9:
                        RenderGraph(graph, "../Data/graph_output");
                        break;
                    case 0:
                        running = false;
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

