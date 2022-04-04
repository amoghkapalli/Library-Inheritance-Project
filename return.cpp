//---------------------------------------------------------------------------
// return.cpp
//---------------------------------------------------------------------------
// Handles the operation of returning a book into the library system. Both by
// unassigning the book from the patron who checked it out, and modifying the
// values for currently checked in copies of the book.
//
// Assumptions:
// -- will only be called on a valid item in the library
// -- patronPtr will point to a valid patron
//
// Implementation:
//  -- no destructor implementation for dynamic memory in create() method -
//  -- memory deallocation to be handled by Patron class where commands are
//  -- are stored in itemHistory list
//
//---------------------------------------------------------------------------

#include "return.h"
#include "Library.h"

//---------------------------------------------------------------------------
// constructor
Return::Return() { commType_ = 'R'; }

//---------------------------------------------------------------------------
// destructor
Return::~Return() {}

//---------------------------------------------------------------------------
// buildCommand
// data format: ID ItemType ItemFormat Item specific info
bool Return::buildCommand(istream &inStream, Library *&library) {

    // read patron ID
    int ID;
    inStream.get(); // clear empty space
    inStream >> ID;
    inStream.get(); // clear empty space

    // first verify the patron
    Patron *patron = nullptr;
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

    Item *target;
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
        target = nullptr;
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
    } else {
        // display error if item not found
        target->errorDisplay();
        cout << endl;
        delete target;
        target = nullptr;
        return false;
    }

    return true;
}

//---------------------------------------------------------------------------
// execture
bool Return::execute() {
    bool success = false;

    // search patron for previous checkout
    if (!patron_->searchCheckouts(item_)) {
        cout << endl
             << "ERROR: Patron " << patron_->getID()
             << " is attempting to return a book they do not have checked "
                "out."
             << endl;
    } else {
        // increase available copies by 1
        if (item_->changeAvailable(1)) {
            // add to patron history
            patron_->addToHistory(this);
            success = true;
        }
    }
    return success;
}

//---------------------------------------------------------------------------
// display
void Return::display() {
    cout << "  Return    ";
    item_->historyDisplay();
}

//---------------------------------------------------------------------------
// return
Command *Return::create() { return new Return(); }