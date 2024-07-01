#ifndef CONFERENCEREGISTRATIONAPP_H
#define CONFERENCEREGISTRATIONAPP_H

#include <QObject>
#include <QWidget>
#include <QTableWidget>
#include <QLineEdit>
#include "RegistrationList.h"

class ConferenceRegistrationApp : public QWidget {
    Q_OBJECT
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
public:
    explicit ConferenceRegistrationApp(QWidget* parent = nullptr);

private slots:
    void addRegistration();
    void updateTable();
    void checkIsRegistered();
    void calculateTotalFee();
    void calculateTotalRegistrations();

};

#endif // CONFERENCEREGISTRATIONAPP_H
