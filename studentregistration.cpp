#include "studentregistration.h"

// Constructor for StudentRegistration, initializes base class and m_Qualification
StudentRegistration::StudentRegistration(Person* a, QString q): Registration(a)
{
    m_Qualification = q;
}

// Calculate fee for student, which is half the standard fee
double StudentRegistration::calculateFee() const
{
    return STANDARD_FEE / 2;
}

// Convert StudentRegistration details to string
QString StudentRegistration::toString() const
{
    return Registration::toString() + " Qualification:" + m_Qualification + " (Student)";
}
