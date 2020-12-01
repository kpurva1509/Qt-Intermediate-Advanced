#ifndef WIDGET_H
#define WIDGET_H

#include <QObject>
#include <QString>
#include "test.h"

class widget : public QObject
{
    Q_OBJECT
public:
    explicit widget(QObject *parent = nullptr);
    void make_changes(QString name);

signals:

};

#endif // WIDGET_H
