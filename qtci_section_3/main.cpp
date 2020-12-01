#include <QCoreApplication>
#include <QDebug>
#include <QVector>
#include <QList>
#include <QHash>
#include <QString>
#include <QSet>
#include <QMap>
#include <QLinkedList>
#include <QSettings>
#include <QStringList>
#include <QRandomGenerator>

void saveAge(QSettings* settings, QString group, QString name, int age) {
    settings->beginGroup(group);
    settings->setValue(name, age);
    settings->endGroup();
}

int getAge(QSettings* settings, QString group, QString name) {
    settings->beginGroup(group);
    if(!settings->contains(name)){
        qWarning() << "Does not contain " << name << " in the group " << group;
        settings->endGroup();
        return 0;
    }

    bool okay;
    int value = settings->value(name).toInt(&okay);

    if(!okay){
        qWarning() << "Conversion unsuccessful";
        return 0;
    }
    return value;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Section - 3, Lecture - 10(QSettings)
    QCoreApplication::setOrganizationName("VoidRealms");
    QCoreApplication::setOrganizationDomain("VoidRealms.com");
    QCoreApplication::setApplicationName("Tester");

    /* Organization can have multiple applications */
    /* Applications provide scoping like namespace */
    QSettings settings(QCoreApplication::organizationName(),QCoreApplication::applicationName());

    /* QString&& key, QVariant&& value */
    settings.setValue("custom_key", 123);

    /* Read the setting */
    qInfo() << settings.value("custom_key").toString();
    qInfo() << settings.value("custom_key").toInt();


    // Section - 3, Lecture - 11(Groups in QSettings)
    saveAge(&settings, "people", "one", 15);
    saveAge(&settings, "people","two", 25);

    qInfo() << getAge(&settings, "people", "one");

    // Section - 3, Lecture - 12(Navigating in groups)
    QStringList people;
    people << "First" << "Second" << "Third";
    foreach(QString item, people){
        /* QRandomGenerator is a singleton */
        /* Returns a pointer to singleton object */
        int value = QRandomGenerator::global()->bounded(100);
        saveAge(&settings, "test", item, value);
    }

    settings.sync();

    return a.exec();
}
