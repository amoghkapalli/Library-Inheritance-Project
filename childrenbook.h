// Subclass of Book
// A children book object. Handles the creation and storage of a children's
// book, containing title, author, number of copies "owned" by the library,
// and copies of this book currently checked in.
//
// Assumptions:
//  -- initial character in input dictates 'C' for children
//  -- Comparison operators will only be used with other ChildrenBook
//  -- istream data will always be in the correct format
//
// Implementation:
//  -- data format from command data file handled in fill() method
//  -- data format from book data file handled in buildItem()
//
//---------------------------------------------------------------------------

#include "Book.h"
#include <iostream>

class ChildrenBook : public Book {

  public:
    // Constructs a new Children object. Creates new Children book
    ChildrenBook();

    // destructor
    ~ChildrenBook();

    // Builds the data for a blank book object. Handles the "filling out" 
    // of the book being created.
    bool buildItem(istream &infile);

    // Creates a dynamically allocated children book object, then
    // returns a copy of that object for the factory to function properly.
    virtual Item *create();

    // fills data for a childrenBook item from Command Data file format
    virtual void fill(istream &);

    // displays the information of the current book in sort order
    virtual void display() const;

    // handles the ouput of an invalid Childrenbook's - prints to console
    void errorDisplay() const;

    // formats the output when ChildrenBook Item is displayed from patron
    void historyDisplay() const;

    //displays the categories and format of data for ChildrenBook list
    void displayBookHeader() const;

    //gets and returns the available copies of this object
    int getCopiesAvailable() const;

    //sets the book author
    void setAuthor(string author);

    // gets and returns the book author
    string getAuthor() const;

    //sets the year data member
    bool setYear(int year);

    //returns the book published year
    int getYear() const;

    //increment or decrement availableCopies_
    virtual bool changeAvailable(int num);

    //---------------------------------------------------------------------------
    // Overloaded Operators
    //---------------------------------------------------------------------------

    /** operator<
     * Less than operator. Compares LHS and RHS for lesser value.
     */
    bool operator<(const Item &rhsItem) const;

    /** operator>
     * Greater than operator. compares LHS and RHS for greater value.
     */
    bool operator>(const Item &rhsItem) const;

    /** operator==
     * Equals operator. Determines if two Book objects are equal.
     */
    bool operator==(const Item &rhsItem) const;

    /** operator !=
     * Does not equals operator. Determines if two books are not equal.
     */
    bool operator!=(const Item &rhsItem) const;

  private:
    // author of the book, last then first name
    string author_;

    // publishing year
    int year_;

    // default value for available and total copies
    static const int COPIES = 5;
};

