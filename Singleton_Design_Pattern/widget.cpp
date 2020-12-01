#include "widget.h"

widget::widget(QObject *parent) : QObject(parent)
{

}

void widget::make_changes(QString name)
{

    test::instance()->name = name;
}
