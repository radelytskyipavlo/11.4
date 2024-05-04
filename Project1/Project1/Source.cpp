#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

struct Friend {
    char firstName[50];
    char lastName[50];
    char phoneNumber[15];
    int birthday[3];
};

void createFriendList(const string& filename);
void displayFriendList(const string& filename);
void searchFriendByLastName(const string& filename);

int main() {
    int choice;
    string filename;

    do {
        cout << "--------------------------\n";
        cout << "Menu\n";
        cout << "[1] - Enter and save information\n";
        cout << "[2] - Load and display information\n";
        cout << "[3] - Search by friend's last name\n";
        cout << "[0] - Exit\n";
        cout << "--------------------------\n";
        cout << "Select: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Entering and saving:\n";
            cout << "Enter a file name: ";
            cin >> filename;
            createFriendList(filename);
            break;

        case 2:
            cout << "Information output:\n";
            cout << "Enter a file name: ";
            cin >> filename;
            displayFriendList(filename);
            break;

        case 3:
            cout << "Search by friend's last name:\n";
            cout << "Enter a file name: ";
            cin >> filename;
            searchFriendByLastName(filename);
            break;

        case 0:
            break;

        default:
            cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 0);

    return 0;
}

void createFriendList(const string& filename) {
    ofstream file(filename, ios::binary | ios::app);
    if (!file.is_open()) {
        cerr << "Error opening file '" << filename << "'" << endl;
        return;
    }

    Friend friendEntry;
    char choice;

    do {
        cout << "Enter friend's first name: ";
        cin >> friendEntry.firstName;
        cout << "Enter friend's last name: ";
        cin >> friendEntry.lastName;
        cout << "Enter friend's phone number: ";
        cin >> friendEntry.phoneNumber;
        cout << "Enter friend's birthday (DD MM YYYY): ";
        for (int i = 0; i < 3; ++i)
            cin >> friendEntry.birthday[i];

        file.write(reinterpret_cast<char*>(&friendEntry), sizeof(Friend));

        cout << "Continue? [Y/n]: ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    file.close();
}

void displayFriendList(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "Error opening file '" << filename << "'" << endl;
        return;
    }

    Friend friendEntry;

    cout << "==============================\n";
    cout << "| Name             | Phone Number | Birthday |\n";
    cout << "------------------------------\n";

    while (file.read(reinterpret_cast<char*>(&friendEntry), sizeof(Friend))) {
        cout << "| " << setw(17) << left << friendEntry.firstName << " " << setw(17) << left << friendEntry.lastName << " | "
            << setw(12) << left << friendEntry.phoneNumber << " | "
            << setw(2) << right << setfill(' ') << friendEntry.birthday[0] << "-" << setw(2) << right << setfill(' ')
            << friendEntry.birthday[1] << "-" << setw(4) << right << setfill(' ') << friendEntry.birthday[2] << " |\n";
    }

    cout << "------------------------------\n";

    file.close();
}

void searchFriendByLastName(const string& filename) {
    char searchLastName[50];
    cout << "Enter friend's last name to search: ";
    cin >> searchLastName;

    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "Error opening file '" << filename << "'" << endl;
        return;
    }

    Friend friendEntry;
    bool found = false;

    while (file.read(reinterpret_cast<char*>(&friendEntry), sizeof(Friend))) {
        if (strcmp(friendEntry.lastName, searchLastName) == 0) {
            found = true;
            cout << "Friend found:\n";
            cout << "Name: " << friendEntry.firstName << " " << friendEntry.lastName << endl;
            cout << "Phone Number: " << friendEntry.phoneNumber << endl;
            cout << "Birthday: " << setw(2) << setfill('0') << friendEntry.birthday[0] << "-"
                << setw(2) << setfill('0') << friendEntry.birthday[1] << "-"
                << setw(4) << setfill('0') << friendEntry.birthday[2] << endl;
            break;
        }
    }

    if (!found) {
        cout << "Friend not found." << endl;
    }

    file.close();
}
