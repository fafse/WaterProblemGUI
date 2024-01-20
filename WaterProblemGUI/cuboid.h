/**
 * @file cuboid.h
 * @brief Заголовочный файл класса Cuboid
 */
#ifndef CUBOID_H
#define CUBOID_H

#define INF 999999
/**
 * @class Cuboid
 * @brief Класс, для хранения информации о кубоиде
 */
class Cuboid
{
public:
    /**
     * @brief Конструктор по умолчанию
     */
    Cuboid();
    /**
     * @brief Конструктор с параметрами
     * @param x Координата x кубоида
     * @param y Координата y кубоида
     * @param h Высота кубоида
     */
    Cuboid(int x,int y,int h);

    int x=-1,               ///< Координата x кубоида
    y=-1,                   ///< Координата y кубоида
    h=-1,                   ///< Текущая высота кубоида
    maxH=INF;               ///< Максимально допустимая высота лужи с кубоидом
    bool isVisited=false;   ///< Флаг, показывающий, проверен ли текущий кубоид

};

#endif // CUBOID_H
