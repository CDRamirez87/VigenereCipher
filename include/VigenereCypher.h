#ifndef VIGENERECYPHER_H
#define VIGENERECYPHER_H

#include <iostream>
#include <vector>


class VigenereCypher
{
    public:
        //Constructors
        VigenereCypher();
        VigenereCypher(std::string fileName);
        VigenereCypher(std::string fileName, std::string cypherKey);
        ~VigenereCypher();

        //Getters
        int index(int row, int col) { return (row * _BOX_WIDTH) + col; };
        char getNode(int row, int col) { return _vigenereSquare[index(row, col)]; };

        void printSquare();
        void printInputVector();

        //Setters
        void setCypherKey(std::string key) { _cypherKey = key; }
        void setOutFileName(std::string name) { _outFileName = name; }
        void setInFileName(std::string name) { _inFileName = name; }

        //Methods
        void processInput(std::string fileName);
        void cypherInput();
        void decypherInput();
        void outputToFile();

    private:
        //Members
        const int _BOX_WIDTH;
        char* _vigenereSquare;
        std::string _cypherKey;
        std::string _outFileName;
        std::string _inFileName;
        std::vector<std::string> _pageLine;

        //Private methods
        void cypherInit();
        char iterThroughKey(int& pos);
        int getCol(char inputChar);
        int getRow(int& pos);
        int searchCol(char searchTarg, int row);

};

#endif // VIGENERECYPHER_H
