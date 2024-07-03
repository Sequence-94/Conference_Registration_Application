#include "registration.h"

// Constructor for base Registration class
Registration::Registration(QObject *parent)
    : QObject{parent}
{}

// Standard fee for registration
const double Registration::STANDARD_FEE = 100.0;

// Constructor for Registration, initialize attendee
Registration::Registration(Person* a)
{
    m_Attendee = a;
}

// Get the attendee of the registration
Person* Registration::getAttendee() const
{
    return m_Attendee;
}

// Get the booking date (current date)
QDate Registration::getBookingDate() const
{
    return QDate::currentDate();
}

// Calculate the fee for the registration
double Registration::calculateFee() const
{
    return STANDARD_FEE;
}

// Convert Registration details to string
QString Registration::toString() const
{
    return "Booking Date:" + getBookingDate().toString() +  " Fee:R" + QString::number(calculateFee());
}


