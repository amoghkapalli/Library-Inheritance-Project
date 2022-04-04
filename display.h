//---------------------------------------------------------------------------
// display.h
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

#ifndef DISPLAY_H
#define DISPLAY_H

#include "command.h"
#include <iostream>

class Display : public Command {
  public:
    // constructor
    Display();

    // destructor
    ~Display();

    // builds a command from data file returns true if successful
    virtual bool buildCommand(istream &inFile, Library *&library);

    // calls display on the library object to display all items
    virtual bool execute();

    // creates a new display command object
    virtual Command *create();

    //calls display on the library object to display all items
    virtual void display();
};

#endif
