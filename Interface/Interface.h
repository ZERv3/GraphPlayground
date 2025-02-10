#pragma once

#include "GraphHandInterface.h"
#include "LoadTestsInterface.h"
#include "FuncTestsInterface.h"

template <typename TMark, typename TRoad, typename TAttributes>
class Interface {
public:
    void run(){
        bool running = true;
        while(running){
            bool handMenu = false;
            bool loadMenu = false;
            try {
                int choice = Ask(InterfaceStrings::title + InterfaceStrings::mainMenuTitle + InterfaceStrings::mainMenuOptions + InterfaceStrings::askChoice, 0, 3);
                system("clear");
                switch(choice){
                    case 0:
                        running = false;
                        break;
                    case 1:
                        handMenu = true;
                        break;
                    case 2:
                        FunctionalTestsInterface<TMark, TRoad, TAttributes>::RunTests();
                        break;
                    case 3:
                        loadMenu = true;
                        break;
                    default:
                        break;
                        
                }
                if(handMenu){
                    GraphHandInterface<TMark, TRoad, TAttributes> handInterface;
                    handInterface.run();
                }
                if(loadMenu){
                    LoadTestsInterface<TMark, TRoad, TAttributes> loadInterface;
                    loadInterface.run();
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
