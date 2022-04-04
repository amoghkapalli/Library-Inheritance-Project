// Subclass of command.
// Handles checking out an item, will attempt to decrement avaialble copies
// of the book by one.
//
// Assumptions:
// -- will only be called on a valid item in the library
// -- patronPtr will point to a valid patron
//
// Implementation:
//  -- Execute calls changeAvailable method on Item
//  -- Item to do error handling with available copies
//  -- no destructor implementation for dynamic memory in create() method -
//  -- memory deallocation to be handled by Patron class where commands are
//  -- are stored in itemHistory list
//---------------------------------------------------------------------------

#ifndef CHECKOUT_H
#define CHECKOUT_H

#include "command.h"
#include "itemfactory.h"
#include "patron.h"

class Checkout : public Command {
  public:
    // constructor
    Checkout();

    // destructor
    virtual ~Checkout();

    //Builds a command from data file and returns true if successful
    virtual bool buildCommand(istream &inStream, Library *&library);

    //displays "CheckOut" to cout and calls historyDisplay on Item
    virtual void display();

    //calls changeAvailable method on Item to decrement by 1
    virtual bool execute();

    //returns new Checkout object, dynamic memory
    virtual Command *create();
};
#endif