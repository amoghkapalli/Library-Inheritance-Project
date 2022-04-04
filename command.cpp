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

#include "command.h"
#include "patron.h"

//---------------------------------------------------------------------------
// constructor
Command::Command() {
    commType_ = ' ';
    patron_ = 0;
    item_ = nullptr;
    patron_ = nullptr;
    libraryPtr_ = nullptr;
}

//---------------------------------------------------------------------------
// destructor
Command::~Command() { item_ = nullptr; }

//---------------------------------------------------------------------------
// getItem
Item *Command::getItem() { return item_; }

//---------------------------------------------------------------------------
// getCommandType
char Command::getCommandType() { return commType_; }
