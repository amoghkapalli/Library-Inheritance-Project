//---------------------------------------------------------------------------
// itemfactory.h
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

#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

#include "Book.h"
#include <iostream>

class ItemFactory {
  public:
    // constructor
    ItemFactory();

    // destructor
    ~ItemFactory();

    // Create a Book object. Determines type of book based on incoming
    Item *createItem(char type);

  private:
    static const int TYPES = 26;

    // array containing indexes for all possible bookTypes in future
    Item *types[TYPES];

    // hash function
    int hash(char ch);
};

#endif