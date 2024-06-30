#include <QCoreApplication>
#include "person.h"
#include "Registration.h"
#include "studentregistration.h"
#include "guestregistration.h"
#include "registrationlist.h"

#include <QDebug>
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Person p1("John Doe", "University", "john@example.com");
    Person p2("Jane Smith", "College", "jane@example.com");
    Person p3 ("Jack Daniels", "University", "jack@example.com");

    Registration *r1 = new Registration(&p1);
    StudentRegistration *sr1 = new StudentRegistration(&p2, "Undergraduate");
    GuestRegistration *gr1 = new GuestRegistration(&p3, "VIP");

    RegistrationList regList;

    regList.addRegistration(r1);
    regList.addRegistration(sr1);
    regList.addRegistration(gr1);

    qDebug() << "Is John Doe Registered: " << regList.isRegistered("John Doe");
    qDebug() << "Is Jane Smith Registered: " << regList.isRegistered("Jane Smith");
    qDebug() << "Is Jack Daniels Registered: " << regList.isRegistered("Jane Smith");

    qDebug() << "Total Fee (Registration): " << regList.totalFee("Registration");
    qDebug() << "Total Fee (StudentRegistration): " << regList.totalFee("StudentRegistration");
    qDebug() << "Total Fee (GuestRegistration): " << regList.totalFee("GuestRegistration");
    qDebug() << "Total Fee (All): " << regList.totalFee("All");

    qDebug() << "Total Registrations (University): " << regList.totalRegistrations("University") ;



    return a.exec();
}




