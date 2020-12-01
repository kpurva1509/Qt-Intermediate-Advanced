#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#include <QObject>
#include <QDebug>
#include <QTextStream>
#include <QtConcurrent>
#include <QThread>
#include <QDateTime>

class commandline : public QObject
{
    Q_OBJECT
public:
    explicit commandline(QObject *parent = nullptr, FILE* filehandle = nullptr);

    [[noreturn]] void monitor();

signals:
    void command(QString value);

public slots:
    QTextStream cin;


};

#endif // COMMANDLINE_H
