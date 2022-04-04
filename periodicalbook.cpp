//---------------------------------------------------------------------------
// periodicalbook.cpp
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

#include "periodicalbook.h"
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

//---------------------------------------------------------------------------
// default constructor
PeriodicalBook::PeriodicalBook() {
    month_ = 0;
    year_ = 0;
    title_ = "";
    itemType_ = 'P';
    availableCopies_ = COPIES;
    totalCopies_ = COPIES;
}

//---------------------------------------------------------------------------
// destructor
PeriodicalBook::~PeriodicalBook() {}

//---------------------------------------------------------------------------
// buildBook
// file format: type title, month year
bool PeriodicalBook::buildItem(istream &in) {
    string title;
    int month;
    int year;

    getline(in, title, ',');
    in.get(); // remove blank space
    in >> month;
    in.get(); // remove blank space
    in >> year;
    setTitle(title);
    setMonth(month);
    setYear(year);

    return (getTitle() == title && getMonth() == month && getYear() == year);
}

//---------------------------------------------------------------------------
// create
// file format: type title, month year
Item *PeriodicalBook::create() { return new PeriodicalBook(); }

//---------------------------------------------------------------------------
// create
// file format: type year, month title
void PeriodicalBook::fill(istream &inFile) {
    inFile >> year_;
    inFile >> month_;
    inFile.get();
    getline(inFile, title_, ',');
}

//---------------------------------------------------------------------------
// display
void PeriodicalBook::display() const {
    cout << setw(7) << left << availableCopies_ << setw(7) << month_ << setw(11)
         << left << year_ << setw(26) << title_ << endl;
}

//---------------------------------------------------------------------------
// errorDisplay
void PeriodicalBook::errorDisplay() const {
    cout << endl
         << "ERROR: Item: " << setw(12) << left << title_.substr(0, 28)
         << " was not found in the library!";
}

void PeriodicalBook::historyDisplay() const {
    cout << setw(7) << left << month_ << setw(11) << left << year_ << setw(26)
         << title_ << endl;
}
int PeriodicalBook::getCopiesAvailable() const { return availableCopies_; }
//---------------------------------------------------------------------------
// setMonth
bool PeriodicalBook::setMonth(int month) {
    bool success = false;
    if (month > 0 && month <= 12) {
        month_ = month;
        success = true;
    } else {
        cout << "ERROR: Month \"" << month << "\" is an invalid month" << endl;
        success = false;
    }
    return success;
}

//---------------------------------------------------------------------------
// getMonth
int PeriodicalBook::getMonth() const { return month_; }

void PeriodicalBook::displayBookHeader() const {

    cout << endl
         << "PERIODICAL BOOKS" << endl
         << "AVAIL  MONTH  YEAR       TITLE" << endl;
}

//---------------------------------------------------------------------------
// setYear
bool PeriodicalBook::setYear(int year) {
    bool success = false;
    if (year > 0) {
        year_ = year;
        success = true;
    } else {
        cout << "ERROR: Year \"" << year << "\" is an invalid year" << endl;
        success = false;
    }
    return success;
}

//---------------------------------------------------------------------------
// getYear
int PeriodicalBook::getYear() const { return year_; }

//---------------------------------------------------------------------------
// changeAvailable
bool PeriodicalBook::changeAvailable(int num) {
    bool success = false;
    // if return, check that a copy is missing
    if (num == 1 && availableCopies_ < COPIES) {
        availableCopies_ += num;
        success = true;
    }
    // if checkout, make sure there are copies
    if (num == -1 && availableCopies_ > 0) {
        availableCopies_ += num;
        success = true;
    }
    return success;
}

//---------------------------------------------------------------------------
// overloaded comparison operators
// Periodicals sorted by date (year, then month), then by title
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// overloaded operator<
bool PeriodicalBook::operator<(const Item &rhsItem) const {
    bool holder = false;

    // cast book to preiodical book
    const PeriodicalBook &rhsBookCasted =
        static_cast<const PeriodicalBook &>(rhsItem);

    // compare year
    if (year_ < rhsBookCasted.getYear()) {
        holder = true;
    }
    // if year is the same compare month
    else if (getYear() == rhsBookCasted.getYear()) {
        if (month_ < rhsBookCasted.getMonth()) {
            holder = true;
        }
        // if the month is the same compare title
        else if (month_ == rhsBookCasted.getMonth()) {
            if (title_ < rhsBookCasted.getTitle()) {
                holder = true;
            }
        }
    }

    return holder;
}

//---------------------------------------------------------------------------
// overloaded operator >

bool PeriodicalBook::operator>(const Item &rhsItem) const {
    bool holder = false;

    // cast book to preiodical book
    const PeriodicalBook &rhsBookCasted =
        static_cast<const PeriodicalBook &>(rhsItem);

    // compare year
    if (year_ > rhsBookCasted.getYear()) {
        holder = true;
    }
    // if year is the same compare month
    else if (getYear() == rhsBookCasted.getYear()) {
        if (month_ > rhsBookCasted.getMonth()) {
            holder = true;
        }
        // if the month is the same compare title
        else if (month_ == rhsBookCasted.getMonth()) {
            if (title_ > rhsBookCasted.getTitle()) {
                holder = true;
            }
        }
    }

    return holder;
}

//---------------------------------------------------------------------------
// overloaded operator==
bool PeriodicalBook::operator==(const Item &rhsItem) const {
    bool holder = false;

    // cast rhs book to periodical's book
    const PeriodicalBook &rhsBookCasted =
        static_cast<const PeriodicalBook &>(rhsItem);

    // compare year, month, title
    if (year_ == rhsBookCasted.getYear() &&
        month_ == rhsBookCasted.getMonth() &&
        title_ == rhsBookCasted.getTitle()) {
        holder = true;
    }

    return holder;
}

//---------------------------------------------------------------------------
// overloaded operator!=
bool PeriodicalBook::operator!=(const Item &rhsItem) const {
    // use comparison operator to return value
    return !(*this == rhsItem);
}
