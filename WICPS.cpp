/*
 * WICPS.cpp
 *
 * Description: Manages Patients with a database
 *
 * Last modified on: May 2017
 * Author: Brendin Green
 */

#include <iostream>
#include "Patient.h"
#include "List.h"

using namespace std;

// Adds a new Patient to the system
void add(List& patients){

    bool correctlyEntered = false;

    while (!correctlyEntered) {
        string input = "";
        cout << "Please enter a 10-digit care-card number for the new patient" << endl;
        cout << ">> ";
        cin >> input;
        if (input.length() != 10) {
            cout << "Please make sure your care card number is ten (10) digits long. " << endl;
        } else {
            Patient newPat = Patient(input);
            bool check = patients.insert(newPat);
            if (!check) {
                cout << "Something went wrong!" << endl;
            } else {
                cout << "Patient added successfully!" << endl;
                patients.printList();
            }
            correctlyEntered = true;
        }
    }
}

void remove(List& patients){

    bool correctlyEntered = false;

    while (!correctlyEntered) {

        string input = "";
        cout << "Please enter the 10-digit care-card number of the patient to be removed" << endl;
        cout << ">> ";
        cin >> input;

        if (input.length() != 10) {
            cout << "Please make sure your care card number is ten (10) digits long. " << endl;
        } else {
            Patient patToRemove = Patient(input);
            bool check = patients.remove(patToRemove);
            if (!check) {
                cout << "Something went wrong!" << endl;
            } else {
                cout << "Patient removed successfully!" << endl;
                patients.printList();
            }
            correctlyEntered = true;
        }
    }
}

// updates patient
void update(List& patients){

    bool enteredCorrectly = false;

    while (not enteredCorrectly) {
        // first find the patient
        string input = "";
        cout << "Please enter a 10-digit care-card number" << endl;
        cout << ">> ";
        cin >> input;

        if (input.length() != 10){
            cout << "Please make sure your care card number is ten (10) digits long. " << endl;
        } else {
            Patient patToFind = Patient(input);
            Patient * patient = patients.search(patToFind);

            enteredCorrectly = true;

            // Now deal with if the user was found or not
            if (!patient) {
                cout << "Unable to find patient in the database, try again\n" << endl;
            } else {

                // Deal with updating the patient
                bool editDone = false;
                while (not editDone) {

                    char editInput = 0;
                    string inputValue = "";

                    cout << "What would you like to change?" << endl;
                    cout << "(n) Name" << endl;
                    cout << "(e) Email" << endl;
                    cout << "(p) Phone" << endl;
                    cout << "(a) Address" << endl;
                    cout << "(x) End editing patient" << endl;
                    cout << ">>";
                    cin >> editInput;

                    cin.ignore();
                    switch (tolower(editInput)) {
                        case 'n' :
                            cout << "Enter a new name" << endl;
                            cout << ">>";
                            getline(cin, inputValue);
                            patient->setName(inputValue);
                            break;
                        case 'e':
                            cout << "Enter a new email" << endl;
                            cout << ">>";
                            cin >> inputValue;
                            patient->setEmail(inputValue);
                            break;
                        case 'p':
                            cout << "Enter a new phone number" << endl;
                            cout << ">>";
                            getline(cin, inputValue);
                            patient->setPhone(inputValue);
                            break;
                        case 'a':
                            cout << "Enter a new address" << endl;
                            cout << ">>";
                            getline(cin, inputValue);
                            patient->setAddress(inputValue);
                            break;
                        case 'x':
                            cout << "The patient is now: ";
                            patient->printPatient();
                            editDone = true;
                            break;
                        default:
                            cout << "That is not one of the options, try again" << endl;
                    }
                }
            }
        }
    }
}

// finds patient
void search(List& patients){

    bool enteredCorrectly = false;

    while (not enteredCorrectly) {
        string input = "";
        cout << "Please enter a 10-digit care-card number to find the patient" << endl;
        cout << ">> ";
        cin >> input;

        if (input.length() != 10){
            cout << "Please make sure your care card number is ten (10) digits long. " << endl;
        } else {
            Patient patToFind = Patient(input);
            Patient * patient = patients.search(patToFind);
            if (!patient) {
                cout << "Unable to find patient in the database" << endl;
            } else {
                cout << "This patient does exist in the database" << endl;
            }
            enteredCorrectly = true;
        }

    }


}

// prints all patients
void print(List& patients){
    if (patients.getElementCount() == 0){
        cout << "There are currently no patients within the database" << endl;
    } else {
        cout << "Our database includes: " << endl;
        patients.printList();
    }
}

// deletes all entries
void drop(List& patients) {
    if (patients.getElementCount() == 0){
        cout << "Database is already empty" << endl;
    } else {
        patients.removeAll();
        cout << "Database dropped!" << endl;
    }
}

int main() {

    // Variables declaration
    List patients = List();
    bool done = false;
    char input = 0;
    // Print menu to user
    cout << "\n----Welcome to the Walk in Clinic Patient Service!\n" << endl;

    // Keep doing what the user selects until the user exits
    while (not done) {

        cout << "--------------------------------------------------------" << endl;
        // Add a patient
        cout << "To add a patient to the database, enter: a" << endl;

        // Remove a patient
        cout << "To remove a patient from the database, enter: r" << endl;

        // Edit a patient
        cout << "To update a patient's details, enter: u" << endl;

        // Search for a patient
        cout << "To check to see if a patient exists, enter: s" << endl;

        // print all
        cout << "To show all patients in the database, enter: p" << endl;

        // print all
        cout << "To drop patients from database, enter: d" << endl;

        // to leave
        cout << "To exit, enter: x" << endl;
        cout << "--------------------------------------------------------" << endl;
        cout << "Your choice" << endl;
        cout << ">>";
        cin >> input;
        cout << "--------------------------------------------------------" << endl;

        switch(tolower(input)) {
            case 'a': add(patients); break;
            case 'r': remove(patients); break;
            case 'u': update(patients); break;
            case 's': search(patients); break;
            case 'p': print(patients); break;
            case 'd': drop(patients); break;
            case 'x': cout << "\n----Bye!\n" << endl; done = true; break;
            default: cout << "Not sure what you mean! Please, try again!" << endl;
        }
    }

    return 0;
}