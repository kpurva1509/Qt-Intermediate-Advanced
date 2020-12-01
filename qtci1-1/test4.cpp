#include "test4.h"

test4::test4(QObject *parent) : QObject(parent)
{
    qInfo() << "Constructed:" << this;
}

test4::~test4()
{
    qInfo() << "Destroyed: " << this;
}
