#include <QCoreApplication>
#include <QDebug>
#include <QVector>
#include <QList>
#include <QHash>
#include <QString>
#include <QSet>
#include <QMap>
#include <QLinkedList>

template<typename T>
void fill(T& container) {
    for(int i=0; i<5; i++){
        container.append(i);
    }
}

template<typename T>
void display(T& container) {
    for(int i=0; i<container.length(); i++){
        if(i>0){
            auto current = reinterpret_cast<std::uintptr_t>(&container.at(i));
            auto previous = reinterpret_cast<std::uintptr_t>(&container.at(i-1));
            auto distance = current - previous;

            qInfo() << i << " at " << current << " previous " << previous << " distance " << distance;
        } else {
            qInfo() << i << &container.at(i) << "distance 0";
        }
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Section - 2, Lecture - 5(QVector v/s QList)
    QVector<int> qVector;
    QList<int> qList;

    fill(qVector);
    fill(qList);
    display(qVector);
    qInfo("");

    // Section - 2, Lecture - 6(QHash)
    QHash<QString, int> hash_entries;
    hash_entries.insert("one", 1);
    hash_entries.insert("two", 2);
    hash_entries.insert("three", 3);

    qInfo() << "Keys: " << hash_entries.keys();
    qInfo() << "Size: " << hash_entries.size();

    foreach(QString key, hash_entries.keys()) {
        qInfo() << "Key: " << hash_entries[key];
    }

    // Section - 2, Lecture -7(QSet)
    QSet<QString> myset;

    myset << "one" << "two" << "three";
    myset.insert("four");

    foreach(QString item, myset){
        qInfo() << item;
    }

    // Section - 2, Lecture -8(QMap - RB Tree Dictionary)
    QMap<QString, int> pairs;
    pairs.insert("first", 1);
    pairs.insert("second", 2);

    qInfo() << pairs.size();

    // Section - 2, Lecture - 9(QLinkedList)
    QLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    return a.exec();
}
