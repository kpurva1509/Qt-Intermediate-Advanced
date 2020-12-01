#include <QCoreApplication>
#include "../mylib/mylib_global.h"
#include "../mylib/mylib.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Mylib lib;
    lib.test();

    //
    return a.exec();
}
