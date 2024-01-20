#include "testcase.h"

const int TestCase::directions[4]= {0,0,1,-1};

TestCase::TestCase()
{
    matrix = nullptr;
    lines = col = sum=0;
}

TestCase::TestCase(int lines, int col) : sum(0)
{
    this->lines = lines;
    this->col = col;
    try
    {
        matrix = new Cuboid * [lines];
        for (int i = 0; i < lines; ++i) {
            matrix[i] = new Cuboid[col];
        }
    }catch (const std::bad_alloc &e)
    {
        qDebug() << "MEMORY ALLOCATION ERROR " << e.what() << "/n";
        if(matrix)
            for (int i = 0; i < lines; ++i) {
                    delete[] matrix[i];
            }
        delete[] matrix;
        throw;
    }
}

TestCase::~TestCase()
{
    if(matrix)
        for (int i = 0; i < lines; ++i) {
                delete[] matrix[i];
        }
    delete[] matrix;
}

void TestCase::reset()
{
    sum=0;
}

void TestCase::enterValues(int** startMatrix)
{
    NullMatrixException matrixException;
    if(matrix==nullptr||this->matrix==nullptr)
        matrixException.raise();
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < col; j++) {
            this->matrix[i][j] = Cuboid(i, j, startMatrix[i][j]);
        }
    }
}

TestCase* TestCase::createObj(int lines, int col)
{
    if (lines < 1 || lines>100 || col < 1 || col>100)
    {
        throw std::runtime_error("Wrong parametrs");
    }
    try {
        return new TestCase(lines, col);
    }
    catch (const std::bad_alloc& e)
    {
        throw std::runtime_error("Error creating test case");
    }
}

void TestCase::solveTask()
{
    if(matrix==nullptr){
        sum=-1;
        return;
    }
    //проход по границам
    for (int i = 0; i < lines; i++)
    {
        if (!matrix[i][0].isVisited)
            makeBorders(matrix[i][0]);
        if (!matrix[i][col - 1].isVisited)
            makeBorders(matrix[i][col - 1]);
    }
    for (int i = 0; i < col; i++)
    {
        if (!matrix[0][i].isVisited)
            makeBorders(matrix[0][i]);
        if (!matrix[lines - 1][i].isVisited)
            makeBorders(matrix[lines - 1][i]);
    }
    int repeats = 0;
    for (int i = 1; i < lines - 1; i++)
    {
        for (int j = 1; j < col - 1; j++)
        {
            if (!matrix[i][j].isVisited)
            {
                repeats++;
            }
        }
    }
    for (int i = 0; i < repeats; i++)
    {
        Cuboid tmp = findMinCuboid();
        fillPool(tmp);
    }
    for (int i = 0; i < lines; i++)//вывод и подсчёт резов
    {
        for (int j = 0; j < col; j++)
        {
            if (matrix[i][j].maxH > matrix[i][j].h) {
                sum += matrix[i][j].maxH - matrix[i][j].h;
            }
        }
        qDebug() << QString::number(sum);
    }
}


void TestCase::makeBorders(Cuboid curCuboid)//создание границ, используя условия задачи
{
    matrix[curCuboid.x][curCuboid.y].isVisited = true;
    matrix[curCuboid.x][curCuboid.y].maxH = curCuboid.h;
    for (int i = 0; i < 4; i++)//проверка соседних ячеек
    {
        int x = curCuboid.x + directions[i];
        int y = curCuboid.y + directions[3 - i];
        if (x >= 0 && x < lines && y >= 0 && y < col)
            if (curCuboid.h <= matrix[x][y].h)
                if (!matrix[x][y].isVisited)
                    makeBorders(matrix[x][y]);
    }
}

Cuboid TestCase::findMinCuboid()
{
    Cuboid minCuboid = Cuboid();
    int min = INF;
    for (int i = 1; i < lines - 1; i++)
        for (int j = 1; j < col - 1; j++)
        {
            int curMin = INF;
            if (!matrix[i][j].isVisited)
            {
                for (int t = 0; t < 4; t++)
                {
                    int x = i + directions[t];
                    int y = j + directions[3 - t];
                    if (matrix[x][y].isVisited) {
                        curMin = std::min(curMin, std::max(matrix[x][y].h, matrix[x][y].maxH));
                    }
                }
                if (minCuboid.x != -1)
                {
                    if (curMin <= min) {
                        minCuboid = matrix[i][j];
                        min = curMin;
                    }
                }
                else
                {
                    minCuboid = matrix[i][j];
                }
            }


        }

    return minCuboid;
}

void TestCase::fillPool(Cuboid curCuboid)//на основе высоты кубоидов создаются границы
{
    if (!matrix[curCuboid.x][curCuboid.y].isVisited)
    {
        int min = INF;
        for (int t = 0; t < 4; t++)
        {
            int x = curCuboid.x + directions[t];
            int y = curCuboid.y + directions[3 - t];
            min = std::min(min, std::max(matrix[x][y].h, matrix[x][y].maxH));

        }

        if (min < matrix[curCuboid.x][curCuboid.y].h)
        {
            matrix[curCuboid.x][curCuboid.y].maxH = matrix[curCuboid.x][curCuboid.y].h;
            matrix[curCuboid.x][curCuboid.y].isVisited = true;
        }
        else
            if (min < matrix[curCuboid.x][curCuboid.y].maxH)
            {
                matrix[curCuboid.x][curCuboid.y].maxH = min;
                matrix[curCuboid.x][curCuboid.y].isVisited = true;

            }
    }
}
