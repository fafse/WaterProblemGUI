/**
 * @file mainwindow.h
 * @brief Заголовочный файл класса MainWindow
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор
     * @param parent Родительский виджет
     */
    MainWindow(QWidget *parent = nullptr);
    /**
     * @brief Деструктор
     */
    ~MainWindow();
private:

private slots:
    /**
     * @brief Обработчик нажатия на кнопку для заполнения матрицы
     */
    void on_answerButton_clicked();

private:
    Ui::MainWindow *ui; ///< Указатель на объект интерфейса
};
#endif // MAINWINDOW_H
