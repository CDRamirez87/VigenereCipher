#include <iostream>
#include <vector>
#include ".\include\VigenereCypher.h"

int main(int argc, char* argv[])
{
    //Error string in case of improper argument usage
    std::string errorString = "Usage: \"./VigenereCipher.exe 'encrypt/decrypt' 'Input Filename' 'Encryption Key'";

    if (argc != 4)
    {
        std::cout << errorString << std::endl;
        exit(1);
    }
    //Instantiate main object
    VigenereCypher newCypher(argv[2], argv[3]);

    //Converts command line char pointer to string
    std::string enOrDe(argv[1]);

    //Option to encrypt or decrypt by command line
    if(enOrDe == "encrypt" || enOrDe == "Encrypt")
        newCypher.cypherInput();
    else if(enOrDe == "decrypt" || enOrDe == "Decrypt")
        newCypher.decypherInput();
    else
    {
        std::cout << errorString << std::endl;
        exit(1);
    }

    //Method to output processed data
    newCypher.outputToFile();

}
