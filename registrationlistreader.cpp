#include "registrationlistreader.h"
#include "StudentRegistration.h"
#include "GuestRegistration.h"
#include <QFile>
#include <QDebug>
#include "RegistrationFactory.h"

// Read registration list from an XML file
bool RegistrationListReader::read(QIODevice *device, RegistrationList &regList)
{
    QXmlStreamReader xml(device);

    if (xml.readNextStartElement()){
        if (xml.name().toString() == "registrationlist"){
            // Loop through registration elements
            while (xml.readNextStartElement()){
                qDebug() << "Second root xml name is: " << xml.name().toString();
                if (xml.name().toString() == "registration"){
                    readRegistration(xml, regList);
                } else {
                    xml.skipCurrentElement();
                }
            }
        } else {
            xml.raiseError(QObject::tr("The file is not an XML RegistrationList"));
        }
    }
    return !xml.error();
}

// Read a single registration from XML
void RegistrationListReader::readRegistration(QXmlStreamReader &xml, RegistrationList &regList)
{
    QString type = xml.attributes().value("type").toString();
    Person *person = new Person();

    // Loop through person elements
    while (xml.readNextStartElement()) {
        if (xml.name().toString() == "attendee") {
            readPerson(xml, *person);
        } else {
            xml.skipCurrentElement();
        }
    }

    // Create registration object using factory pattern
    Registration* registration = RegistrationFactory::instance().createRegistration(type, person);
    regList.addRegistration(registration);
}

// Read a person element from XML
void RegistrationListReader::readPerson(QXmlStreamReader &xml, Person &person)
{
    while (xml.readNextStartElement()) {
        if (xml.name().toString() == "name") {
            person.setName(xml.readElementText());
        } else if (xml.name().toString() == "affiliation") {
            person.setAffiliation(xml.readElementText());
        } else if (xml.name().toString() == "email") {
            person.setEmail(xml.readElementText());
        } else {
            xml.skipCurrentElement();
        }
    }
}
