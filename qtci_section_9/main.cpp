#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QString>
#include <iostream>
#include <QDir>
#include <QList>
#include <QtAlgorithms>
#include <QVector>
#include <QRandomGenerator>
#include "test.h"

#define add(a,b) a+b

void randoms(QVector<int>& mylist, int max) {

    mylist.reserve(max);
    for(int i=0; i<max; i++) {
        mylist.append(QRandomGenerator::global()->bounded(1000));
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Section - 9, Lecture - 36(qDeleteAll)

    QList<test*> mylist;

    for(int i=0; i<10; i++) {
        test* t = new test();
        t->setObjectName(QString::number(i));
        mylist.append(t);
    }

    qInfo() << mylist.at(0);

    qDeleteAll(mylist);

    mylist.clear();

    // Section - 9, Lecture - 37(qFill)

    QVector<int> myvector;
    myvector << 1 << 2 << 3;
    myvector.fill(0);

    qInfo() << myvector;

    // Section - 9, Lecture - 38(qSort)

    QVector<int> mylist2;
    randoms(mylist2, 10);

    qInfo() << "Unsorted list: " << mylist2;

    //qsort(mylist2);

    std::sort(mylist2.begin(), mylist2.end());
    qInfo() << "Sorted list: " << mylist2;

    // Section - 9, Lecture - 39(qEqual)

    QVector<int> list1;
    randoms(list1,10);

    QVector<int> list2;
    randoms(list2,10);

    qInfo() << list1;
    qInfo() << list2;

    //qInfo() << "Equal: " << qEqual(list1.begin(), list1.end(), list2.begin());
    //qCopy(list1.begin(),list1.end(), list2.begin());
    //qInfo() << "Equal: " << qEqual(list1.begin(), list1.end(), list2.begin());

    qInfo() << "Equal: " << std::equal(list1.begin(), list1.end(), list2.begin());
    std::copy(list1.begin(),list1.end(), list2.begin());
    qInfo() << "Equal: " << std::equal(list1.begin(), list1.end(), list2.begin());

    // Section - 9, Lecture - 40(Custom Macros)

    //Easy...but dangerous
        qInfo() << add(1,2);

    //Lets break it!

    qInfo() << add("Test",22);
    qInfo() << add(true,true);
    qInfo() << add(false, true);
    qInfo() << add(false, false);
    qInfo() << add("Test",'\n');
    qInfo() << add("Test",'/n');

    return a.exec();
}
