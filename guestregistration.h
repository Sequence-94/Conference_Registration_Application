#ifndef GUESTREGISTRATION_H
#define GUESTREGISTRATION_H

#include "registration.h"
#include <QString>

class GuestRegistration : public Registration
{
    Q_OBJECT
private:
    QString m_Category;


public:
    GuestRegistration(Person* a, QString c);
    double calculateFee() const override;
    QString toString() const override;
};

#endif // GUESTREGISTRATION_H
