#ifndef PERSON_H
#define PERSON_H

#include <QObject>
#include <QString>

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


    void setName(const QString &newName);

    void setAffiliation(const QString &newAffiliation);

    void setEmail(const QString &newEmail);

private:
    QString m_Name;
    QString m_Affiliation;
    QString m_Email;
signals:
};

#endif // PERSON_H
