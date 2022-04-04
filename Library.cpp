//---------------------------------------------------------------------------
// library.h
//---------------------------------------------------------------------------
// Library class acts as interface between data files and storage / functions
//
// Assumptions:
// -- correctly formatted input from file
// -- each book item is uniquely identified by its srting criteria
// -- each command is uniquely and correctly identified by command char
// Implementation:
// -- holds a book factory, command factory, patron container, and bookcase
// -- Library reads input from data files
//---------------------------------------------------------------------------

#include "Library.h"

//---------------------------------------------------------------------------
// constructor
Library::Library() {}

//---------------------------------------------------------------------------
// destructor
Library::~Library() {}

//---------------------------------------------------------------------------
// buildPatron
// data format --> ID# Last First
bool Library::buildPatrons(istream &inFile) {
    return patContainer.insert(inFile);
}

//---------------------------------------------------------------------------
// runCommands
bool Library::performCommands(istream &inFile) {
    return commManager.performCommands(inFile, this);
}

//---------------------------------------------------------------------------
// buildLibrary
bool Library::buildLibrary(istream &in) { return shelf.buildLibrary(in); }

//---------------------------------------------------------------------------
// displayItems
void Library::displayItems() const { shelf.display(); }

//---------------------------------------------------------------------------
// displayPatrons
void Library::displayPatrons() const { patContainer.display(); }

//---------------------------------------------------------------------------
// getPatron
bool Library::getPatron(int userID, Patron *&toReturn) {
    bool success = false;

    // valid ID retrieve patron from PatronContainer
    if (userID > 0 && userID < 10000) {
        Patron *patron = nullptr;
        patContainer.retrieve(userID, patron);
        if (patron != nullptr) {
            toReturn = patron;
            success = true;
        }
    }
    return success;
}

//---------------------------------------------------------------------------
// getItem
bool Library::getItem(Item &target, Item *&toReturn) {

    bool success = false;

    // retrieve item from shelf
    Item *retrieved;

    // if successfully retrieved item
    if (shelf.retrieve(target, retrieved)) {

        // set referenced to item to found item
        toReturn = retrieved;
        success = true;
    }

    return success;
}