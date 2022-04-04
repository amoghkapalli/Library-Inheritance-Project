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
//  -- separate display methods
//
//---------------------------------------------------------------------------

#include "childrenbook.h"
#include "Book.h"
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;
//---------------------------------------------------------------------------
// Constructor
ChildrenBook::ChildrenBook() {
    author_ = "";
    year_ = 0;
    itemType_ = 'C';
    availableCopies_ = COPIES;
    totalCopies_ = COPIES;
}

//---------------------------------------------------------------------------
// Destruct1or
ChildrenBook::~ChildrenBook() {}

//---------------------------------------------------------------------------
// buildBook
bool ChildrenBook::buildItem(istream &inFile) {
    string title = "";
    string author = "";
    int year;

    // set methods used to verify incoming data is valid
    getline(inFile, author, ',');
    inFile.get(); // remove blank space
    getline(inFile, title, ',');
    inFile.get(); // remove blank space
    inFile >> year;
    setAuthor(author);
    setTitle(title);
    setYear(year);

    return (getAuthor() == author && getTitle() == title && getYear() == year);
}

//---------------------------------------------------------------------------
// create
Item *ChildrenBook::create() {
    // dynamic memory deallocated in itemContainer
    return new ChildrenBook();
}

//---------------------------------------------------------------------------
// fill
// command file data format: title, author
void ChildrenBook::fill(istream &inFile) {
    getline(inFile, title_, ',');
    inFile.get(); // remove blank space
    getline(inFile, author_, ',');
}

//---------------------------------------------------------------------------
// display
void ChildrenBook::display() const {
    cout << setw(7) << left << availableCopies_ << setw(32) << left
         << title_.substr(0, 28) << setw(36) << left << author_ << setw(5)
         << left << year_ << endl;
}

//---------------------------------------------------------------------------
// errorDisplay
void ChildrenBook::errorDisplay() const {
    cout << endl
         << "ERROR: Item: " << setw(12) << left << title_.substr(0, 28) << "by "
         << setw(12) << left << author_ << " was not found in the library";
}

//---------------------------------------------------------------------------
// historyDisplay
void ChildrenBook::historyDisplay() const {

    cout << setw(32) << left << title_.substr(0, 28) << setw(25) << left
         << author_ << setw(5) << left << year_ << endl;
}

//---------------------------------------------------------------------------
// displayBookHeader()
void ChildrenBook::displayBookHeader() const {
    cout << endl << "CHILDREN BOOKS" << endl << "AVAIL  TITLE                 ";
    cout << "          AUTHOR                              YEAR" << endl;
}

//---------------------------------------------------------------------------
// getCopiesAvailable
int ChildrenBook::getCopiesAvailable() const { return availableCopies_; }

//---------------------------------------------------------------------------
// setAuthor
void ChildrenBook::setAuthor(string author) { author_ = author; }

//---------------------------------------------------------------------------
// getAuthor
string ChildrenBook::getAuthor() const { return author_; }

//---------------------------------------------------------------------------
// setYear
bool ChildrenBook::setYear(int year) {
    if (year > 0) {
        year_ = year;
        return true;
    }
    return false;
}

//---------------------------------------------------------------------------
// getYear
int ChildrenBook::getYear() const { return year_; }

//---------------------------------------------------------------------------
// changeAvailable
bool ChildrenBook::changeAvailable(int num) {
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
// Children sorted by title, then author
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// overloaded operator <
bool ChildrenBook::operator<(const Item &rhsItem) const {
    bool holder = false;

    // cast book to children's book
    const ChildrenBook &rhsBookCasted =
        static_cast<const ChildrenBook &>(rhsItem);

    // compare titles
    (getTitle() < rhsBookCasted.getTitle()) ? holder = true : holder = false;

    // if the book titles are the same compare authors
    if (getTitle() == rhsBookCasted.getTitle()) {
        (getAuthor() < rhsBookCasted.getAuthor()) ? holder = true
                                                  : holder = false;
    }
    return holder;
}

//---------------------------------------------------------------------------
// overloaded operator>
bool ChildrenBook::operator>(const Item &rhsItem) const {
    bool holder = false;

    // cast book to children's book
    const ChildrenBook &rhsBookCasted =
        static_cast<const ChildrenBook &>(rhsItem);

    // compare titles, adjust bool as needed
    (getTitle() > rhsBookCasted.getTitle()) ? holder = true : holder = false;

    // if the book titles are the same compare authors
    if (getTitle() == rhsBookCasted.getTitle()) {
        (getAuthor() > rhsBookCasted.getAuthor()) ? holder = true
                                                  : holder = false;
    }
    return holder;
}

//---------------------------------------------------------------------------
// overloaded operator==
bool ChildrenBook::operator==(const Item &rhsItem) const {
    bool holder = false;
    if (this->getType() != rhsItem.getType()) {
        return holder;
    }
    // cast rhs book to children's book
    const ChildrenBook &rhsBookCasted =
        static_cast<const ChildrenBook &>(rhsItem);

    // compare author, title, and year between two books
    // read error here TODO
    if (rhsBookCasted.getAuthor() == getAuthor() &&
        rhsBookCasted.getTitle() == getTitle()) {
        holder = true;
    }
    return holder;
}

//---------------------------------------------------------------------------
// overloaded operator !=
bool ChildrenBook::operator!=(const Item &rhsItem) const {
    // use comparison operator to return value
    return !(*this == rhsItem);
}