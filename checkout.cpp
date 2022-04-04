// Subclass of command.
// Handles checking out a book, will attempt to decrement avaialble copies
// of the book by one.
//
// Assumptions:
// -- will only be called on a valid item in the library
//
// Implementation:
//  -- Execute calls changeAvailable method on Item
//  -- Item to do error handling with available copies
//  -- no destructor implementation for dynamic memory in create() method -
//  -- memory deallocation to be handled by Patron class where commands are
//  -- are stored in itemHistory list
//---------------------------------------------------------------------------

#include "checkout.h"
#include "Library.h"
#include <iostream>

//---------------------------------------------------------------------------
// constructor
Checkout::Checkout() {
    commType_ = 'C';
    item_ = nullptr;
    patron_ = nullptr;
    libraryPtr_ = nullptr;
}

//---------------------------------------------------------------------------
// destructor
Checkout::~Checkout() {}
//---------------------------------------------------------------------------
// buildCommand
// data format: PatronID itemType itemFormat Iteminfo
bool Checkout::buildCommand(istream &inStream, Library *&library) {

    // read patron ID
    int ID;
    inStream.get(); // clear empty space
    inStream >> ID;
    inStream.get(); // clear empty space

    // first verify the patron
    Patron *patron;
    if (!library->getPatron(ID, patron)) {
        cout << endl
             << "ERROR: User ID \"" << ID << "\" is an invalid patron ID"
             << endl;
        return false;
    } else {
        patron_ = patron;
    }

    // set data member
    patron_ = patron;

    Item *target = nullptr;
    ItemFactory iFactory;
    char itemType;

    // read itemType
    inStream >> itemType;
    inStream.get(); // clear empty space

    // check item type
    target = iFactory.createItem(itemType);
    if (target == nullptr) {
        cout << endl
             << "ERROR: Item Type \"" << itemType
             << "\" is an invalid Item Type" << endl;
        delete target;
        return false;
    }

    // read item format
    char format;
    inStream >> format;
    inStream.get(); // clear empty space

    // check format
    if (!target->setFormat(format)) {
        cout << endl
             << "ERROR: Item Format: \"" << format << "\" is an invalid format"
             << endl;
        delete target;
        target = nullptr;
        return false;
    }

    // set item specific information
    target->fill(inStream);

    // search library for the target item
    Item *found;
    if (library->getItem(*target, found)) {
        item_ = found;
        delete target;
        target = nullptr;
    }

    // display error message and deallocate memory if not found
    else {
        target->errorDisplay();
        cout << endl;
        delete target;
        target = nullptr;
        return false;
    }

    return true;
}

//---------------------------------------------------------------------------
// display
void Checkout::display() {
    cout << "  CheckOut  ";
    item_->historyDisplay();
}

//---------------------------------------------------------------------------
// execute
// item_ and patron_ data fields are set by command.buildCommand
bool Checkout::execute() {
    bool success = false;

    // decrement available copies
    if (item_->changeAvailable(-1)) {

        // add this checkout to patron history
        patron_->addToHistory(this);
        success = true;
    }
    // if false then no copies available
    else {
        cout << endl
             << "ERROR: Patron " << patron_->getID()
             << " checkout failed due to no copies available of";
        item_->errorDisplay();
        cout << endl;
    }
    return success;
}

//---------------------------------------------------------------------------
// create
Command *Checkout::create() { return new Checkout(); }