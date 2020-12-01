#ifndef TEST2_H
#define TEST2_H

#include <QObject>
#include <QPointer>
#include <QDebug>

/* QPointer is a templated class which provides guarded pointers to QObject.
 * We msy not be abble to control the pointer in consumer class
 */

class test2 : public QObject
{
    Q_OBJECT
public:
    explicit test2(QObject *parent = nullptr);

    /* Memeber variable widget */
    QPointer<QObject> widget;

    void useWidget();

signals:

public slots:

};

#endif // TEST2_H
