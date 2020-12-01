#include <QCoreApplication>
#include <QDebug>
#include <QPointer>
#include <QSharedPointer>
#include "test.h"
#include "test2.h"
#include "test3.h"
#include "test4.h"
#include "consumer.h"

void useScopedPointerExample(test3* obj) {
    if(!obj) return;
    qInfo() << "Using " << obj;
}

void useScopedPointerReferenceExample(QScopedPointer<test3>& mypointer) {
    qInfo() << "Using " << mypointer;
}

void createScopedPointerExample() {
    QScopedPointer<test3> mypointer(new test3);
    useScopedPointerExample(mypointer.data());
    // useScopedPointerReferenceExample(mypointer.data());
}

/* Creating a shared pointer to test and consumer
 * createPointer() creates pointer to a shared obj
 * makeConsumer() creates a pointer to the consumer
 * object.
 * Consumer has a data memeber of the type test4
 * This member is swapped with the newly created
 * object from createPointer() */

void doDeleteLater(test4* obj) {
    qInfo() << "Deleting " << obj;
    obj->deleteLater();
}

QSharedPointer<test4> createPointer() {
    test4* t = new test4();
    t->setObjectName("Test Object - 4");
    QSharedPointer<test4> p(t, doDeleteLater);
    return p;
}

void doStuff(QSharedPointer<Consumer> ptr) {
    qInfo() << "In function: " << ptr.data()->tester;
    ptr.clear();
}

QSharedPointer<Consumer> makeConsumer() {
    QSharedPointer<Consumer> c(new Consumer,&QObject::deleteLater);
    QSharedPointer<test4> t = createPointer();
    c.data()->tester.swap(t);
    doStuff(c);

    return c;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Section - 1, Lecture - 1 (Parent-child relationship)

    /* Manually assigning memory on the heap */
    /* Pass a reference to the application */
    /* Once the application closes, memory is reclaimed automatically */
    /* test* p = new test(nullptr); // bad practice */
    test* p = new test(&a);

    p->setObjectName("parent");

    for(int i=0; i<5; i++){
        p->makeChild(QString::number(i));
    }

    /* delete p; not required, as application closes and tears down */


    // Section - 1, Lecture - 2(QPointer)

    QObject* obj = new QObject(nullptr);
    obj->setObjectName("my Object");
    QPointer<QObject> p2(obj);

    test2 t2;
    t2.widget = p2;
    t2.useWidget();

    if(p2.data()){
        qInfo() << p2.data();
    }

    delete p2;
    t2.useWidget();


    // Section - 1, Lecture - 3(QScopedPointer)

    for(int i=0; i<10; i++) {
        createScopedPointerExample();
    }


    // Section - 1, Lecture - 4(QSharedPointer)

    QSharedPointer<Consumer> consume = makeConsumer();
    qInfo() << "In main " << consume.data()->tester;

    return a.exec();
}
