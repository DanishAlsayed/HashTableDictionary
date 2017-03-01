# HashTableDictionary
One of my early university assignments implementing a dictionary using a chained hash table.
Hash Function used: 
H(n) = ((((n0 mod m)x128+n1)mod m x128+n2) . . .+nk-1)mod m 
Where n is the ASCII value of a character in the length k Latin word and m=4603 and the size of the hash table. 
Compiling procedure and execution instructions:
The program is made to run on Linux (e.g. Fedora 16). Please use g++ compiler in the terminal. The command is:
$g++ dictionary.cpp –o dictionary.o
dictionary.o is the object code file that will be executed. To execute, the program requires 2 command line arguments, the file containing the words to be processed (e.g. input.txt which is present in the same directory as dictionary.cpp and dictionary.o) and the file to store the output results (e.g. output.txt will be created in the same directory as well):
$./dictionary.o input.txt output.txt
The results will be written in output.txt.
Note: To run successfully, the file “dict.txt” must be present in the same directory as dictionary.cpp and dictionary.o. This is because dict.txt is the data set that the program reads upon launch to do any processing of commands on its base.
Note: A sample input.txt file is included
