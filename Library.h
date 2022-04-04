//---------------------------------------------------------------------------
// library.h
//---------------------------------------------------------------------------
// Library class acts as interface between data files and storage / functions
//
// Assumptions:
// -- correctly formatted input from file
// -- each book item is uniquely identified by its srting criteria
// -- each command is uniquely and correctly identified by command char
// Implementation:
// -- holds a book factory, command factory, patron container, and bookcase
// -- Library reads input from data files
//---------------------------------------------------------------------------

#ifndef LIBRARY_H
#define LIBRARY_H

#include "commandmanager.h"
#include "patroncontainer.h"
#include "shelf.h"
#include <iostream>

using namespace std;

class Library {

  public:
    // default constructor
    Library();

    // default destructor
    ~Library();

    // adds patron to patron container
    bool buildPatrons(istream &);

    // interface between data file and command execution
    bool performCommands(istream &);

    // interface between data file and book addition
    bool buildLibrary(istream &);

    // displays books by category, sorted within the category
    void displayItems() const;

    // displays all patrons in the library by order of ID
    void displayPatrons() const;

    // Finds and returns a patron within the library system. Assigns
    // desired patron to a pointer to be used by calling function.
    bool getPatron(int userID,Patron *&);

    // retrieves an item from the library
    bool getItem(Item &target, Item *&toReturn);

  private:
    // contents of the library
    Shelf shelf;

    // holds patrons of the library
    PatronContainer patContainer;

    // interface with command objects
    CommandManager commManager;
};

#endif
