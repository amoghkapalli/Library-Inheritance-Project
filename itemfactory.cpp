//---------------------------------------------------------------------------
// itemfactory.cpp
//---------------------------------------------------------------------------
// A Item factory class. Handles the creation of Item objects based on the
// Item code being taken from input. Works as an intermidiate class to process
// any type of Item creation in one class. Able to create periodicals, fiction,
// and children's books based on incoming Item code.
//
// Assumptions:
//  -- valid character corresponding to book type from input
//  -- book type character will correspond to present Item type
//---------------------------------------------------------------------------

#include "itemfactory.h"
#include "childrenbook.h"
#include "fictionbook.h"
#include "periodicalbook.h"
#include <ctype.h>

//---------------------------------------------------------------------------
// constructor
ItemFactory::ItemFactory() {

    for (int i = 0; i < TYPES; i++) {
        types[i] = nullptr;
    }

    types[2] = new ChildrenBook;
    types[5] = new FictionBook;
    types[15] = new PeriodicalBook;
}

//---------------------------------------------------------------------------
// destructor
ItemFactory::~ItemFactory() {
    for (int i = 0; i < TYPES; i++) {
        delete types[i];
        types[i] = nullptr;
    }
}

//---------------------------------------------------------------------------
// createBook
Item *ItemFactory::createItem(char type) {
    Item *toReturn = nullptr;
    int subscript = hash(type);

    if (types[subscript] != nullptr) {
        toReturn = types[subscript]->create();
    }

    return toReturn;
}

//---------------------------------------------------------------------------
// hash
int ItemFactory::hash(char type) {
    // change to uppercase if it's not
    type = toupper(type);
    int subscript = type - 'A';
    return subscript;
}