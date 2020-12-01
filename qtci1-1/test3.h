#ifndef TEST3_H
#define TEST3_H

#include <QObject>
#include <QDebug>

class test3 : public QObject
{
    Q_OBJECT
public:
    explicit test3(QObject *parent = nullptr);
    ~test3();

signals:

public slots:

};

#endif // TEST3_H
