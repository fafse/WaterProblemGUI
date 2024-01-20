/**
 * @file nullmatrixexception.h
 * @brief Заголовочный файл класса NullMatrixException
 */
#ifndef NULLMATRIXEXCEPTION_H
#define NULLMATRIXEXCEPTION_H
#include <QException>
/**
 * @class NullMatrixException
 * @brief Исключение для обработки ситуации с невыделенной памятью для матрицы
 */
class NullMatrixException : public QException
{
public:
    /**
     * @brief Вызывает исключение
     */
    void raise() const override;
    /**
     * @brief Клонирует исключение
     * @return Клон исключения
     */
    NullMatrixException *clone() const override {return new NullMatrixException(*this);}
};

#endif // NULLMATRIXEXCEPTION_H
