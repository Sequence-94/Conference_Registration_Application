#ifndef REGISTRATIONLISTWRITER_H
#define REGISTRATIONLISTWRITER_H

#include "registrationlist.h"
#include <QDomDocument>
#include <QFile>
#include <QTextStream>

class RegistrationListWriter
{
public:
    static bool write(const RegistrationList& regList, const QString& filename);

private:
    static QDomElement createRegistrationElement(QDomDocument& doc, const Registration* reg);
    static QDomElement createPersonElement(QDomDocument& doc, const Person* person);

};

#endif // REGISTRATIONLISTWRITER_H
