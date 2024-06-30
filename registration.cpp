#include "registration.h"

Registration::Registration(QObject *parent)
    : QObject{parent}
{}


const double Registration::STANDARD_FEE = 100.0;

Registration::Registration(Person* a)
{
    m_Attendee = a;
}

Person* Registration::getAttendee() const
{
    return m_Attendee;
}

QDate Registration::getBookingDate() const
{
    return QDate::currentDate();
}

double Registration::calculateFee() const
{
    return STANDARD_FEE;
}

QString Registration::toString() const
{
    return "Booking Date:" + getBookingDate().toString() +  " Fee:R" + QString::number(calculateFee());
}




