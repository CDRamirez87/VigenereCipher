#include <iostream>
#include <vector>
#include ".\include\VigenereCypher.h"

int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        std::cout << "Usage: \"./VigenereCypherWin.exe 'encrypt/decrypt' 'Input Filename' 'Encryption Key'" << std::endl;
        exit(1);
    }

    std::string enOrDe(argv[1]);

    VigenereCypher newCypher(argv[2], argv[3]);

    if(enOrDe == "encrypt" || enOrDe == "Encrypt")
        newCypher.cypherInput();
    else if(enOrDe == "decrypt" || enOrDe == "Decrypt")
        newCypher.decypherInput();
    else
        std::cout << "Usage:" << argv[0] << "\"encrypt\" or \"decrypt\" \"Input Filename\" \"Encryption Key\"" << "\n";

    newCypher.outputToFile();

}
