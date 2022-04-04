//---------------------------------------------------------------------------
// ItemContainer.h
//---------------------------------------------------------------------------
// An itemContainer class to contain one genre of books. Acts as interface
// between bookcase and book.
// ItemContainer is a binary search tree containing Node structs that
// Contain pointers to book objects, left child, and right child.
//
// Assumptions:
//  -- container has no limit
//  -- each item is uniquely identified by its sorting criteria
//  -- each ItemContainer will store only one type
//  -- items will not be removed from the library
//
// Implementation
//  -- root data member is a pointer to the root of the tree
//  -- genre_ data member stores the itemContainer genre type
//  -- Does not allow duplicate items to be inserted
//  -- uses a hash table of binary search trees to store the items
//  -- first letter of item title is used to get the array index
//  -- array size is 26, letters a...z correlate directly to index 0...25
//  -- first letter of genre is stored as char
//---------------------------------------------------------------------------

#ifndef ITEMCONTAINER_H
#define ITEMCONTAINER_H

#include "item.h"
#include <iostream>

using namespace std;

class ItemContainer {

  public:
    // constructor
    ItemContainer();

    // destructor
    ~ItemContainer();

    // calls private helper method to insert book as Node is
    bool insert(Item *);

    // sets book to checked out and returns by reference
    bool retrieve(Item &target, Item *&returned) const;

    // checks if an item object is found in the container
    bool isInContainer(Item *target) const;

    // prints the contents of the tree in-order
    void display() const;

    // clears the BookContainer structure
    void makeEmpty();

    // Checks if the BookContainer tree is empty
    bool isEmpty() const;

    // setter method for the genre_ data member
    bool setGenre(char genre);

    // retrieves the BookContainer genre_ data member
    char getGenre() const;

  private:
    // Node struct that holds item objects in tree
    struct Node {

        Item *item;
        Node *left;
        Node *right;

        // default constructor
        Node();
        // destructor
        ~Node();
    };

    // root of the BookContaier BST
    Node *root;

    // genre of this bookcontainer
    char type;

    // inserts a Node object containing a book pointer into the tree
    bool insertNode(Node *);

    // recursive helper function for display
    void displayHelper(Node *cur) const;

    // recursive helper function for makeEmpty
    void clear(Node *cur);
};

#endif
