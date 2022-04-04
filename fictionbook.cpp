//---------------------------------------------------------------------------
// fictionbook.cpp
//---------------------------------------------------------------------------
// A fiction book object. Handles the creation and storage of a fiction book,
// containing title, author, number of copies "owned" by the library, and
// copies of this book currently checked in.
//
// Ficiton sorted by author, then title
//
// Implementation:
//  -- initial character in input dictates 'f' for fiction
//---------------------------------------------------------------------------
#include "fictionbook.h"
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

//---------------------------------------------------------------------------
// default constructor
FictionBook::FictionBook() {
    author_ = "";
    year_ = 0;
    title_ = "";
    itemType_ = 'F';
    availableCopies_ = COPIES;
    totalCopies_ = COPIES;
}

//---------------------------------------------------------------------------
// destructor
FictionBook::~FictionBook() {}

//---------------------------------------------------------------------------
// buildBook
// file format: type author, title, year : istream passed in beginning at author
bool FictionBook::buildItem(istream &in) {
    string author;
    string title;
    int year;

    getline(in, author, ',');
    in.get(); // remove blank space
    getline(in, title, ',');
    in.get(); // remove blank space
    in >> year;
    setAuthor(author);
    setTitle(title);
    setYear(year);

    return (getAuthor() == author && getTitle() == title && getYear() == year);
}

//---------------------------------------------------------------------------
// create
Item *FictionBook::create() { return new FictionBook(); }

//---------------------------------------------------------------------------
// fill
// data format: author, title
void FictionBook::fill(istream &inFile) {
    getline(inFile, author_, ',');
    inFile.get(); // remove blank space
    getline(inFile, title_, ',');
}

//---------------------------------------------------------------------------
// dsiplayBookHeader
void FictionBook::displayBookHeader() const {
    cout << endl << "FICTION BOOKS " << endl << setw(39) << "AVAIL  AUTHOR";
    cout << "TITLE                               YEAR" << endl;
}

//---------------------------------------------------------------------------
// display
void FictionBook::display() const {
    cout << setw(7) << left << availableCopies_ << setw(32) << left << author_
         << setw(36) << left << title_.substr(0, 28) << setw(5) << left << year_
         << endl;
}

//---------------------------------------------------------------------------
// errorDisplay
void FictionBook::errorDisplay() const {
    cout << " \"" << setw(10) << left << title_.substr(0, 29) << "\" by "
         << setw(12) << left << author_;
}

//---------------------------------------------------------------------------
// historyDisplay
void FictionBook::historyDisplay() const {
    cout << setw(32) << left << author_ << setw(25) << left
         << title_.substr(0, 22) << setw(5) << left << year_ << endl;
}

//---------------------------------------------------------------------------
// getCopiesAvailable
int FictionBook::getCopiesAvailable() const { return availableCopies_; }
//---------------------------------------------------------------------------
// setAuthor
void FictionBook::setAuthor(string author) { author_ = author; }

//---------------------------------------------------------------------------
// setYear
bool FictionBook::setYear(int year) {
    bool success = false;
    if (year > 0) {
        year_ = year;
        success = true;
    }
    return success;
}

//---------------------------------------------------------------------------
// getAuthor
string FictionBook::getAuthor() const { return author_; }

//---------------------------------------------------------------------------
// getYear
int FictionBook::getYear() const { return year_; }

//---------------------------------------------------------------------------
// changeAvailable
bool FictionBook::changeAvailable(int num) {
    bool success = false;

    if (num == 1 && availableCopies_ < totalCopies_) {
        availableCopies_ += num;
        success = true;
    } else if (num == -1 && availableCopies_ > 0) {
        availableCopies_ += num;
        success = true;
    }
    return success;
}

//---------------------------------------------------------------------------
// overloaded comparison operators
// Fiction sorted by author, then title
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// overloaded operator<
bool FictionBook::operator<(const Item &rhsItem) const {
    bool holder = false;
    const FictionBook &rhsBookCasted =
        static_cast<const FictionBook &>(rhsItem);

    (getAuthor() < rhsBookCasted.getAuthor()) ? holder = true : holder = false;

    // if the book authors are the same, compare titles
    if (getAuthor() == rhsBookCasted.getAuthor()) {
        (getTitle() < rhsBookCasted.getTitle()) ? holder = true
                                                : holder = false;
    }

    return holder;
}

//---------------------------------------------------------------------------
// overloaded operator>
bool FictionBook::operator>(const Item &rhsItem) const {
    bool holder = false;

    // cast book to fiction book
    const FictionBook &rhsBookCasted =
        static_cast<const FictionBook &>(rhsItem);

    // compare titles, adjust bool as needed
    (getAuthor() > rhsBookCasted.getAuthor()) ? holder = true : holder = false;

    // if the book titles are the same compare authors
    if (getAuthor() == rhsBookCasted.getAuthor()) {
        (getTitle() > rhsBookCasted.getTitle()) ? holder = true
                                                : holder = false;
    }
    return holder;
}

//---------------------------------------------------------------------------
// overloaded operator ==
bool FictionBook::operator==(const Item &rhsItem) const {
    bool holder = false;

    // cast rhs book to fiction book
    const FictionBook &rhsBookCasted =
        static_cast<const FictionBook &>(rhsItem);

    // compare author, title, and year between two books
    if (rhsBookCasted.getAuthor() == getAuthor() &&
        rhsBookCasted.getTitle() == getTitle()) {
        holder = true;
    }
    return holder;
}

//---------------------------------------------------------------------------
// overloaded operator !=
bool FictionBook::operator!=(const Item &rhsItem) const {
    return !(*this == rhsItem);
}
