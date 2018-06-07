#include <iostream>
#include <vector>
#include ".\include\VigenereCypher.h"

int main(int argc, char* argv[])
{

    if (argc != 3)
    {
        std::cout << "Usage:" << argv[0] << " filename key" << "\n";
        exit(1);
    }

    VigenereCypher newCypher(argv[1], argv[2]);

    newCypher.cypherInput();

    newCypher.outputToFile();

}
