#include "guestregistration.h"

// Constructor for GuestRegistration, initializes base class and m_Category
GuestRegistration::GuestRegistration(Person* a, QString c): Registration(a)
{
    m_Category = c;
}

// Calculate fee for guest, which is 10% of the standard fee
double GuestRegistration::calculateFee() const
{
    return STANDARD_FEE * 0.1;
}

// Convert GuestRegistration details to string
QString GuestRegistration::toString() const
{
    return Registration::toString() + " Category:" + m_Category + " (Guest)";
}
