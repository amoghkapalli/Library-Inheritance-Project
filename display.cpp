//---------------------------------------------------------------------------
// display.cpp
//---------------------------------------------------------------------------
// Subclass of command.
// Displays the contents of the library.
//
// Assumptions:
// -- Will display all items stored in the library
// -- will only be called on a valid library object
//
// Implementation:
// -- calls display on library object
//---------------------------------------------------------------------------

#include "display.h"
#include "Library.h"

//---------------------------------------------------------------------------
// constructor
Display::Display() {
    commType_ = 'D';
    item_ = nullptr;
    patron_ = nullptr;
    libraryPtr_ = nullptr;
}

//---------------------------------------------------------------------------
// destructor
Display::~Display() {}

//---------------------------------------------------------------------------
// buildCommand
bool Display::buildCommand(istream &inStream, Library *&library) {
    libraryPtr_ = library;
    return true;
}

//---------------------------------------------------------------------------
// execute
bool Display::execute() {

    if (libraryPtr_ != nullptr) {
        libraryPtr_->displayItems();
        return true;
    }
    return false;
}

//---------------------------------------------------------------------------
// display
void Display::display() { execute(); }

//---------------------------------------------------------------------------
// create
Command *Display::create() { return new Display(); }
