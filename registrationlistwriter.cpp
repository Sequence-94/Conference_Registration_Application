#include "registrationlistwriter.h"

bool RegistrationListWriter::write(const RegistrationList &regList, const QString &filename)
{
    QDomDocument doc;
    QDomElement root = doc.createElement("registrationlist");
    doc.appendChild(root);

    for(const auto& reg : regList.getAttendeeList()){
        QDomElement regElem = createRegistrationElement(doc,reg);
        root.appendChild(regElem);
    }

    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        return false;
    }

    QTextStream stream(&file);
    stream << doc.toString();
    file.close();

    return true;
}

QDomElement RegistrationListWriter::createRegistrationElement(QDomDocument &doc, const Registration *reg)
{
    QDomElement regElem = doc.createElement("registration");
    regElem.setAttribute("type",reg->metaObject()->className());

    QDomElement personElem = createPersonElement(doc,reg->getAttendee());
    regElem.appendChild(personElem);

    QDomElement dateElem = doc.createElement("bookingdate");
    dateElem.appendChild(doc.createTextNode(reg->getBookingDate().toString()));
    regElem.appendChild(dateElem);

    QDomElement feeElem = doc.createElement("registrationfee");
    feeElem.appendChild(doc.createTextNode(QString::number(reg->calculateFee())));
    regElem.appendChild(feeElem);

    return regElem;
}

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
