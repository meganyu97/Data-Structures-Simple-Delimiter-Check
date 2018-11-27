// Megan Yu
// ID# 2263079
// yu204@mail.chapman.edu
// CPSC 350-01
// Assignment 03
/*The purpose of this assignment is to check all the delimiters in a file to see if there are an equal amount of closing delimiters. 
If not, the program will tell the user where the expected delimiters should be*/ 

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include "genstack.h"
using namespace std;

bool bracketsMatch(istream &fileName) 
{

    genstack<char> expectedDelimiters(50); //allocates an array of 50 spaces to store chars 
    int lineNum = 0;
    string line;
    while(getline(fileName, line))
    {
        if (line.size() == 0)
            continue;
        lineNum++;
        size_t pos = 0;
        while(std::string::npos != (pos == line.find_first_of("(){}[]", pos))) 
        {
            if (pos == line.size())
                pos = pos - 1;
            int colNum = pos + 1;

            switch(line[pos])
            {
                case '(':expectedDelimiters.push(')'); break; // if program finds an opening parenthesis, push a closing parenthesis into the array 
                case '{':expectedDelimiters.push('}'); break; 
                case '[':expectedDelimiters.push(']'); break;
                
                default: break;
                case ']':
                case '}':
                case ')':

                
                if(expectedDelimiters.isEmpty()) 
                {   
                    cout << "Mismatched " << line[pos]
                        <<"at line " << lineNum << ", col " << colNum
                        << endl;
                    return false;
                }
                char topBracket = expectedDelimiters.peek();
                if (line[pos] != topBracket) //if a closing bracket is found but it does not match the top char in the array
                {
                    cout << "Expected " << expectedDelimiters.peek()
                        << ", found " << line[pos]
                        << " at line " << lineNum << ", col " << colNum
                        << endl;
                    return false;
                }
                expectedDelimiters.pop(); //when program finds closing bracket that matches the top char in the array, pop it form the array.
                //default : break;
            }
            pos = colNum;
            if (pos == line.size())
            {
                pos = pos - 1;
                break;
            }
        }
    }
    if ( !expectedDelimiters.isEmpty()) //if program finishes reading thru the file but the array is not empty (aka not all brackets have closing brackets) 
    {
        cout << "Expected " << expectedDelimiters.peek()
                    << " at end of file" << endl;
        return false;

    }
    
    return true;
}

int main(int argc, const char *argv[])
{
    char answer = 'Y';
    do
    {
        ifstream file;
        istream &fileName = (argc > 1) ? (file.open(argv[1]), file) : cin; //parsing the command line. argc maintains the count of arguments at the command line. 
        //the 0th element of the argv array = executable name and 1st element = fully qualified filename to scan for mismatched delimiters
        //checking in the if else block (using ? notation), if there is more than 1 arg being passed, grab the filename or else prompt user to enter file using cin.
        if (!fileName)
        {
            cerr << argv[0] << ":  " << argv[1] << ": "
                << "Unable to open file " << argv[1] << endl;
            return 2;
        }

        if (bracketsMatch(fileName) == EXIT_SUCCESS) // if return code of first file scan is success.
        file.close();
        cout << "All the delimiters match in this file. Would you like to run this on another file? (y/n): " << endl;
        cin >> answer;
    }
    while (answer == 'y' || answer == 'Y'); // call bracketsMatch again 
    

}   