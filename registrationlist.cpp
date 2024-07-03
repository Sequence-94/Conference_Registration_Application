#include "registrationlist.h"
#include <QDebug>
#include <QMetaProperty>
#include <QMetaObject>

// Add a registration to the list, check for duplicates
bool RegistrationList::addRegistration(Registration *r)
{
    for (const auto& reg : m_AttendeeList) {
        if (reg->getAttendee()->getEmail() == r->getAttendee()->getEmail() &&
            reg->getAttendee()->getName() == r->getAttendee()->getName()) {
            return false; // duplicate
        }
    }
    m_AttendeeList.append(r);
    qDebug() << "Added: " << r->getAttendee()->getName();
    return true;
}

// Destructor, clean up memory
RegistrationList::~RegistrationList()
{
    qDeleteAll(m_AttendeeList);
    m_AttendeeList.clear();
}

// Check if a person is registered by name
bool RegistrationList::isRegistered(QString n) const
{
    for (const auto& reg : m_AttendeeList) {
        if (reg->getAttendee()->getName() == n) {
            qDebug() << "Names: -> " << reg->getAttendee()->getName();
            return true;
        }
    }
    return false;
}

// Calculate the total fee for a given type of registration
double RegistrationList::totalFee(QString type) const
{
    double total = 0.0;
    if (type == "Standard") {
        type = "Registration";
    }
    if (type == "Student") {
        type = "StudentRegistration";
    }
    if (type == "Guest") {
        type = "GuestRegistration";
    }

    for (const auto& reg : m_AttendeeList) {
        const QMetaObject* metaObj = reg->metaObject();
        QString regtype = metaObj->className();

        if (type == "All") {
            total += reg->calculateFee();
        } else if (regtype == type) {
            total += reg->calculateFee();
        }
    }
    return total;
}

// Count total registrations by affiliation
int RegistrationList::totalRegistrations(QString a) const
{
    int count = 0;
    for (const auto& reg : m_AttendeeList) {
        if (reg->getAttendee()->getAffiliation() == a) {
            count++;
        }
    }
    return count;
}

// Get the list of all registrations
const QList<Registration *> &RegistrationList::getAttendeeList() const
{
    return m_AttendeeList;
}
