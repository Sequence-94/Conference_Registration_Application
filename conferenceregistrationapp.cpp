#include "conferenceregistrationapp.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include "Person.h"
#include "Registration.h"
#include "StudentRegistration.h"
#include "GuestRegistration.h"

ConferenceRegistrationApp::ConferenceRegistrationApp(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout* layout = new QVBoxLayout(this);

// Setup inputs
nameInput = new QLineEdit(this);
emailInput = new QLineEdit(this);
affiliationInput = new QLineEdit(this);
typeInput = new QLineEdit(this);

// Setup table
table = new QTableWidget(this);
table->setColumnCount(4);
table->setHorizontalHeaderLabels({"Name", "Email", "Affiliation", "Fee"});

// Setup buttons
QPushButton* addButton = new QPushButton("Add Registration", this);
connect(addButton, &QPushButton::clicked, this, &ConferenceRegistrationApp::addRegistration);

layout->addWidget(new QLabel("Name:"));
layout->addWidget(nameInput);
layout->addWidget(new QLabel("Email:"));
layout->addWidget(emailInput);
layout->addWidget(new QLabel("Affiliation:"));
layout->addWidget(affiliationInput);
layout->addWidget(new QLabel("Type (Standard/Student/Guest):"));
layout->addWidget(typeInput);
layout->addWidget(addButton);
layout->addWidget(table);

setLayout(layout);
updateTable();
}

void ConferenceRegistrationApp::addRegistration() {
    QString name = nameInput->text();
    QString email = emailInput->text();
    QString affiliation = affiliationInput->text();
    QString type = typeInput->text();

    Person* person = new Person(name, affiliation, email);
    Registration* reg = nullptr;
    if (type.toLower() == "student") {
        reg = new StudentRegistration(person, "Qualification");
    } else if (type.toLower() == "guest") {
        reg = new GuestRegistration(person, "Category");
    } else {
        reg = new Registration(person);
    }

    if (regList.addRegistration(reg)) {
        updateTable();
        // Clear input fields
        nameInput->clear();
        emailInput->clear();
        affiliationInput->clear();
        typeInput->clear();

    } else {
        QMessageBox::warning(this, "Error", "Duplicate registration!");
    }
}

void ConferenceRegistrationApp::updateTable() {
    table->setRowCount(0);
    for (const auto& reg : regList.getAttendeeList()) {
        int row = table->rowCount();
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(reg->getAttendee()->getName()));
        table->setItem(row, 1, new QTableWidgetItem(reg->getAttendee()->getEmail()));
        table->setItem(row, 2, new QTableWidgetItem(reg->getAttendee()->getAffiliation()));
        table->setItem(row, 3, new QTableWidgetItem(QString::number(reg->calculateFee())));
    }
}
