#ifndef STUDENTREGISTRATION_H
#define STUDENTREGISTRATION_H

#include <QString>
#include "registration.h"

class StudentRegistration : public Registration
{
public:
    StudentRegistration(Person* a, QString q);
    double calculateFee() const override;
    QString toString() const override;

private:
    QString m_Qualification;

signals:
};

#endif // STUDENTREGISTRATION_H
