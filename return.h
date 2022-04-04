//---------------------------------------------------------------------------
// return.h
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

#ifndef RETURN_H
#define RETURN_H

#include "command.h"
#include <iostream>

class Return : public Command {
  public:
    // Construct a new Return object. Default constructor.
    Return();

    // Destroy the Return object and free memory.
    ~Return();

    // builds a command from data file
    virtual bool buildCommand(istream &inFile, Library *&library);

    // Handles the execution of the return of the given book
    // into the library system.
    virtual bool execute();

    // displays "return" to cout and calls historyDisplay on Item
    virtual void display();

    // returns new return object
    virtual Command *create();
};

#endif