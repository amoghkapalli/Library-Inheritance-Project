// Parent class to child command classes
// Handles the commands from the file. Manages subclasses using input command
// characters. Builds command objects from data file and calls execute.
//
// Assumptions:
// -- Data file format is correct
//
// Implementation:
// -- Has access to Library class through a reference to a pointer
// -- Builds and checks command type and values
//
//---------------------------------------------------------------------------
#ifndef COMMAND_H
#define COMMAND_H

class Library;
class Patron;
#include "item.h"

class Command {
  public:
    //Construct a new Command object. Default constructor.
    Command();

    //Destroy the Return object and free memory.
    virtual ~Command();

    // Handles the execution of object type on stored data members
    virtual bool execute() = 0;

    // Handles the display of command object
    virtual void display() = 0;

    // creates and returns a new command object pointer
    virtual Command *create() = 0;

    // builds a command from data file
    virtual bool buildCommand(istream &inFile, Library *&library) = 0;

    // gets and returns the Item object associated with command
    Item *getItem();

    // gets and returns the char code for command type
    char getCommandType();

  protected:
    // pointer to patron associated with command
    Patron *patron_;

    // pointer to item assocaited with command
    Item *item_;

    // command type code
    char commType_;

    //// pointer to library associated with command
    Library *libraryPtr_;
};

#endif