#include "nullmatrixexception.h"
#include <QDebug>

void NullMatrixException::raise() const
{
    qDebug() << "\n: ";
    throw *this;
}
