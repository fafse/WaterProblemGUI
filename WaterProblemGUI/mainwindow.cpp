#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "matrixwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->matrixWidget->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_answerButton_clicked()
{
    qDebug() << "I CLICKED";
    int lines,rows;
    bool isInt[2];
    lines=ui->linesArgslineEdit->text().toInt(&isInt[0]);           //Получение аргументов из интерфейса
    rows=ui->columnsArgslineEdit->text().toInt(&isInt[1]);
    if(isInt[0]&&isInt[1]&&lines<=100&&rows<=100&&lines>0&&rows>0)    //проверка на соответствие изначальным условиям задачи
    {
            ui->matrixWidget->setParams(lines,rows);                //Открытие виджета с заданными параметрами
            ui->matrixWidget->show();
    }else
    {
        QMessageBox::warning(this,"Ошибка","Строки и столбцы должны быть числом от 1 до 100");
    }

}

