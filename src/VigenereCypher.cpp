#include "../include/VigenereCypher.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

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
    _vigenereSquare = new char[_BOX_WIDTH * _BOX_WIDTH]();

    int temp(0);

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


void VigenereCypher::printInputVector()
{
    for (int i = 0; i < _pageLine.size(); i++)
    {
        std::cout << _pageLine.at(i) << std::endl;
    }

    std::cout << _pageLine.size();
}


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


char VigenereCypher::iterThroughKey(int& pos)
{
    pos++;

    if (pos >= _cypherKey.length() || pos < 0)
    {
        pos = 0;
    }

    char returnChar = _cypherKey[pos];

    return returnChar;
}


int VigenereCypher::getCol(char inputChar)
{
    int colInt = static_cast<int>(inputChar);
    return colInt - 32;
}


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
        {
            return i;
        }
    }
}


void VigenereCypher::cypherInput()
{
    int cyphPos(-1), cypherRow(0), cypherCol(0);


    for (int i = 0; i < _pageLine.size(); i++)
    {
        for (int j = 0; j < _pageLine[i].size(); j++)
        {
            if(_pageLine[i].at(j) == '\n')
            {
                _pageLine[i].at(j) = ' ';
            }

             cypherRow = getRow(cyphPos);
             cypherCol = getCol(_pageLine[i].at(j));

            _pageLine[i].at(j) = _vigenereSquare[index(cypherRow, cypherCol)];
        }
    }
}


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


void VigenereCypher::outputToFile()
{

    std::ofstream fOut("CypherOutput.txt");

    if (!fOut)
    {
        std::cerr << "Output file could not be created";
        exit(1);
    }

    for (int i = 0; i < _pageLine.size(); i++)
    {
        fOut << _pageLine.at(i);
        i++;
    }

}


VigenereCypher::~VigenereCypher()
{
    delete[] _vigenereSquare;
}
