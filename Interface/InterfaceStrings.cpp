#include "InterfaceStrings.h"

namespace InterfaceStrings {
    const std::string title = "\nЛабораторная №4 - Граф\n";
    const std::string getDialogTypeTitle = "Выберите формат ввода данных:\n1.Терминальный ввод\n2.Оконный (MacOS)\n";
    const std::string askChoice = "Выбор: ";
    const std::string askValue = "\nВведите значение: ";

    // Ошибки
    const std::string incorrectInput = "Некорректный ввод";
    const std::string usedKeySymbols = "Ввод содержит особые символы";
    const std::string objectTypeNotExists = "Указан несуществующий тип";
    const std::string objectExists = "Объект с указанными параметрами уже существует";
    const std::string objectNotExists = "Объекта с указанными параметрами нет";
    const std::string objectAimsSelf = "Начальный объект не может быть конечным";

    //Главное меню
    const std::string mainMenuTitle = "Главное Меню:";
    const std::string mainMenuOptions = "\n\t1. Ручное редактирование графа\n\t2. Функциональные тесты\n\t3. Нагрузочные тесты\n\t----------------------\n\t0. Завершить программу\n";

    // Меню редактирования
    const std::string handMenuTitle = "Ручное Редактирование:";
    const std::string handMenuOptions = "\n\t1. Добавить транспортную точку\n\t2. Соединить транспортные точки\n\t3. Удалить транспортную точку\n\t4. Удалить соединение транспортных точек\n\t5. Найти кратчайшее расстояние\n\t6. Сохранить граф в файл\n\t7. Загрузить граф из файла\n\t8. Сгенерировать граф\n\t9. Отрендерить граф\n\t----------------------\n\t0. Выйти из меню\n";
    
    // Меню нагрузочных тестов
    const std::string loadTestsMenuTitle = "Нагрузочные тесты:";
    const std::string loadTestsMenuOptions = "\n\t1. Создание графа\n\t2. Получение вершин\n\t3. Получение ребер\n\t4. Алгоритм Дийкстры\n\t5. Поиск в ширину\n\t6. Поиск в глубину \n\t7. Запустить все тесты\n\t----------------------\n\t0. Выйти из меню\n";
    
    // Запросы
    const std::string getObjectTypeTitle = "Введите тип";
    const std::string getObjectNameTitle = "Введите название";
    const std::string getAttributeTitle = "Введите сравнительный аттрибут";
    const std::string getVertexCountTitle = "Введите количество вершин";
    const std::string getEdgesCountTitle = "Введите количество ребер";
    const std::string getStepCountTitle = "Введите количество шагов";
    const std::string getDifficultyTitle = "Введите процент нагруженности ребрами (в %)";


    // Типы объектов
    const std::string markTypes = "Станция | Платформа | Остановка | Аэропорт";
    const std::string roadTypes = "Линия метро | Железнодорожная линия | Автобусная линия | Авиамаршрут | Пеший маршрут";
    
    const std::string attributes = "Стоимость | Метрика | Время";
}
