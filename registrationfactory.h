#ifndef REGISTRATIONFACTORY_H
#define REGISTRATIONFACTORY_H

#include "Registration.h"
#include "StudentRegistration.h"
#include "GuestRegistration.h"
#include "Person.h"
#include <QString>

class RegistrationFactory
{
public:
   // RegistrationFactory();

    static RegistrationFactory& instance();

    Registration* createRegistration(const QString& type, Person* person, const QString& additionalInfo = "");

private:

    RegistrationFactory() {};
    ~RegistrationFactory() {};
    RegistrationFactory(const RegistrationFactory&) = delete;
    RegistrationFactory& operator=(const RegistrationFactory&) = delete;

};

#endif // REGISTRATIONFACTORY_H
