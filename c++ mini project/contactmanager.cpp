#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Contact {
public:
    string name;
    string phone;

    Contact(const string& n, const string& p) : name(n), phone(p) {}
};

class ContactManager {
private:
    vector<Contact> contacts;
    string fileName;

public:
    ContactManager(const string& file) : fileName(file) {
        loadContacts();
    }

    void addContact(const string& name, const string& phone) {
        contacts.emplace_back(name, phone);
        saveContacts();
        cout << "Contact added successfully.\n";
    }

    void displayContacts() {
        if (contacts.empty()) {
            cout << "No contacts to display.\n";
        } else {
            cout << "Contacts:\n";
            for (const auto& contact : contacts) {
                cout << "Name: " << contact.name << "\tPhone: " << contact.phone << "\n";
            }
        }
    }

    void editContact() {
        string searchName;
        cout << "Enter the name of the contact to edit: ";
        getline(std::cin, searchName);

        auto it = find_if(contacts.begin(), contacts.end(), [searchName](const Contact& c) {
            return c.name == searchName;
        });

        if (it != contacts.end()) {
            string newName, newPhone;
            cout << "Enter new details for the contact:\n";
            cout << "New Name: ";
            getline(std::cin, newName);
            cout << "New Phone: ";
            getline(std::cin, newPhone);

            it->name = newName;
            it->phone = newPhone;

            saveContacts();
            cout << "Contact edited successfully.\n";
        } else {
            cout << "Contact not found.\n";
        }
    }

private:
    void loadContacts() {
        ifstream inputFile(fileName);
        if (!inputFile.is_open()) {
            cout << "No existing contacts file found.\n";
            return;
        }

        while (!inputFile.eof()) {
            string name, phone;
            inputFile >> name >> phone;
            if (!name.empty() && !phone.empty()) {
                contacts.emplace_back(name, phone);
            }
        }

        inputFile.close();
    }

    void saveContacts() {
        ofstream outputFile(fileName);
        for (const auto& contact : contacts) {
            outputFile << contact.name << " " << contact.phone << "\n";
        }
        outputFile.close();
    }
};

int main() {
    ContactManager contactManager("contacts.txt");

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Add Contact\n";
        cout << "2. Display Contacts\n";
        cout << "3. Edit Contact\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); 

        switch (choice) {
            case 1: {
                string name, phone;
                cout << "Enter contact details:\n";
                cout << "Name: ";
                getline(cin, name);
                cout << "Phone: ";
                getline(cin, phone);
                contactManager.addContact(name, phone);
                break;
            }
            case 2:
                contactManager.displayContacts();
                break;
            case 3:
                contactManager.editContact();
                break;
            case 4:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}