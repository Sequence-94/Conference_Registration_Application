#ifndef REGISTRATION_H
#define REGISTRATION_H

#include "Person.h"
#include <QObject>
#include <QString>
#include <QDate>

class Registration : public QObject
{
    Q_OBJECT
public:
    explicit Registration(QObject *parent = nullptr);
    static const double STANDARD_FEE;
    Registration(Person* a);
    Person* getAttendee() const;
    QDate getBookingDate() const;
    virtual double calculateFee() const;
    virtual QString toString() const;


private:
    Person *m_Attendee;
    QDate m_BookingDate;



signals:
};

#endif // REGISTRATION_H
