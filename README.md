# ISE CS4455

# David Laffey: 22385959

## Project Structure
root
|---lexer.l - The lexer file that defines the tokens
│---parser.txt - input file
│---parser.y - parser file (run from here)
|---bucol.c
|---bucol.h 
|---table.h 
|---table.c 

## Build Instructions
Readme:
To run the compiler either use the coderunner setup I already have and press the play button from the parser.y file which runs all the necessary files and takes the input txt called parser.txt.



OR :
To run the compiler put these commands in the terminal and the text you want to compile in the parser.txt file:

fileName="parser.y"

dir=$(dirname "$fileName")

filename=$(basename "$fileName" .y)

flex -o del.yy.c "$filename".l

bison -d "$fileName

gcc -o "$filename".out del.yy.c "$filename".tab.c bucol.c table.c -lm

./"$filename".out < "$filename".txt

# features
 - declaring variables
 - assigning values to variables
 - adding
 - printing strings to terminal
 - finishing the program
- get input


