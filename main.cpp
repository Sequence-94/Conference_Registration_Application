#include <QCoreApplication>
#include "person.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Person person("John Doe", "University of Doom","john.doe@gmail.com");

    qDebug()<<person.toString();

    return a.exec();
}




