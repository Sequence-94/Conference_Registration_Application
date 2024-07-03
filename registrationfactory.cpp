#include "registrationfactory.h"

// Singleton pattern for RegistrationFactory
RegistrationFactory &RegistrationFactory::instance()
{
    static RegistrationFactory instance;
    return instance;
}

// Create registration object based on type
Registration *RegistrationFactory::createRegistration(const QString &type, Person *person, const QString &additionalInfo)
{
    if (type == "StudentRegistration") {
        return new StudentRegistration(person, "Qualification");
    } else if (type == "GuestRegistration") {
        return new GuestRegistration(person, "Category");
    } else {
        return new Registration(person);
    }
}
