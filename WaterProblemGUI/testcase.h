/**
 * @file testcase.h
 * @brief Заголовочный файл класса TestCase
 */
#ifndef TESTCASE_H
#define TESTCASE_H
#include "cuboid.h"
#include "nullmatrixexception.h"
#include <QDebug>

#define INF 999999

class TestCase
{
public:
    /**
     * @brief Статический массив, указывающий направления для обхода кубоида
     */
    static const int directions[4];
    /**
     * @brief Метод для создания объекта TestCase
     * @param lines Количество строк матрицы
     * @param col Количество столбцов матрицы
     * @return Указатель на созданный объект TestCase
     */
    static TestCase* createObj(int lines, int col);
    /**
     * @brief Конструктор по умолчанию
     */
    TestCase();
    /**
     * @brief Деструктор
     */
    ~TestCase();
    /**
     * @brief Копирование значений матрицы в текущий тест-кейс
     * @param startMatrix Матрица кубоидов, заданная в условии
     */
    void enterValues(int** startMatrix);
    /**
     * @brief Получение результата обработки тест-кейса
     * @return Сумму дюймов воды в лужах
     */
    int getResult() {return sum;}
    /**
     * @brief Обработка тест-кейса
     */
    void solveTask();
    /**
     * @brief Сброс тест-кейса до изначального положения
     */
    void reset();
private:
    Cuboid** matrix;     ///< Двумерный массив кубоидов
    int lines,           ///< Количество строк матрицы
    col,                 ///< Количество столбцов матрицы
    sum;                 ///< Сумма дюймов воды в лужах

    /**
     * @brief Конструктор, задающий параметры
     * @param lines Количество строк матрицы
     * @param col Количество столбцов матрицы
     */
    TestCase(int lines, int col);
    /**
     * @brief Создание границ, используя условия задачи
     * @param curCuboid Текущий кубоид
     */
    void makeBorders(Cuboid curCuboid);
    /**
     * @brief Поиск кубоида, с минимальной границей
     * @return Минимальный кубоид
     */
    Cuboid findMinCuboid();
    /**
     * @brief Заполнение луж
     * @param curCuboid Текущий кубоид
     */
    void fillPool(Cuboid curCuboid);//заполнение луж
};

#endif // TESTCASE_H
