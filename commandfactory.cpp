// A command factory class to create new instances of command objects.
//
// Assumptions:
//  -- Each command will have a unique char identifier
//
// Implementation:
//  -- character case is handled by the hash
//---------------------------------------------------------------------------

#include "commandfactory.h"
#include "checkout.h"
#include "display.h"
#include "history.h"
#include "return.h"

//---------------------------------------------------------------------------
// commandFactory()
CommandFactory::CommandFactory() {
    // Checkout, display, Return, History
    commandTypes[2] = new Checkout;
    commandTypes[3] = new Display;
    commandTypes[7] = new History;
    commandTypes[17] = new Return;
}

//---------------------------------------------------------------------------
// destructor()
CommandFactory::~CommandFactory() {
    for (int i = 0; i < ALPHABET; i++) {
        if (commandTypes[i] != nullptr) {
            delete commandTypes[i];
            commandTypes[i] = nullptr;
        }
    }
}

//---------------------------------------------------------------------------
// createCommand()
Command *CommandFactory::createCommand(char type) {
    if (type < 'A' || type > 'z') {
        return nullptr;
    }

    // create new command pointer
    Command *toReturn = nullptr;

    // create subscript from hash
    int subscript = hash(type);

    // if command exists at hash location
    if (subscript > 0 && commandTypes[subscript] != nullptr) {
        toReturn = commandTypes[subscript]->create();
    }

    return toReturn;
}

//---------------------------------------------------------------------------
// hash
int CommandFactory::hash(char type) const {
    int subscript = 0;
    if (type > 'A' && type < 'z') {
        // change to uppercase if it's not
        type = toupper(type);
        subscript = type - 'A';
    }
    return subscript;
}