// CommandManager handles the operations of looping through the command
// data file. Interface between library object, command object, and data
// file.
//
// Assumptions:
//  -- data file will be correctly formatted
//  -- data file will contain no empty lines
//
// Implementation:
//  -- reaching eof character breaks the for loop
//  -- prints error messages on invalid input from file
//---------------------------------------------------------------------------

#include "commandmanager.h"
#include "commandfactory.h"
#include "Library.h"
#include "patron.h"
#include <sstream>

//---------------------------------------------------------------------------
// Constructor
CommandManager::CommandManager() {
    unstoredCommands[3] = true;
    unstoredCommands[7] = true;
}

//---------------------------------------------------------------------------
// runCommands
bool CommandManager::performCommands(istream &inFile, Library *library) {
    // instantiate bool tracker
    bool success = false;

    // create storage for command char

    for (;;) {
        // read the line of data and store it
        string dataLine;
        getline(inFile, dataLine);
        // check for eof
        if (inFile.eof()) {
            // data file read succesfully
            success = true;
            break;
        }
        stringstream commandLine(dataLine);

        // read the first char of ss and create command obj
        char commandType = 0;
        commandLine >> commandType;
        CommandFactory commFactory;

        // create pointer to empty command
        Command *newCommand = nullptr;

        // createCommand must check for type errors
        newCommand = commFactory.createCommand(commandType);

        // if the type was invalid, delete the command object and continue loop
        if (newCommand == nullptr) {
            // output error message
            cout << endl
                 << "ERROR: Command: \"" << commandType
                 << "\" is an invalid command" << endl;
            continue;
        }

        // send the rest of the data line to the empty command object
        // buildCommand will handle format for each sub command
        if (newCommand->buildCommand(commandLine, library)) {

            // if all formatting was correct, execute command.
            // execute will add to patron history if applicable
            if (newCommand->execute()) {

                // delete executed commands that are not stored in patron
                // history lists
                if (unstoredCommands[commandType - 'A']) {
                    delete newCommand;
                    newCommand = nullptr;
                }
            }
            // delete commands that did not execute
            else {
                delete newCommand;
                newCommand = nullptr;
            }
        }
        // if command could not succesfully be built, deallocate memory
        else {
            delete newCommand;
            newCommand = nullptr;
        }
    }

    return success;
}