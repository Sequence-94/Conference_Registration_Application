#include "registrationlistreader.h"
#include "StudentRegistration.h"
#include "GuestRegistration.h"
#include <QFile>
#include <QDebug>
#include "RegistrationFactory.h"



bool RegistrationListReader::read(QIODevice *device, RegistrationList &regList)
{
    QXmlStreamReader xml(device);

    if(xml.readNextStartElement()){
        if(xml.name().toString()=="registrationlist"){
            while(xml.readNextStartElement()){
                qDebug()<<"second root xml name is: "<<xml.name().toString();
                if(xml.name().toString()=="registration"){
                    readRegistration(xml,regList);
                }else{
                    xml.skipCurrentElement();
                }
            }
        }else{
            xml.raiseError(QObject::tr("The File is not an XML RegistrationList"));
        }
    }
    return !xml.error();
}

void RegistrationListReader::readRegistration(QXmlStreamReader &xml, RegistrationList &regList)
{
    QString type = xml.attributes().value("type").toString();

    // Registration *registration = nullptr;
    // Registration *sregistration = nullptr;
    // Registration *gregistration = nullptr;
    Person *person = new Person();

    while (xml.readNextStartElement()) {
        if (xml.name().toString() == "attendee") {
            readPerson(xml, *person);
        } else {
            xml.skipCurrentElement();
        }
    }

    Registration* registration = RegistrationFactory::instance().createRegistration(type, person);
    regList.addRegistration(registration);

    // if (type == "Registration" && registration == nullptr) {
    //     registration = new Registration(person);
    //     regList.addRegistration(registration);
    //     //qDebug()<<"===========COUNT1==============";
    // }

    // if(type == "StudentRegistration"){
    //     sregistration = new StudentRegistration(person,"Qualification");
    //     regList.addRegistration(sregistration);
    // }

    // if(type == "GuestRegistration"){
    //     gregistration = new GuestRegistration(person,"Category");
    //     regList.addRegistration(gregistration);
    // }
}

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
