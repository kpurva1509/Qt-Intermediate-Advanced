#ifndef TEST_H
#define TEST_H

#include <QObject>

class test : public QObject
{
public:
    explicit test(QObject *parent = nullptr);

signals:

};

#endif // TEST_H
