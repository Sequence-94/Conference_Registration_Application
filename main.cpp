#include <QCoreApplication>
#include "person.h"
#include "Registration.h"
#include "studentregistration.h"

#include <QDebug>
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Person p("John Doe", "University", "john@example.com");

    StudentRegistration sr(&p,"Engineering");

    qDebug() << "Attendee: " << sr.getAttendee()->toString();
    qDebug() << "Fee: R" << sr.calculateFee();
    qDebug() << "ToString: " << sr.toString();

    return a.exec();
}




