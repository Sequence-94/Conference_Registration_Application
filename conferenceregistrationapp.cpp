#include "conferenceregistrationapp.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include "Person.h"
#include "Registration.h"
#include "StudentRegistration.h"
#include "GuestRegistration.h"
#include "registrationlistwriter.h"
#include "registrationlistreader.h"
#include <QFileDialog>
#include "RegistrationFactory.h"


ConferenceRegistrationApp::ConferenceRegistrationApp(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    // Setup inputs
    nameInput = new QLineEdit(this);
    emailInput = new QLineEdit(this);
    affiliationInput = new QLineEdit(this);
    typeInput = new QLineEdit(this);

    // Setup inputs for other functions
    checkNameInput = new QLineEdit(this);
    totalFeeTypeInput = new QLineEdit(this);
    totalRegistrationsAffiliationInput = new QLineEdit(this);

    // Setup table
    table = new QTableWidget(this);
    table->setColumnCount(4);
    table->setHorizontalHeaderLabels({"Name", "Email", "Affiliation", "Fee"});

    // Setup buttons
    QPushButton* addButton = new QPushButton("Add Registration", this);
    connect(addButton, &QPushButton::clicked, this, &ConferenceRegistrationApp::addRegistration);

    QPushButton* checkButton = new QPushButton("Check Registration", this);
    connect(checkButton, &QPushButton::clicked, this, &ConferenceRegistrationApp::checkIsRegistered);

    QPushButton* totalFeeButton = new QPushButton("Calculate Total Fee", this);
    connect(totalFeeButton, &QPushButton::clicked, this, &ConferenceRegistrationApp::calculateTotalFee);

    QPushButton* totalRegistrationsButton = new QPushButton("Calculate Total Registrations", this);
    connect(totalRegistrationsButton, &QPushButton::clicked, this, &ConferenceRegistrationApp::calculateTotalRegistrations);

    QPushButton* saveButton = new QPushButton("Save Registration List", this);
    connect(saveButton, &QPushButton::clicked, this, &ConferenceRegistrationApp::saveRegistrationList);

    QPushButton* loadButton = new QPushButton("Load Registration List", this);
    connect(loadButton, &QPushButton::clicked, this, &ConferenceRegistrationApp::loadRegistrationList);


    layout->addWidget(new QLabel("Name:"));
    layout->addWidget(nameInput);
    layout->addWidget(new QLabel("Email:"));
    layout->addWidget(emailInput);
    layout->addWidget(new QLabel("Affiliation:"));
    layout->addWidget(affiliationInput);
    layout->addWidget(new QLabel("Type (Standard/Student/Guest):"));
    layout->addWidget(typeInput);
    layout->addWidget(addButton);

    layout->addWidget(new QLabel("Check Name:"));
    layout->addWidget(checkNameInput);
    layout->addWidget(checkButton);

    layout->addWidget(new QLabel("Total Fee Type (Standard/Student/Guest/All):"));
    layout->addWidget(totalFeeTypeInput);
    layout->addWidget(totalFeeButton);

    layout->addWidget(new QLabel("Total Registrations Affiliation:"));
    layout->addWidget(totalRegistrationsAffiliationInput);
    layout->addWidget(totalRegistrationsButton);

    layout->addWidget(saveButton);
    layout->addWidget(loadButton);

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
    Registration* reg = RegistrationFactory::instance().createRegistration(type, person);


    // if (type.toLower() == "student") {
    //     reg = new StudentRegistration(person, "Qualification");
    // } else if (type.toLower() == "guest") {
    //     reg = new GuestRegistration(person, "Category");
    // } else {
    //     reg = new Registration(person);
    // }

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

void ConferenceRegistrationApp::checkIsRegistered() {
    QString name = checkNameInput->text();
    bool registered = regList.isRegistered(name);
    QMessageBox::information(this, "Check Registration",
                             registered ? "The person is registered." : "The person is not registered.");
    checkNameInput->clear();
}

void ConferenceRegistrationApp::calculateTotalFee() {
    QString type = totalFeeTypeInput->text();
    double total = regList.totalFee(type);
    QMessageBox::information(this, "Total Fee", "The total fee is: " + QString::number(total));
    totalFeeTypeInput->clear();
}

void ConferenceRegistrationApp::calculateTotalRegistrations() {
    QString affiliation = totalRegistrationsAffiliationInput->text();
    int total = regList.totalRegistrations(affiliation);
    QMessageBox::information(this, "Total Registrations", "The total number of registrations is: " + QString::number(total));
    totalRegistrationsAffiliationInput->clear();
}

void ConferenceRegistrationApp::saveRegistrationList()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save Registration List", "", "XML files (*.xml)");
    if (!filename.isEmpty()) {
        if (RegistrationListWriter::write(regList, filename)) {
            QMessageBox::information(this, "Success", "Registration list saved successfully.");
        } else {
            QMessageBox::warning(this, "Error", "Failed to save the registration list.");
        }
    }
}

void ConferenceRegistrationApp::loadRegistrationList()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open Registration List", "", "XML files (*.xml)");
    if (!filename.isEmpty()) {
        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "Error", "Failed to open the registration list file.");
            return;
        }
        RegistrationListReader reader;
        if (reader.read(&file, regList)) {
            updateTable();
            QMessageBox::information(this, "Success", "Registration list loaded successfully.");
        } else {
            QMessageBox::warning(this, "Error", "Failed to load the registration list.");
        }
    }
}
