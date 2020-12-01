#include <QCoreApplication>
#include <QDebug>
#include "test.h"
#include "widget.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    test::instance()->name = "Bryan";

        qInfo() << test::instance()->name;

        for(int i = 0; i < 5; i++) {
            widget w;
            w.make_changes("Widget: " + QString::number(i));
        }

        qInfo() << test::instance()->name;

    return a.exec();
}
