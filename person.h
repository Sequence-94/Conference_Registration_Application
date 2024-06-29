#ifndef PERSON_H
#define PERSON_H

#include <QObject>

class Person : public QObject
{
    Q_OBJECT
public:
    explicit Person(QObject *parent = nullptr);
    Person (QString n,QString a,QString e);
    QString getName() const;
    QString getAffiliation() const;
    QString getEmail() const;
    QString toString() const;


private:
    QString m_Name;
    QString m_Affiliation;
    QString m_Email;
signals:
};

#endif // PERSON_H