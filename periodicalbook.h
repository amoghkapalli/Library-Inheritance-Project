//---------------------------------------------------------------------------
// periodicalbook.h
//---------------------------------------------------------------------------
// A periodical book object. Handles the creation and storage of a periodical
// book, containing title, author, number of copies "owned" by the library,
// and copies of this book currently checked in.
//
// Assumptions:
//  -- initial character in input dictates 'p' for periodical
//  -- Comparison operators will only be used with other Periodicals
//  -- istream data will always be in the correct format
//
// Implementation:
//  -- data format from command data file handled in fill() method
//  -- data format from book data file handled in buildItem()
//---------------------------------------------------------------------------

#ifndef PERIODICALBOOK_H
#define PERIODICALBOOK_H

#include "Book.h"
#include <iostream>

class PeriodicalBook : public Book {

  public:
    // constructor
    PeriodicalBook();

    /**
     * @brief Destroy the Periodical Book object.
     *
     * @pre: Assumes valid created object to be destroyed
     * @post: Periodical object will be deleted and memory freed
     */
    ~PeriodicalBook();

    /** buildBook
     * @brief creates book object reading from data file
     * @pre: A correctly formatted open data file
     * @post: a new book object
     */
    bool buildItem(istream &in);

    /** create
     * @brief Creates a periodical book object, then returns a copy of that
     * object for the factory to function properly.
     *
     * @return PeriodicalBook copy of newly created book object
     * @post: new periodical book object is created and returned.
     */
    virtual Item *create();

    //---------------------------------------------------------------------------
    /** fill
     * @brief fills data for a periodical item from Command Data file format
     * @pre an empty periodical item
     * @post only author and title data fields are set
     */
    virtual void fill(istream &);

    //---------------------------------------------------------------------------
    /** displayBookHeader
     * @brief displays the categories and format of data for periodcial list
     * @pre none
     * @post periodical book item list header printed to cout
     */
    virtual void displayBookHeader() const;

    //---------------------------------------------------------------------------
    /** display
     * @brief displays the book copies, title, month, and year
     * @post contents displayed to console
     */
    virtual void display() const;

    //---------------------------------------------------------------------------
    /** errorDisplay
     * @brief handles the ouput of an invalid periodical's - prints to console
     * @post error messaged displayed
     */
    virtual void errorDisplay() const;

    //---------------------------------------------------------------------------
    /** historyDisplay
     * @brief formats the output when periodcica Item is displayed from patron
     * history list
     * @pre periodical Item previously added to patron history
     * @post data members printed to console in history format
     */
    virtual void historyDisplay() const;

    //---------------------------------------------------------------------------
    /** getCopiesAvailable
     * @brief gets and returns the available copies of this object
     * @pre none
     * @post availableCopies_ returned
     * @return int of availableCopies_
     */
    virtual int getCopiesAvailable() const;

    /** setMonth
     * @brief sets the publishing month data of the periodical
     * @pre a new periodical book object
     * @post month data member set
     */
    bool setMonth(int month);

    /** getMonth
     * @brief returns the publishing month of the periodical
     * @return month int from 1 -12
     */
    int getMonth() const;

    /** setYear
     * @brief sets the publishing year data of the periodical
     * @pre a new periodical book object
     * @post year data member set
     * @return
     */
    bool setYear(int year);

    /** getYear
     * @brief returns the publishing year of the periodical
     * @return year int
     */
    int getYear() const;


    // increment or decrement availableCopies
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
    // month periodical was written/published
    int month_;

    // year periodical was written/published
    int year_;

    static const int COPIES = 1;
};
#endif // !PERIODICALBOOK_H
