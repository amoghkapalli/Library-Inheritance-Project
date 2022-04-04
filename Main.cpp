#include "Library.h"
#include <fstream>
#include <iostream>

using namespace std;
int main() {

    Library lib;
    ifstream books;
    ifstream patrons;
    ifstream commands;

    patrons.open("data4patrons.txt");
    books.open("data4books.txt");
    commands.open("data4commands.txt");
    lib.buildPatrons(patrons); // add patrons

    
    lib.buildLibrary(books); // initialize books

    
    
    lib.performCommands(commands); // read and execute commands

    return 0;
}