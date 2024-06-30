#include "person.h"

Person::Person(QObject *parent)
    : QObject{parent}
{}

Person::Person(QString n, QString a, QString e)
{
    m_Name = n;
    m_Affiliation = a;
    m_Email = e;
}

QString Person::getName() const
{
    return m_Name;
}

QString Person::getAffiliation() const
{
    return m_Affiliation;
}

QString Person::getEmail() const
{
    return m_Email;
}

QString Person::toString() const
{

    return "Name:" + m_Name + " Email:" + m_Email + " Affiliation:" + m_Affiliation;
}
