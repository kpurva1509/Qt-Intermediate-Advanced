#include "test2.h"

test2::test2(QObject *parent) : QObject(parent)
{

}

void test2::useWidget()
{
    if(!widget.data()){
        qInfo() << "No data";
        return;
    }

    qInfo() << "widget:" << widget.data();
    widget.data()->setObjectName("Used Widget");
}
