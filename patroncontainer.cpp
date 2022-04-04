
// PatonContainer class stores all patrons of the library and acts as an
// interface between the patron and the library class. The PatronContainer
// allows quick lookup for patrons.
//
// Assumtpions:
//  -- There can only be 10,000 patrons
//  -- userID will be unique identifier to lookup patrons
// Implementation:
//  -- Patrons are stored in an array
//---------------------------------------------------------------------------

#include "patroncontainer.h"
#include <iostream>

//---------------------------------------------------------------------------
// constructor
PatronContainer::PatronContainer() {}

//---------------------------------------------------------------------------
// destructor
PatronContainer::~PatronContainer() {
    for (int i = 0; i < PATRON_LIMIT; i++) {
        if (patronList[i] != nullptr) {
            delete patronList[i];
            patronList[i] = nullptr;
        }
    }
}

//---------------------------------------------------------------------------
// insert
// data  format: userID First Last
bool PatronContainer::insert(istream &inFile) {
    bool success = false;

    for (;;) {
        int userID;
        inFile >> userID;
        if (inFile.eof()) {
            success = true;
            break;
        }
        inFile.get(); // clear empty space
        // check for valid ID #
        if (userID > 0 && userID < 10000) {
            // create a new patron
            Patron *patron = new Patron();
            success = patron->buildPatron(inFile, userID);
            // check if ID is already in use
            if (patronList[userID] != nullptr) {
                delete patron;
                patron = nullptr;
                cout << "User ID: " << userID << " is already in use" << endl;
            } else {
                // otherwise place it in the hash
                patronList[userID] = patron;
            }
        } else {
            cout << "User ID: " << userID << " is an invalid User ID " << endl;
        }
    }

    return success;
}

//---------------------------------------------------------------------------
// retrieve
bool PatronContainer::retrieve(const int userID, Patron *&toReturn) const {
    bool success = false;
    if (userID > 0 && userID < 10000) {
        if (patronList[userID] != nullptr) {
            toReturn = patronList[userID];
            success = true;
        }
    }
    return success;
}

//---------------------------------------------------------------------------
// display
void PatronContainer::display() const {
    for (int i = 0; i < PATRON_LIMIT; i++) {
        if (patronList[i] != nullptr) {
            string name = patronList[i]->getName();
            int id = patronList[i]->getID();
            cout << id << "   " << name << endl;
        }
    }
}