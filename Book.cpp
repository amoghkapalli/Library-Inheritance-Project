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

#include "Book.h"
#include <iostream>
using namespace std;

//---------------------------------------------------------------------------
// constructor
Book::Book() {
    title_ = "";
    format_ = 'H';
    availableCopies_ = 0;
    totalCopies_ = 0;
}
//---------------------------------------------------------------------------
// destructor
Book::~Book() {}

//---------------------------------------------------------------------------
// setTitle
void Book::setTitle(string incomingTitle) { title_ = incomingTitle; }

//---------------------------------------------------------------------------
// getTitle
string Book::getTitle() const { return title_; }
