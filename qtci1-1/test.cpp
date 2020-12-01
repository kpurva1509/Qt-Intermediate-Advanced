#include "test.h"

/* Class method implementations */

test::test(QObject *parent) : QObject(parent)
{
    qInfo() << this << "Constructed";

}

test::~test() {
    qInfo() << "Destroyed";
}

void test::makeChild(QString name) {

    test* child = new test(this);
    child->setObjectName(name);
}
