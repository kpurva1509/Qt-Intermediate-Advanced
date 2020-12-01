#include "counter3.h"

Counter3::Counter3(QObject *parent) : QObject(parent)
{

}

void Counter3::increment()
{
    value++;
}

void Counter3::decrement()
{
    value--;
}

int Counter3::count()
{
    return value;
}
