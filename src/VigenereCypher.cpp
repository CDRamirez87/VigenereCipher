#include "../include/VigenereCypher.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

//TODO: Allow the user to provide a name for the output file

VigenereCypher::VigenereCypher() :
    _BOX_WIDTH(95)
    {
        cypherInit();
    }

VigenereCypher::VigenereCypher(std::string fileName) :
     VigenereCypher()
{
    processInput(fileName);
}

VigenereCypher::VigenereCypher(std::string fileName, std::string cypherKey) :
    VigenereCypher(fileName)
{
    setCypherKey(cypherKey);
}



void VigenereCypher::cypherInit()
{
    //Creates an array to hold Vigenere box
    _vigenereSquare = new char[_BOX_WIDTH * _BOX_WIDTH]();

    int temp(0);

    //Iterates through the box and writes an integer corresponding to an ASCII character
    //in a Vigenere pattern
    for (int row = 0; row < _BOX_WIDTH; row++)
    {
        for (int col = 0; col < _BOX_WIDTH; col++)
        {
            temp = (row + col + 32);

            if (temp > 126)
            {
                temp -= _BOX_WIDTH;
            }

            _vigenereSquare[index(row, col)] = temp;
        }
    }
}

//Prints the square, used for debugging
void VigenereCypher::printSquare()
{
    for (int row = 0; row < _BOX_WIDTH; row++)
    {
        for (int col = 0; col < _BOX_WIDTH; col ++)
        {
            if (col == 0)
                std::cout << "\n\n";

            std::cout << _vigenereSquare[index(row, col)] << " ";
        }

    }
}

//Prints the vector containing the file input, used for debugging
void VigenereCypher::printInputVector()
{
    for (int i = 0; i < _pageLine.size(); i++)
        std::cout << _pageLine.at(i) << std::endl;

    std::cout << _pageLine.size();
}

//Opens the selected file and reads each line into a vector element
void VigenereCypher::processInput(std::string fileName)
{
    std::ifstream inputFile(fileName);

    if (!inputFile)
    {
        std::cerr << "Input file could not be opened for reading";
        exit(1);
    }

    while (inputFile)
    {
        std::string lineBuffer;
        std::getline(inputFile, lineBuffer);
        _pageLine.push_back(lineBuffer);
    }

}

//Iterates through the encryption key and returns each character one at a time
char VigenereCypher::iterThroughKey(int& pos)
{
    pos++;

    if (pos >= _cypherKey.length() || pos < 0)
        pos = 0;

    char returnChar = _cypherKey[pos];

    return returnChar;
}

//Finds the correct column in the Vigenere box for the encryption char
int VigenereCypher::getCol(char inputChar)
{
    int colInt = static_cast<int>(inputChar);
    return colInt - 32;
}

//Finds the correct row in the Vigenere box for the encryption char
int VigenereCypher::getRow(int& pos)
{
    char nextChar = iterThroughKey(pos);
    int charInt = static_cast<int>(nextChar);
    return charInt - 32;
}


int VigenereCypher::searchCol(char searchTarg, int row)
{
    for (int i = 0; i < _BOX_WIDTH; i++)
    {
        if (_vigenereSquare[index(row, i)] == searchTarg)
            return i;
    }
}

//Iterates through the characters in the input file and encrypts them
//NOTE: Changes newlines into spaces to obfuscate format
void VigenereCypher::cypherInput()
{
    int cyphPos(-1), cypherRow(0), cypherCol(0);


    for (int i = 0; i < _pageLine.size(); i++)
    {
        for (int j = 0; j < _pageLine[i].size(); j++)
        {
            if(_pageLine[i].at(j) == '\n')
                _pageLine[i].at(j) = ' ';

             cypherRow = getRow(cyphPos);
             cypherCol = getCol(_pageLine[i].at(j));

            _pageLine[i].at(j) = _vigenereSquare[index(cypherRow, cypherCol)];
        }
    }
}

//Iterates through the input file and decrypts each character
void VigenereCypher::decypherInput()
{
    int cyphPos(-1), cypherRow(0), cypherCol(0);
    char finalChar(' ');

    for (int i = 0; i < _pageLine.size(); i++)
    {
        for (int j = 0; j < _pageLine[i].size(); j++)
        {
            cypherRow = getRow(cyphPos);
            cypherCol = searchCol(_pageLine[i].at(j), cypherRow);

            finalChar = (_vigenereSquare[index(0, cypherCol)]);
            _pageLine[i].at(j) = finalChar;
        }
    }
}

//Creates or opens an output file and writes each line in the _pageLine vector to it
void VigenereCypher::outputToFile()
{

    std::ofstream fOut("CipherOutput.txt");

    if (!fOut)
    {
        std::cerr << "Output file could not be created";
        exit(1);
    }

    for (int i = 0; i < _pageLine.size(); i++)
        fOut << _pageLine.at(i);
}

//Destructor
VigenereCypher::~VigenereCypher()
{
    delete[] _vigenereSquare;
}
