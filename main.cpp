#include <QCoreApplication>
#include "person.h"
#include "Registration.h"

#include <QDebug>
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Person p("John Doe", "University", "john@example.com");

    Registration r(&p);

    qDebug() << "Attendee: " << r.getAttendee()->toString();
    qDebug() << "Booking Date: " << r.getBookingDate().toString();
    qDebug() << "Fee: R" << r.calculateFee();
    qDebug() << "ToString: " << r.toString();

    return a.exec();
}




