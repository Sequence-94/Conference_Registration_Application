#include "studentregistration.h"


StudentRegistration::StudentRegistration(Person* a, QString q): Registration(a)
{
    m_Qualification = q;
}

double StudentRegistration::calculateFee() const
{
    return STANDARD_FEE/2;
}

QString StudentRegistration::toString() const
{
    return Registration::toString() + " Qualification:" + m_Qualification + " (Student)";
}
