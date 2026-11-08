#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

//struture for holding details and function to intilazie 
struct Contact {
    string name;
    string phonenumber;
    string email;

    Contact(string n, string p, string e) {
        name = n;
        phonenumber = p;
        email = e;
    }
};

//we use hash maps for speeds
class ContactDirectory {
private:
    // hash map to all hold name and thier structure poiners 
    unordered_map<string, Contact*> map;

public:
    // check for duplicates if found update not found insert new ones
    void insertContact(string name, string phone, string email) {
        if (map.find(name) != map.end()) {
            // Update existing contact to avoid duplicates
            map[name]->phonenumber = phone;
            map[name]->email = email;
            cout << "existing contact details updated for: " << name << "\n";
            return;
        }
        Contact* newContact = new Contact(name, phone, email);
        map[name] = newContact;
        cout << "saved new contact: " << name << "\n";
    }

    //search contact we use hash map find function
    void searchContact(string name) {
        if (map.find(name) == map.end()) {
            cout << "no record exists for name: " << name << "\n";
            return;
        }
        Contact* match = map[name];
        cout << "\n contact found\n";
        cout << "name: " << match->name << "\n";
        cout << "phone: " << match->phonenumber << "\n";
        cout << "email: " << match->email << "\n";
    }

    // Delete a contact record and free memory allocations in O(1)
    void deleteContact(string name) {
        if (map.find(name) == map.end()) {
            cout << "cannot delete. record not found for: " << name << "\n";
            return;
        }
        Contact* target = map[name];
        map.erase(name); // delete contact 
        delete target;        // Free dymaic memory allocation from structures
        cout << "successfully cleared records for: " << name << "\n";
    }

    // we use this to prevent memory leaks 
    ~ContactDirectory() {
        for (auto& pair : map) {
            delete pair.second;
        }
        map.clear();
    }
};

int main() {
    cout << " Activating O(1) Direct-Lookup Contact Engine \n";
    ContactDirectory myPhonebook;
    string inputChoice;
    while (true) {
        cout << "\n======= MENU =======\n";
        cout << "1. add / update contact\n";
        cout << "2. search contact\n";
        cout << "3. delete contact\n";
        cout << "4. exit\n";
        cout << "enter your choice (1-4): ";
        
    //safety buffer to handle inputs of inapproriate 
        getline(cin, inputChoice);

        if (inputChoice.empty()) {
            continue;
        }

        // user should enter only one charcter sine=ce 1,2,3,4 are single charcaters 
        if (inputChoice.length() > 1) {
            cout << "invalid choice please select a single valid digit (1, 2, 3, or 4).\n";
            continue;
        }

        // Extract the single character to feed into the switch statement
        char choice = inputChoice[0];

        if (choice == '4') {
            cout << "\nShutting down engine!\n";
            break;
        }

        string name, phone, email;
            //switch case to determine which function to be choosed 
            switch (choice) {
            case '1':
                cout << "enter name: ";
                getline(cin, name);
                cout << "enter phone number: ";
                getline(cin, phone);
                cout << "enter email: ";
                getline(cin, email);
                
                myPhonebook.insertContact(name, phone, email);
                break;

            case '2':
                cout << "enter name to search: ";
                getline(cin, name);
                myPhonebook.searchContact(name);
                break;

            case '3':
                cout << "enter name to delete: ";
                getline(cin, name);
                myPhonebook.deleteContact(name);
                break;

            default:
                cout << "invalid choice please select a valid option (1, 2, 3, or 4).\n";
                break;
        }
    }

    return 0;
}
