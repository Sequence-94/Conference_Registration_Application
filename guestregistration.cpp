#include "guestregistration.h"


GuestRegistration::GuestRegistration(Person* a, QString c): Registration(a)
{
    m_Category = c;
}

double GuestRegistration::calculateFee() const
{
    return STANDARD_FEE*0.1;
}

QString GuestRegistration::toString() const
{
    return Registration::toString() + " (Guest)";
}
