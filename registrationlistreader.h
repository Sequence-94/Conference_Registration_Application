#ifndef REGISTRATIONLISTREADER_H
#define REGISTRATIONLISTREADER_H

#include <QXmlStreamReader>
#include "registrationlist.h"

class RegistrationListReader
{

public:
    bool read(QIODevice *device, RegistrationList &regList);

private:
    void readRegistration(QXmlStreamReader &xml, RegistrationList &regList);
    void readPerson(QXmlStreamReader &xml, Person &person);
};

#endif // REGISTRATIONLISTREADER_H
