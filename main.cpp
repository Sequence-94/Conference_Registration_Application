#include <QApplication>
#include "person.h"
#include "Registration.h"
#include "studentregistration.h"
#include "guestregistration.h"
#include "registrationlist.h"
#include "conferenceregistrationapp.h"

#include <QDebug>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


    ConferenceRegistrationApp window;
    window.show();

    return app.exec();
}




