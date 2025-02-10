#pragma once

#include <fstream>

#include "../Graph/Graph/DirectedGraph.h"
//Пример реализации городской транспортной системы
#include "../ObjectClasses/TransportIO.h" //Система обозначений дорог и метод
using namespace TransportMapper;

#include "../ObjectClasses/CTM.h"
#include "../ObjectClasses/CTMMap.h" //Система параметров (стоимость, время, расстояние)
using namespace AttributeMapper;

#include "../ObjectClasses/Mark/MarkIO.h" //Абстрактный тип меток (вершин графа)
#include "../ObjectClasses/Road/RoadIO.h" //Абстрактный тип дорог (ребер графа)



template<class TMark, class TRoad, typename TAttributes>
class GraphFileInterface{
public:
    static void SaveGraphToFile(DirectedGraph<TMark, TRoad>& graph, const std::string& filename = "out.txt") {
        std::ofstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Ошибка открытия файла для сохранения");
        }

        // Запись вершин
        auto verts = graph.GetVertices();
        file << verts.GetLength() << "\n";
        for (int i = 0; i < verts.GetLength() ; i++){
            auto v = verts.GetElement(i);
            file << "(<" << v.GetType() << ">, "
            << v.GetValue() << ")"<< "\n";
        }

        // Запись рёбер
        auto edges = graph.GetEdges();
        file << edges.GetLength() << "\n";
        for(int i = 0; i < edges.GetLength(); i++) {
            auto v1 = *(edges.GetElement(i).GetSourceVertex());
            auto v2 = *(edges.GetElement(i).GetEndVertex());
            auto w = edges.GetElement(i).GetWeight();
            auto wattr = w.GetAttributes();
            file << "{(<" << v1.GetType() << ">, " << v1.GetValue() << ")"<< ", ";
            file << "(<" << v2.GetType() << ">, " << v2.GetValue() << ")"<< ", ";
            file << "(<" << w.GetType() << ">, " << wattr.GetCost().GetValue() << ", " << wattr.GetDistance().GetValue() << ", " << wattr.GetTime().GetValue() << ")}"<< "\n";
        }

        file.close();
    }


    static std::tuple<std::string, std::string, std::string> ParseEdgeString(const std::string& input) {
        std::stringstream ss(input);
        std::string source, dest, weight;

        if (ss.peek() == '{') ss.get(); // Пропускаем '{'
        
        std::getline(ss, source, ')'); source += ")";
        ss.ignore(2); // Пропускаем ", "
        
        std::getline(ss, dest, ')'); dest += ")";
        ss.ignore(2); // Пропускаем ", "
        
        std::getline(ss, weight, '}'); // Читаем до конца строки

        return {source, dest, weight};
    }

    static void LoadGraphFromFile(DirectedGraph<TMark, TRoad>& graph, HashTable<std::pair<std::string, std::string>, TMark*>& vertices, const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Ошибка открытия файла для загрузки");
        }

        graph.Clear();
        vertices.Clear();
        vertices = HashTable<std::pair<std::string, std::string>, TMark*>();

        int vertexCount, edgeCount;
        file >> vertexCount;
        file.ignore(); // Очищаем символ новой строки перед чтением строки

        // Читаем вершины
        for (int i = 0; i < vertexCount; i++) {
            TMark newMark;
            std::string input;
            std::getline(file, input);
            std::istringstream(input) >> newMark;
            
            std::string inputName, inputType;
            inputName = newMark.GetValue();
            inputType = getString(newMark.GetType());

            TMark* markInternalPtr = CreateMark(graph, newMark);
            vertices.Add(std::pair<std::string, std::string>({inputName, inputType}), markInternalPtr);
        }

        file >> edgeCount;
        file.ignore();
                
        // Читаем рёбра
        for (int i = 0; i < edgeCount; i++) {
                std::string input;
                std::getline(file, input);
                
                if (input.empty()) continue; // Пропускаем пустые строки

                auto [sourceStr, destStr, weightStr] = ParseEdgeString(input);

                // Парсим вершины
                std::istringstream sourceStream(sourceStr), destStream(destStr);
                std::string sourceName, sourceType, destName, destType;
                sourceStream.ignore(2); // Пропускаем "(<"
                std::getline(sourceStream, sourceType, '>'); // Читаем тип
                sourceStream.ignore(2); // Пропускаем ">, "
                std::getline(sourceStream, sourceName, ')'); // Читаем имя

                destStream.ignore(2);
                std::getline(destStream, destType, '>');
                destStream.ignore(2);
                std::getline(destStream, destName, ')');

                // Проверка наличия вершин в таблице
                std::pair<std::string, std::string> sourceKey = {sourceName, sourceType};
                std::pair<std::string, std::string> destKey = {destName, destType};

                if (!vertices.Contains(sourceKey) || !vertices.Contains(destKey)) {
                    throw std::runtime_error("Ошибка данных: несоответствие вершин");
                }

                // Парсим ребро
                TRoad road;
                std::istringstream weightStream(weightStr);
                std::string roadType;
                double cost, distance, time;

                weightStream.ignore(2); // Пропускаем "(<"
                std::getline(weightStream, roadType, '>');
                weightStream.ignore(2);
                weightStream >> cost;
                weightStream.ignore(2);
                weightStream >> distance;
                weightStream.ignore(2);
                weightStream >> time;

                std::string roadInput = "(<" + roadType + ">," + std::to_string(cost) + ", " +
                                        std::to_string(distance) + ", " + std::to_string(time) + ")";
                std::istringstream(roadInput) >> road;

                // Добавляем ребро в граф
                ConnectMarks(graph, vertices.GetValue(sourceKey), vertices.GetValue(destKey), road);
            }

        file.close();
    }
};

