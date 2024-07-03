#include "person.h"

// Constructor for Person class
Person::Person(QObject *parent)
    : QObject{parent}
{}

// Constructor for Person with name, affiliation, and email
Person::Person(QString n, QString a, QString e)
{
    m_Name = n;
    m_Affiliation = a;
    m_Email = e;
}

// Get the name of the person
QString Person::getName() const
{
    return m_Name;
}

// Get the affiliation of the person
QString Person::getAffiliation() const
{
    return m_Affiliation;
}

// Get the email of the person
QString Person::getEmail() const
{
    return m_Email;
}

// Convert Person details to string
QString Person::toString() const
{
    return "Name:" + getName() + " Affiliation:" + getAffiliation() + " Email:" + getEmail();
}

// Set the name of the person
void Person::setName(const QString &newName)
{
    m_Name = newName;
}


// Set the affiliation of the person
void Person::setAffiliation(const QString &newAffiliation)
{
    m_Affiliation = newAffiliation;
}

// Set the email of the person

void Person::setEmail(const QString &newEmail)
{
    m_Email = newEmail;
}




