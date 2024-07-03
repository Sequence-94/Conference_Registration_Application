#include "registrationlistwriter.h"

// Write registration list to an XML file
bool RegistrationListWriter::write(const RegistrationList &regList, const QString &filename)
{
    QDomDocument doc;
    QDomElement root = doc.createElement("registrationlist");
    doc.appendChild(root);

    // Loop through all registrations and create XML elements for each
    for(const auto& reg : regList.getAttendeeList()){
        QDomElement regElem = createRegistrationElement(doc, reg);
        root.appendChild(regElem);
    }

    // Write the XML document to file
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        return false;
    }

    QTextStream stream(&file);
    stream << doc.toString();
    file.close();

    return true;
}

// Create XML element for a registration
QDomElement RegistrationListWriter::createRegistrationElement(QDomDocument &doc, const Registration *reg)
{
    QDomElement regElem = doc.createElement("registration");
    regElem.setAttribute("type", reg->metaObject()->className());

    QDomElement personElem = createPersonElement(doc, reg->getAttendee());
    regElem.appendChild(personElem);

    QDomElement dateElem = doc.createElement("bookingdate");
    dateElem.appendChild(doc.createTextNode(reg->getBookingDate().toString()));
    regElem.appendChild(dateElem);

    QDomElement feeElem = doc.createElement("registrationfee");
    feeElem.appendChild(doc.createTextNode(QString::number(reg->calculateFee())));
    regElem.appendChild(feeElem);

    return regElem;
}

// Create XML element for a person
QDomElement RegistrationListWriter::createPersonElement(QDomDocument &doc, const Person *person)
{
    QDomElement personElem = doc.createElement("attendee");

    QDomElement nameElem = doc.createElement("name");
    nameElem.appendChild(doc.createTextNode(person->getName()));
    personElem.appendChild(nameElem);

    QDomElement affElem = doc.createElement("affiliation");
    affElem.appendChild(doc.createTextNode(person->getAffiliation()));
    personElem.appendChild(affElem);

    QDomElement emailElem = doc.createElement("email");
    emailElem.appendChild(doc.createTextNode(person->getEmail()));
    personElem.appendChild(emailElem);

    return personElem;
}
