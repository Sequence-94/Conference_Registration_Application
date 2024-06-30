#ifndef REGISTRATIONLIST_H
#define REGISTRATIONLIST_H

#include <QList>
#include "registration.h"

class RegistrationList
{
private:
    QList<Registration*> m_AttendeeList;

public:
    bool addRegistration(Registration* r);
    ~RegistrationList();
    bool isRegistered(QString n) const;
    double totalFee(QString type) const;
    int totalRegistrations(QString a) const;
};

#endif // REGISTRATIONLIST_H
