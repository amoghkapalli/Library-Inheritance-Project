//---------------------------------------------------------------------------
// history.cpp
//---------------------------------------------------------------------------
// Handles the operation of retrieving the history of a Patron within the
// library system. Returns and outputs their rental history of books from the
// library.
//
// Assumptions:
// -- will only be called on a valid item in the library
// -- patronPtr will point to a valid patron
//
// Implementation:
//  -- no destructor implementation for dynamic memory in create() method -
//  -- memory deallocation to be handled by Patron class where commands are
//  -- are stored in itemHistory list
//---------------------------------------------------------------------------

#ifndef HISTORY_H
#define HISTORY_H

#include "command.h"
#include <iostream>

class History : public Command {
  public:
    // constructor
    History();

    // destructor
    ~History();

    // builds a command from data file
    virtual bool buildCommand(istream &inFile, Library *&library);

    // Handles the execution of the history retrieval for a patron object.
    // Outputs the check-out history of a given patron in a organized
    // fashion.
    virtual bool execute();

    // display
    virtual void display();

    // returns new History object, dynamic memory
    virtual Command *create();
};

#endif