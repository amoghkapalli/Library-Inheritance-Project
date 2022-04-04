//---------------------------------------------------------------------------
// ItemContainer.cpp
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

#include "itemcontainer.h"

//---------------------------------------------------------------------------
// Node functions
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Node Constructor
ItemContainer::Node::Node() {
    item = nullptr;
    left = nullptr;
    right = nullptr;
}

//---------------------------------------------------------------------------
// Node Destructor
ItemContainer::Node::~Node() {
    delete item;
    item = nullptr;
    left = nullptr;
    right = nullptr;
}

//---------------------------------------------------------------------------
// ItemContainer Methods

//---------------------------------------------------------------------------
// constructor
ItemContainer::ItemContainer() {
    root = nullptr;
    type = ' ';
}

//---------------------------------------------------------------------------
// Destructor
ItemContainer::~ItemContainer() { makeEmpty(); }

//---------------------------------------------------------------------------
// insert
bool ItemContainer::insert(Item *theItem) {
    bool success = false;

    // and the book is not already in container
    if (!isInContainer(theItem)) {
        // then send to insertNode
        Node *toInsert = new Node();
        toInsert->item = theItem;
        if (insertNode(toInsert)) {
            success = true;
        }
    }
    return success;
}

//---------------------------------------------------------------------------
// retrieve
bool ItemContainer::retrieve(Item &target, Item *&returned) const {
    returned = nullptr;
    bool success = false;
    Node *cur = root;

    while (cur != nullptr) {
        if (*cur->item == target) {
            success = true;
            returned = cur->item;
            break;
            // move to left subtree
        } else if (target < *cur->item && cur->left != nullptr) {
            cur = cur->left;
            // move to right subtree
        } else if (target > *cur->item && cur->right != nullptr) {
            cur = cur->right;
        }
        // not found break loop and return
        else {
            break;
        }
    }

    return success;
}

//---------------------------------------------------------------------------
// isInContainer
bool ItemContainer::isInContainer(Item *target) const {
    Item *temp;
    return retrieve(*target, temp);
}

//---------------------------------------------------------------------------
// display
void ItemContainer::display() const {

    if (root != nullptr) {
        root->item->displayBookHeader();
        displayHelper(root);
    }
}

//---------------------------------------------------------------------------
// displayHelper
// recursive helper for display
void ItemContainer::displayHelper(Node *cur) const {
    if (cur == nullptr) {
        return;
    }
    displayHelper(cur->left);
    cur->item->display();
    displayHelper(cur->right);
}

//---------------------------------------------------------------------------
// makeEmpty
void ItemContainer::makeEmpty() {
    if (root != nullptr) {
        clear(root);
    }
}

//---------------------------------------------------------------------------
// clear
// recursive helper function for makeEmpty
void ItemContainer::clear(Node *cur) {
    // base case
    if (cur == nullptr) {
        return;
    }
    // post-order traversal
    clear(cur->left);
    clear(cur->right);
    delete cur;
    cur = nullptr;
}

//---------------------------------------------------------------------------
// isEmpty
bool ItemContainer::isEmpty() const { return (root == nullptr); }

//---------------------------------------------------------------------------
// setGenre
// genre can only be set on an empty bookContainer object
// once books are stored the genre can not be changed
bool ItemContainer::setGenre(char genre) {
    bool success = false;
    if (root == nullptr && genre >= 'A' && genre <= 'z') {
        // uppercase for consistency
        type = toupper(genre);
        success = true;
    }
    return success;
}

//---------------------------------------------------------------------------
// getGenre
char ItemContainer::getGenre() const { return type; }

//---------------------------------------------------------------------------
// insertNode
// helper function to insert into a tree
bool ItemContainer::insertNode(Node *node) {
    bool inserted = false;

    // if the tree is empty
    if (root == nullptr) {
        root = node;
        inserted = true;
    }
    // if its not empty traverse the tree
    else {
        Node *cur = root;
        // if the book is less thn the curernt book insert in the left subtree
        // otherwise insert in the right subtree

        while (!inserted) {
            // if its less than
            if (*node->item < *cur->item) {
                // and there is an empty space, insert
                if (cur->left == nullptr) {
                    cur->left = node;
                    inserted = true;
                }
                // if theres not an empty space move cur left
                else {
                    cur = cur->left;
                }
            }
            // if its greater than
            else if (*node->item > *cur->item) {
                // and theres an empty space, insert
                if (cur->right == nullptr) {
                    cur->right = node;
                    inserted = true;
                }
                // otherwise move right
                else {
                    cur = cur->right;
                }
            }
            // if its equal, delete the node and return false
            else if (*node->item == *cur->item) {
                node->item = nullptr;
                delete node;
                node = nullptr;
                inserted = false;
                break;
            }
        }
    }

    return inserted;
}