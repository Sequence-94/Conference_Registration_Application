#ifndef CONFERENCEREGISTRATIONAPP_H
#define CONFERENCEREGISTRATIONAPP_H

#include <QObject>
#include <QWidget>
#include <QTableWidget>
#include <QLineEdit>
#include "RegistrationList.h"

class ConferenceRegistrationApp : public QWidget {
    Q_OBJECT

public:
    explicit ConferenceRegistrationApp(QWidget* parent = nullptr);


private:
    RegistrationList regList;
    QTableWidget* table;
    QLineEdit* nameInput;
    QLineEdit* emailInput;
    QLineEdit* affiliationInput;
    QLineEdit* typeInput;
    QLineEdit* checkNameInput;
    QLineEdit* totalFeeTypeInput;
    QLineEdit* totalRegistrationsAffiliationInput;


private slots:
    void addRegistration();
    void updateTable();
    void checkIsRegistered();
    void calculateTotalFee();
    void calculateTotalRegistrations();
    void saveRegistrationList();

};

#endif // CONFERENCEREGISTRATIONAPP_H
