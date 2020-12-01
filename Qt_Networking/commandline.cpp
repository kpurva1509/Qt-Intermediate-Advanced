#include "commandline.h"

commandline::commandline(QObject *parent, FILE* filehandle) : QObject(parent), cin(filehandle)
{

}

void commandline::monitor() {

    while(true) {
        QString value = cin.readLine();
        emit command(value);
    }
}
