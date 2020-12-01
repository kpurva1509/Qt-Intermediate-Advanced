#ifndef TEST4_H
#define TEST4_H

#include <QObject>
#include <QDebug>

class test4 : public QObject
{
    Q_OBJECT
public:
    explicit test4(QObject *parent = nullptr);
    ~test4();

signals:

public slots:

};

#endif // TEST4_H
