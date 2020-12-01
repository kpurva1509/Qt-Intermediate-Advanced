#include "test.h"

test *test::create_instance()
{
    return new test();
}

test::test(QObject *parent) : QObject(parent)
{

}

test *test::instance()
{
    return Singleton<test>::instance(test::create_instance);
}
