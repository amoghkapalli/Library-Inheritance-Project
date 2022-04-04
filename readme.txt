1. Describe the state of your program, exactly what works and what does 
not work.
I believe that everything in this program works the way it is supposed to.
I got the output the exact same as the output from the example outputs. The
class book is a subclass of item which is the parent of the differet 
types of books. Having aitem class allows this program to be extended to have
additional types of data to be added to the classes. In addition, having a item
factory allows for different types of items only if the items are virtual.

2. List your hash table(s) that you wrote (not STL) - briefly what they
 are used for and file they are found in. (Include any factories that are 
 essentially hash tables).
I use a hash table to store containers for different genres and a hashtable
for storing the specific genres of books depending on the way they need to be 
ordered. In shelf, the hash table stores the values for the different genres.
A hash table of binary search trees stores the books.

3. State which file and which function you read the book data, just high-level
 function calls, i.e., how/where it gets into your collections.
For the book data, after reading the file in from the main, I call the 
buildLibrary method in library.cpp which is where I then go to the shelf class
to create a new Item* for every line. I then keep track of the genre and add 
the books line by line checking if there are duplicates and if it 
is a valid code. If the item was then successfully inserted, then the loop 
continues. henever a book cannot be built, the item is deleted.


4. State which file and which function you read the command data, high-level
 function calls, how/where you perform the commands.
For the command data, after reading the file in from the main, I call the 
performCommands method in library.cpp which then calls the performCommands
in the commandManager. This again goes through line by line checking the 
first char and if it is a appropriate command and if so, then the entire line
is built. Whenever a new command cannot be built, the command is deleted.
Otherwise, the command is executed and added to the history.


5. Describe any dirty little secrets (e.g., switch used, or if-else-if, etc.)  
If you feel they do not violate the open-closed design principle, explain.
I didnt use anything which I believe violates the open-closed principle
such as switch statements. This is why I used itemfactory and a command 
factory because this allows for item and command actions to have setData.

6. Describe anything you are particularly proud of ...
I am proud of having so many allocs and yet no memory leaks and dealing 
with these little by little. I origianlly expected to have so many and 
having to investigate piece by piece but I lucky didnt have to.