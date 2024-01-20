/**
 * @file matrixwidget.h
 * @brief Заголовочный файл класса MatrixWidget
 */
#ifndef MATRIXWIDGET_H
#define MATRIXWIDGET_H

#include <QWidget>
#include <QMessageBox>
#include <QLineEdit>
#include <QRegularExpression>
#include "testcase.h"

/**
 * @brief Класс для представления матрицы и выполнения операций над ней
 *
 * Этот класс предоставляет интерфейс для ввода и отображения матрицы,
 * а также выполнения операций над матрицей.
 */

namespace Ui {
class MatrixWidget;
}

class MatrixWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор класса MatrixWidget
     * @param parent Родительский виджет
     */
    explicit MatrixWidget(QWidget *parent = nullptr);
    /**
     * @brief Деструктор класса MatrixWidget
     */
    ~MatrixWidget();
    /**
     * @brief Метод для настроек параметров матрицы
     * @param lines Количество строк матрицы
     * @param columns Количество столбцов матрицы
     */
    void setParams(int lines, int columns);

private slots:
    /**
     * @brief Слот для обработки изменения текущего режима
     * @param arg1 Новое состояние флажка
     */
    void on_modeCheckBox_stateChanged(int arg1);
    /**
     * @brief Слот для обработки нажатия кнопки получения результата
     */
    void on_getResultButton_clicked();

private:
    Ui::MatrixWidget *ui;   ///< Интерфейс виджета
    TestCase testcase;      ///< Тест-кейс
    int lines=0,            ///< Колиечество строк матрицы
    columns=0,              ///< Количество столбцов матрицы
    mode=0;                 ///< Текущий режим вывода интерфейса
    int** startMatrix;      ///< Матрица отображения, используемая дла ввода/вывода на интерфейс данных
    /**
     * @brief Обнуляет матрицу
     */
    void resetMatrix();
    /**
     * @brief Переносит данные из виджета с таблицей в матрицу отображения
     */
    void enterFromTableWidget();
    /**
     * @brief Переносит данные из виджета с текстом в матрицу отображения
     */
    void enterFromPlainText();
    /**
     * @brief Проверка матрицы на соответствие условиям задачи
     * @return Флаг, отображающий, подходит ли матрица условиям задачи
     */
    bool validateMatrix();
    /**
     * @brief Проверка числа на соответствие условиям задачи
     * @param number Проверяемое число
     * @return Флаг, оторбажающий, подходит ли число под условия задачи
     */
    bool validateNumber(int number);
    /**
     * @brief Выбрать режим отображения виджета с таблицой
     */
    void selectTableWidget();
    /**
     * @brief Выбрать режим отображения виджета с текстом
     */
    void selectPlainText();
};

#endif // MATRIXWIDGET_H
