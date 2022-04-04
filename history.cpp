
// Handles the operation of retrieving the history of a Patron within the
// library system. Returns and outputs their rental history of books from the
// library.
//
// Assumptions:
// -- will only be called on a valid item in the library
//
// Implementation:
//  -- no destructor implementation for dynamic memory in create() method -
//  -- memory deallocation to be handled by Patron class where commands are
//  -- are stored in itemHistory list
//---------------------------------------------------------------------------

#include "history.h"
#include "Library.h"
#include "patroncontainer.h"
#include <iostream>

//---------------------------------------------------------------------------
// constructor
History::History() {
    commType_ = 'H';
    item_ = nullptr;
    patron_ = nullptr;
    libraryPtr_ = nullptr;
}

//---------------------------------------------------------------------------
// Destructor
History::~History() {}

//---------------------------------------------------------------------------
// build Command
// data format: PatronID
bool History::buildCommand(istream &inStream, Library *&library) {
    bool success = false;
    inStream.get(); // clear space

    int ID;
    // read patron ID
    inStream >> ID;
    Patron *patron;

    // check library for patron
    if (library->getPatron(ID, patron)) {
        patron_ = patron;
        success = true;
    }

    else {
        cout << endl
             << "ERROR: User ID \"" << ID << "\" is an invalid patron ID"
             << endl;
    }

    return success;
}

//---------------------------------------------------------------------------
// execute
bool History::execute() {

    patron_->displayPatron();
    patron_->printHistory();
    return true;
}

//---------------------------------------------------------------------------
// display
void History::display() {}

//---------------------------------------------------------------------------
// create
Command *History::create() { return new History(); }