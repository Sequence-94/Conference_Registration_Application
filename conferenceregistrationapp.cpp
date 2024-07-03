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


// Constructor for the app
ConferenceRegistrationApp::ConferenceRegistrationApp(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout* layout = new QVBoxLayout(this); // Vertical layout for the app

    // Input fields for user to enter registration details
    nameInput = new QLineEdit(this);
    emailInput = new QLineEdit(this);
    affiliationInput = new QLineEdit(this);
    typeInput = new QLineEdit(this);

    // Input fields for other functions
    checkNameInput = new QLineEdit(this);
    totalFeeTypeInput = new QLineEdit(this);
    totalRegistrationsAffiliationInput = new QLineEdit(this);

    // Setup the table for displaying registrations
    table = new QTableWidget(this);
    table->setColumnCount(4);
    table->setHorizontalHeaderLabels({"Name", "Email", "Affiliation", "Fee"});

    // Add a button to add a new registration
    QPushButton* addButton = new QPushButton("Add Registration", this);
    connect(addButton, &QPushButton::clicked, this, &ConferenceRegistrationApp::addRegistration);

    // Add a button to check if someone is registered
    QPushButton* checkButton = new QPushButton("Check Registration", this);
    connect(checkButton, &QPushButton::clicked, this, &ConferenceRegistrationApp::checkIsRegistered);

    // Add a button to calculate the total fee for a type of registration
    QPushButton* totalFeeButton = new QPushButton("Calculate Total Fee", this);
    connect(totalFeeButton, &QPushButton::clicked, this, &ConferenceRegistrationApp::calculateTotalFee);

    // Add a button to calculate the total number of registrations for an affiliation
    QPushButton* totalRegistrationsButton = new QPushButton("Calculate Total Registrations", this);
    connect(totalRegistrationsButton, &QPushButton::clicked, this, &ConferenceRegistrationApp::calculateTotalRegistrations);

    // Add a button to save the registration list to a file
    QPushButton* saveButton = new QPushButton("Save Registration List", this);
    connect(saveButton, &QPushButton::clicked, this, &ConferenceRegistrationApp::saveRegistrationList);

    // Add a button to load the registration list from a file
    QPushButton* loadButton = new QPushButton("Load Registration List", this);
    connect(loadButton, &QPushButton::clicked, this, &ConferenceRegistrationApp::loadRegistrationList);

    // Adding all the widgets to the layout
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

    setLayout(layout); // Set the layout for the widget
    updateTable(); // Update the table to show any existing registrations
}

// Method to add a new registration
void ConferenceRegistrationApp::addRegistration() {
    QString name = nameInput->text(); // Get the name from the input
    QString email = emailInput->text(); // Get the email from the input
    QString affiliation = affiliationInput->text(); // Get the affiliation from the input
    QString type = typeInput->text(); // Get the type from the input

    Person* person = new Person(name, affiliation, email); // Create a new person
    Registration* reg = RegistrationFactory::instance().createRegistration(type, person); // Use the factory to create the registration

    if (regList.addRegistration(reg)) { // Add the registration to the list
        updateTable(); // Update the table to show the new registration
        // Clear input fields
        nameInput->clear();
        emailInput->clear();
        affiliationInput->clear();
        typeInput->clear();
    } else {
        QMessageBox::warning(this, "Error", "Duplicate registration!"); // Show an error if the registration is a duplicate
    }
}

// Method to update the table with the latest registration details
void ConferenceRegistrationApp::updateTable() {
    table->setRowCount(0); // Clear the table
    for (const auto& reg : regList.getAttendeeList()) { // Loop through all registrations
        int row = table->rowCount();
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(reg->getAttendee()->getName())); // Set the name
        table->setItem(row, 1, new QTableWidgetItem(reg->getAttendee()->getEmail())); // Set the email
        table->setItem(row, 2, new QTableWidgetItem(reg->getAttendee()->getAffiliation())); // Set the affiliation
        table->setItem(row, 3, new QTableWidgetItem(QString::number(reg->calculateFee()))); // Set the fee
    }
}

// Method to check if a person is registered
void ConferenceRegistrationApp::checkIsRegistered() {
    QString name = checkNameInput->text(); // Get the name from the input
    bool registered = regList.isRegistered(name); // Check if they are registered
    QMessageBox::information(this, "Check Registration",
                             registered ? "The person is registered." : "The person is not registered."); // Show a message box with the result
    checkNameInput->clear(); // Clear the input field
}

// Method to calculate the total fee for a type of registration
void ConferenceRegistrationApp::calculateTotalFee() {
    QString type = totalFeeTypeInput->text(); // Get the type from the input
    double total = regList.totalFee(type); // Calculate the total fee
    QMessageBox::information(this, "Total Fee", "The total fee is: " + QString::number(total)); // Show a message box with the result
    totalFeeTypeInput->clear(); // Clear the input field
}

// Method to calculate the total number of registrations for an affiliation
void ConferenceRegistrationApp::calculateTotalRegistrations() {
    QString affiliation = totalRegistrationsAffiliationInput->text(); // Get the affiliation from the input
    int total = regList.totalRegistrations(affiliation); // Calculate the total number of registrations
    QMessageBox::information(this, "Total Registrations", "The total number of registrations is: " + QString::number(total)); // Show a message box with the result
    totalRegistrationsAffiliationInput->clear(); // Clear the input field
}

// Method to save the registration list to a file
void ConferenceRegistrationApp::saveRegistrationList()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save Registration List", "", "XML files (*.xml)"); // Open a save file dialog
    if (!filename.isEmpty()) { // If a file was selected
        if (RegistrationListWriter::write(regList, filename)) { // Write the registration list to the file
            QMessageBox::information(this, "Success", "Registration list saved successfully."); // Show a success message
        } else {
            QMessageBox::warning(this, "Error", "Failed to save the registration list."); // Show an error message if it failed
        }
    }
}

// Method to load the registration list from a file
void ConferenceRegistrationApp::loadRegistrationList()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open Registration List", "", "XML files (*.xml)"); // Open an open file dialog
    if (!filename.isEmpty()) { // If a file was selected
        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) { // Try to open the file
            QMessageBox::warning(this, "Error", "Failed to open the registration list file."); // Show an error message if it failed
            return;
        }
        RegistrationListReader reader;
        if (reader.read(&file, regList)) { // Read the registration list from the file
            updateTable(); // Update the table with the loaded registrations
            QMessageBox::information(this, "Success", "Registration list loaded successfully."); // Show a success message
        } else {
            QMessageBox::warning(this, "Error", "Failed to load the registration list."); // Show an error message if it failed
        }
    }
}
