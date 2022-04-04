//---------------------------------------------------------------------------
// patron.h
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

#ifndef PATRON_H
#define PATRON_H

#include "command.h"
#include "item.h"
#include <list>
#include <string>

using namespace std;

class Patron {

  public:
    // default constructor
    Patron();

    // default constructor
    ~Patron();

    // sets the userID, firstName and lastName of patron
    bool buildPatron(istream &infile, int userID);

    // retrieves and returns firstName
    string getName() const;

    // retrieves and returns userID
    int getID() const;

    // prints the itemHistory to console
    void printHistory();

    // adds a Item object to patron itemHistory
    bool addToHistory(Command *);

    // searches checkout history to see if an item is viable for return
    bool searchCheckouts(const Item *target);

    // displays the patron information, ID, Last, First
    void displayPatron();

  private:
    // patron name
    string nameLastFirst_;

    // patron unique ID
    int userID_;

    // list to store Patron item rental history
    list<Command *> itemHistory;
};
#endif
