// Subclass of Item
// A book object. Handles the creation and storage of a
// book, containing title, author, number of copies "owned" by the library,
// and copies of this book currently checked in. Parent class of fictionbook,
// periodicalbook, and childrenbook.
//
// Assumptions:
// -- book copies will be initialized by subclass
// -- all books will have a title
//
// Implementation:
// -- available and total copies initialized to 0 for generic book object
// -- subclasses will initialize total and available copies
//
//---------------------------------------------------------------------------

#ifndef BOOK_H
#define BOOK_H

#include "item.h"
#include <iostream>

using namespace std;

class Book : public Item {
  public:
    // default constructor
    Book();

    //Destroy the Book object
    //Object will be deleted and memory freed.
    virtual ~Book();

    //Get the title of the current book object. Return string containing 
    // the title of the current book
    string getTitle() const;

    //Sets the title of the given book.
    void setTitle(string incomingTitle);

  protected:
    // title of book
    string title_;
    // copies of book checked into library
    int availableCopies_;
    // total amount of copies the library owns
    int totalCopies_;
};
#endif
