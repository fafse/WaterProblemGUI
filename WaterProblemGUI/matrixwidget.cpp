#include "matrixwidget.h"
#include "ui_matrixwidget.h"

MatrixWidget::MatrixWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MatrixWidget)
{
    ui->setupUi(this);
}

MatrixWidget::~MatrixWidget()
{
    if(startMatrix)
        for (int i = 0; i < lines; ++i) {
                delete[] startMatrix[i];
        }
    delete[] startMatrix;
    delete ui;
}

void MatrixWidget::resetMatrix()
{
    for(int i = 0; i < lines; i++)
        for(int j = 0; j< columns; j++)
            startMatrix[i][j]=-1;
}

bool MatrixWidget::validateNumber(int number)
{
    if(number>100||number<1)
        return false;
    return true;
}

bool MatrixWidget::validateMatrix()
{
    for(int i = 0; i < lines; i++)
        for(int j = 0; j< columns; j++)
        {
            if(!validateNumber(startMatrix[i][j]))
                return false;
        }
    return true;
}

void MatrixWidget::setParams(int lines, int columns)
{
    if(!validateNumber(lines)||!validateNumber(columns))
        return;
    this->lines=lines;
    this->columns=columns;
    try {
        testcase = *TestCase::createObj(lines,columns);                 //Проверка на правильное создание тест-кейса
    }  catch (std::runtime_error &e) {
        QMessageBox::warning(this,"Ошибка при инициализации",e.what());

    }
    try                                                                 //Выделение памяти для матрицы отображения
    {
        startMatrix = new int * [lines];
        for (int i = 0; i < lines; ++i) {
            startMatrix[i] = new int[columns];
        }
        resetMatrix();
    }catch (const std::bad_alloc &e)
    {
        QMessageBox::warning(this,"Ошибка при выделении памяти",e.what());
        if(startMatrix)                                                 //Если не удалось создать, то очищаем остатки
            for (int i = 0; i < lines; ++i) {
                    delete[] startMatrix[i];
            }
        delete[] startMatrix;
        throw;
    }
    ui->tableMatrixWidget->clear();                                    //Подготовка виджета перед отображением
    ui->tableMatrixWidget->setRowCount(lines);
    ui->tableMatrixWidget->setColumnCount(columns);
    if (mode) {                                                         // Отображение данных в соответствии с режимом
        // Режим с QTableWidget
        selectTableWidget();
    } else {
        // Режим с QPlainTextEdit
        selectPlainText();
    }
}


void MatrixWidget::enterFromTableWidget()
{
    for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < columns; ++j) {
            QTableWidgetItem *item = ui->tableMatrixWidget->item(i, j);                     //Получение данных из ячеек
            if (item) {
                bool conversionOk=false;
                int value;
                if(item->text()!="")
                    value = item->text().toInt(&conversionOk);                             //Проверка на правильный ввод
                if (conversionOk&&validateNumber(value)) {
                    startMatrix[i][j] = value;
                }
            }
        }
    }
}

void MatrixWidget::enterFromPlainText()
{
    QString text = ui->MatrixPlainEdit->toPlainText();

    if (text.isEmpty()) {
        return;
    }

    text.replace(QRegularExpression("\\s+"), " ");
    text.replace(QRegularExpression("\\s*\n"), " ");
    text.remove(QRegularExpression("[^0-9\\s]"));

    QStringList elements = text.split(QRegularExpression("\\s+"), QString::SkipEmptyParts);

    int index = 0;
    for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (index < elements.size()) {
                bool conversionOk = false;
                int value = elements.at(index).toInt(&conversionOk);
                if (conversionOk && validateNumber(value)) {
                    startMatrix[i][j] = value;
                    ++index;
                }
            }
        }
    }
}

void MatrixWidget::selectPlainText()
{
    QString formattedText;
    for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < columns; ++j) {
            if(!validateNumber(startMatrix[i][j])) continue;
            formattedText += QString::number(startMatrix[i][j]);
            if (j < columns - 1) {
                formattedText += " ";
            }
        }
        formattedText += "\n";
    }
    ui->MatrixPlainEdit->setPlainText(formattedText);
    ui->MatrixPlainEdit->show();
    ui->tableMatrixWidget->hide();
}

void MatrixWidget::selectTableWidget()
{
    ui->tableMatrixWidget->clear();
    ui->tableMatrixWidget->setRowCount(lines);
    ui->tableMatrixWidget->setColumnCount(columns);
    for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < columns; ++j) {
            if(!validateNumber(startMatrix[i][j])) continue;
            QTableWidgetItem *item = new QTableWidgetItem(QString::number(startMatrix[i][j]));
            ui->tableMatrixWidget->setItem(i, j, item);
        }
    }
    ui->tableMatrixWidget->show();
    ui->MatrixPlainEdit->hide();
}

void MatrixWidget::on_modeCheckBox_stateChanged(int arg1)
{
    resetMatrix();                                          //обнуляем матрицу перед новой записью
    if (mode) {
        // Режим с QTableWidget
        enterFromTableWidget();
    } else {
        // Режим с QPlainTextEdit
        enterFromPlainText();
    }

    mode = arg1;                                                                                // Обновляем режим

    if (mode) {
        // Отображение данных в соответствии с режимом
        // Режим с QTableWidget
        selectTableWidget();
    } else {
        // Режим с QPlainTextEdit
        selectPlainText();
    }
}

void MatrixWidget::on_getResultButton_clicked()
{
    resetMatrix();
    if(mode) {
    // Режим с QTableWidget
        enterFromTableWidget();
    }else {
        // Режим с QPlainTextEdit
        enterFromPlainText();
    }
    //TODO:кидать exception если число не так введено
    if(!validateMatrix())
    {
        QMessageBox::warning(this,"Ошибка","Проверьте данные матрицы на соответствие условиям");
        return;
    }
    testcase.reset();
    testcase.enterValues(startMatrix);
    testcase.solveTask();
    ui->resultLabel->setText("Результат: "+QString::number(testcase.getResult()));
}
