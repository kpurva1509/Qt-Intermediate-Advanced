#ifndef TEST_H
#define TEST_H

#include <QObject>
#include <QString>
#include "singleton.h"

class test : public QObject
{
    Q_OBJECT
    static test* create_instance();

public:
    explicit test(QObject *parent = nullptr);
    static test* instance();
    QString name;

signals:

};

#endif // TEST_H
