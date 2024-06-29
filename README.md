# Conference Registration Application

This project is a Qt-based GUI application for managing conference registrations. It supports multiple types of registrations, including standard, student, and guest registrations, with corresponding fee calculations. The application ensures no duplicate registrations and provides various querying capabilities.

## Features

- **Registration Management**: Add and manage conference registrations with support for standard, student, and guest types.
- **Fee Calculation**: Automatically calculates registration fees based on the type of registration.
- **Duplicate Prevention**: Ensures no duplicate registrations based on email and name.
- **Query Capabilities**: Check if a person is registered, calculate total fees, and count registrations by affiliation.
- **User-Friendly Interface**: Interactive GUI using Qt Widgets to display and manage registrations.

## Technologies Used

- **C++**: Core application logic.
- **Qt Framework**: GUI design and implementation, leveraging Qt's meta-object system and widgets.
- **UML Design**: Initial design based on UML class diagrams.

## Getting Started

1. **Clone the repository**:
    ```sh
    git clone https://github.com/your-username/conference-registration-app.git
    cd conference-registration-app
    ```

2. **Build the application**:
    - Ensure you have Qt and a C++ compiler installed.
    - Open the project in Qt Creator or build from the command line:
      ```sh
      qmake
      make
      ```

3. **Run the application**:
    ```sh
    ./ConferenceRegistrationApp
    ```

## License
