//---------------------------------------------------------------------------
// item.h
//---------------------------------------------------------------------------
// An abstract class.
// An item class for the library to store different types of items.
// Current item types are book, but can be other types such as DVD, magazine,
// etc.
//
// Assumptions:
// -- All items will have a unique char identifier
// -- all items will have a format
//
// Implementation:
// -- bool array keeps track of known formats
//
//---------------------------------------------------------------------------

#include "item.h"

using namespace std;
//---------------------------------------------------------------------------
// constructor
Item::Item() {
    itemType_ = ' ';

    // initialize known formats
    validFormat[7] = true;
}

//---------------------------------------------------------------------------
// destrucor
Item::~Item() {}

//---------------------------------------------------------------------------
// getType
char Item::getType() const { return itemType_; }

//---------------------------------------------------------------------------
// setFormat
bool Item::setFormat(char format) {
    bool success = false;
    if (format > 'A' && format < 'z') {
        int checkHash = toupper(format) - 'A';
        if (validFormat[checkHash]) {
            format_ = format;
            success = true;
        }
    }
    return success;
}