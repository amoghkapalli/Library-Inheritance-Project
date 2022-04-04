//---------------------------------------------------------------------------
// item.h
//---------------------------------------------------------------------------
// An abstract class.
// An item class for the library to store different types of items.
// Current item types are book, but can be other types such as DVD, magazine,
// etc.
//
// Assumptions:
// -- All items will have a unique char identifier
// -- all items will have a format
//
// Implementation:
// -- bool array keeps track of known formats
//
//---------------------------------------------------------------------------

#ifndef ITEM_H
#define ITEM_H
#include <iostream>
using namespace std;

class Item {
  public:
    // constructor
    Item();

    // destuctor
    virtual ~Item();

    // creates item object reading from data file
    virtual bool buildItem(istream &in) = 0;

    // prints the contents of the item to console, pure virtual function
    virtual void display() const = 0;

    // handles the ouput of an invalid Item - prints to console
    virtual void errorDisplay() const = 0;

    // formats the output when Item is displayed from patron
    virtual void historyDisplay() const = 0;

    // displays the categories and format of data for Item list
    virtual void displayBookHeader() const = 0;

    // gets and returns the available copies of this object
    virtual int getCopiesAvailable() const = 0;

    // creates a new item object, pure virutal funciton
    virtual Item *create() = 0;

    // fills data for an item from Command Data file format
    virtual void fill(istream &) = 0;

    // gets and returns itemtpye code
    char getType() const;

    // sets the Item format type
    virtual bool setFormat(char format);

    // increment or decrement availableCopies_
    virtual bool changeAvailable(int num) = 0;

    //---------------------------------------------------------------------------
    // Overloaded Operators
    //---------------------------------------------------------------------------

    /**
     * Less than operator. Compares LHS and RHS for lesser value.
     */
    virtual bool operator<(const Item &rhsItem) const = 0;

    /**
     * Greater than operator. compares LHS and RHS for greater value.
     */
    virtual bool operator>(const Item &rhsItem) const = 0;

    /**
     * Equals operator. Determines if two Item objects are equal.
     */
    virtual bool operator==(const Item &rhsItem) const = 0;

    /**
     * Does not equals operator. Determines if two items are not equal.
     */
    virtual bool operator!=(const Item &rhsItem) const = 0;

  protected:
    // Item type code
    char itemType_;

    // format type code
    char format_;

    static const int FORMATS = 26;

    // array of knwon and valid format types
    bool validFormat[FORMATS] = {false};
};

#endif
