//---------------------------------------------------------------------------
// shelf.h
//---------------------------------------------------------------------------
// Holds containers of items of different genres.
//
// Assumptions:
//  -- each genre is uniquely identified by a letter
//  -- there cannot be two genres with the same letter
// Implementation
//  -- containers[]
//  -- uses a hash table to store containers for differnt genres
//  -- each genre is associated with a letter e.g: F- fiction
//  -- array size is 26, letters a...z correlate directly to index 0...25
//  -- uses a hash table of binary search trees to store the books
//  -- first letter of genre is stored as char
//  -- no destructor - no dynamically allocated memory
//---------------------------------------------------------------------------

#ifndef SHELF
#define SHELF

#include "itemcontainer.h"
#include "itemfactory.h"

class Shelf {

  public:
    Shelf(); // contructor

    ~Shelf(); // destructor

    // inserts book into a container
    bool insert(Item *);

    // interface between data file and book addition
    bool buildLibrary(istream &in);

    // checks and gets the item that needs to be checked out
    bool retrieve(Item &target, Item *&toReturn);

    // displays all the contents of containers to console

    void display() const;

  private:
    static const int ITEM_TYPES = 26;

    // hash funtion to get genre
    int hash(char) const;

    // array of known item Types
    bool validCodes[ITEM_TYPES];

    // array that stores containers by genre
    ItemContainer *containers[ITEM_TYPES];
};

#endif
