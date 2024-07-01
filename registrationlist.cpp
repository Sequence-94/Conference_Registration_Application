#include "registrationlist.h"

#include <QDebug>

#include <QMetaProperty>
#include <QMetaObject>

bool RegistrationList::addRegistration(Registration *r)
{
    for(const auto& reg : m_AttendeeList){
        if(reg->getAttendee()->getEmail() == r->getAttendee()->getEmail()
            &&
            reg->getAttendee()->getName()==r->getAttendee()->getName()){
            return false;//duplicate
        }
    }
    m_AttendeeList.append(r);
    qDebug() << "added: " << r->getAttendee()->getName();
    return true;
}


RegistrationList::~RegistrationList()
{
    qDeleteAll(m_AttendeeList);
    m_AttendeeList.clear();
}

bool RegistrationList::isRegistered(QString n) const
{

    for(const auto& reg : m_AttendeeList){
        if(reg->getAttendee()->getName() == n){
            qDebug()<<"names: -> "<<reg->getAttendee()->getName();
            return true;
        }
    }
    return false;
}

double RegistrationList::totalFee(QString type) const
{
    double total = 0.0;
    if (type == "Standard"){
        type = "Registration";
    }
    if (type == "Student"){
        type = "StudentRegistration";
    }
    if (type == "Guest"){
        type = "GuestRegistration";
    }

    for(const auto& reg : m_AttendeeList){
        const QMetaObject* metaObj = reg->metaObject();
        QString regtype = metaObj->className();

        if(type == "All"){
            total += reg->calculateFee();
        }
        else if(regtype == type){
            total += reg->calculateFee();
        }
    }
    return total;
}

int RegistrationList::totalRegistrations(QString a) const
{
    int count = 0;
    for(const auto& reg : m_AttendeeList){
        if(reg->getAttendee()->getAffiliation() == a){
            count++;
        }
    }
    return count;
}

const QList<Registration *> &RegistrationList::getAttendeeList() const
{
    return m_AttendeeList;
}

