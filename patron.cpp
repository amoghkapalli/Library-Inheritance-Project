//---------------------------------------------------------------------------
// patron.cpp
//---------------------------------------------------------------------------
// A Patron class to store information on Patrons of the library
// Patron name, ID, book rental history and currently checked out books
// are all stored.
// Patron Objects are initiated in the Patron Factory.
//
// Assumptions:
//  -- rentalHistory has no limit
//  -- currentCheckOuts has no limit
//  -- userID will be unique identifier
// Implementation:
//  -- rentalHistory Book objects are stored in a STL list
//  -- currentCheckOuts Book objects are stored in a STL list
//  -- Once a book is added to currentCheckOuts it is added to rentalHistory
//---------------------------------------------------------------------------

#include "patron.h"
#include <sstream>
#include <vector>

//---------------------------------------------------------------------------
// Constructor
Patron::Patron() {

    // initialize member fields
    nameLastFirst_ = "";
    userID_ = 0;
}

//---------------------------------------------------------------------------
// destructor
Patron::~Patron() {
    for (list<Command *>::iterator it2 = itemHistory.begin();
         it2 != itemHistory.end(); it2++) {
        delete (*it2);
    }
}

//---------------------------------------------------------------------------
// buildPatron
bool Patron::buildPatron(istream &inFile, int userID) {
    string nameLastFirst = "";
    userID_ = userID;

    // take name from inFile
    getline(inFile, nameLastFirst);
    nameLastFirst_ = nameLastFirst;
    return true;
}

//---------------------------------------------------------------------------
// getFirst
string Patron::getName() const { return nameLastFirst_; }

//---------------------------------------------------------------------------
// getID
int Patron::getID() const { return userID_; }

//---------------------------------------------------------------------------
// printHistory
void Patron::printHistory() {

    // if the list is not empty
    if (!itemHistory.empty()) {
        // long iterator loop

        for (list<Command *>::iterator it2 = itemHistory.begin();
             it2 != itemHistory.end(); it2++) {
            (*it2)->display();
        }
    }
}

//---------------------------------------------------------------------------
// addToHistory
bool Patron::addToHistory(Command *comm) {

    // push history object to back of list (newest)
    itemHistory.push_back(comm);

    return true;
}
//---------------------------------------------------------------------------
// displayPatron()
void Patron::displayPatron() {
    char splitChar = ' ';
    string firstName;
    string lastName;

    vector<string> result;
    stringstream ss(nameLastFirst_);
    string item;

    while (getline(ss, item, splitChar)) {
        result.push_back(item);
    }
    cout << endl
         << getID() << " " << result.at(0) << ", " << result.at(1) << ":"
         << endl;
}

//---------------------------------------------------------------------------
// searchCheckouts
bool Patron::searchCheckouts(const Item *target) {
    int checkCount = 0;
    int returnCount = 0;
    // for each command object stored in patron
    for (list<Command *>::iterator it = itemHistory.begin();
         it != itemHistory.end(); it++) {

        if (*target == *(*it)->getItem()) {
            if ((*it)->getCommandType() == 'C') {
                checkCount++;
            }
            if ((*it)->getCommandType() == 'R') {
                returnCount++;
            }
        } else {
            continue;
        }

        if (checkCount - returnCount > 0) {
            return true;
        }
        return false;
    }
    return false;
}