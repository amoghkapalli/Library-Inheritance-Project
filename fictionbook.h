//---------------------------------------------------------------------------
// fictionbook.h
//---------------------------------------------------------------------------
// A fiction book object. Handles the creation and storage of a fiction book,
// containing title, author, number of copies "owned" by the library, and
// copies of this book currently checked in.
//
// Ficiton sorted by author, then title
//
// Assumptions:
//  -- initial character in input dictates 'f' for fiction
//---------------------------------------------------------------------------

#ifndef FICTIONBOOK_H
#define FICTIONBOOK_H

#include "Book.h"
#include <iostream>

class FictionBook : public Book {

  public:
    // constructor
    FictionBook();

    // destructor
    ~FictionBook();

    // creates book object reading from data file
    bool buildItem(istream &in);

    // Creates a fiction book object, then returns a copy of that object
    // for the factory to function properly.
    virtual Item *create();

    // fills data for a fictionBook item from Command Data file format
    virtual void fill(istream &);

    // displays the categories and format of data for fictionBook list
    virtual void displayBookHeader() const;

    // displays the information of the current book in sort order
    virtual void display() const;

    // handles the ouput of an invalid FictionBook's - prints to console
    virtual void errorDisplay() const;

    // formats the output when FictionBook Item is displayed from patron
    virtual void historyDisplay() const;

    // gets and returns the available copies of this object
    virtual int getCopiesAvailable() const;

    // sets the author data member of the book
    void setAuthor(string author);

    // sets the year data member
    bool setYear(int year);

    // gets and returns the book author
    string getAuthor() const;

    // returns the book published year
    int getYear() const;

    // increment or decrement availableCopies_
    virtual bool changeAvailable(int num);

    //---------------------------------------------------------------------------
    // Overloaded Operators
    //---------------------------------------------------------------------------

    /**
     * Less than operator. Compares LHS and RHS for lesser value.
     */
    bool operator<(const Item &rhsItem) const;

    /**
     * Greater than operator. compares LHS and RHS for greater value.
     */
    bool operator>(const Item &rhsItem) const;

    /**
     * Equals operator. Determines if two Book objects are equal.
     */
    bool operator==(const Item &rhsItem) const;

    /**
     * Does not equals operator. Determines if two books are not equal.
     */

    bool operator!=(const Item &rhsItem) const;

  private:
    // author of the book, last then first name
    string author_;

    // publishing year
    int year_;

    // default copies available
    static const int COPIES = 5;
};
#endif
