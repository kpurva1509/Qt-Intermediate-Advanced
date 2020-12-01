#include "test3.h"

test3::test3(QObject *parent) : QObject(parent)
{
    qInfo() << "Object constructed";
}

test3::~test3()
{
    qInfo() << "Object Destroyed";
}
