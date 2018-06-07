# README #

### What is this repository for? ###

A program that encrypts plain text files using a Vigenere cipher.
Version 1.0

### How do I get set up? ###

Once the code is compiled (or by using the .exe in /bin/Release) simply place the file to be encrypted in the same directory
as the .exe and then run the .exe on the command line in the following format:

>./VigenereCipher.exe ["Encrypt" or "Decrypt"] [Filename] [Encryption Key]

For example, if you wanted to encrypt a file called secret.txt, you would use this:

>./VigenereCipher.exe encrypt secret.txt ThisIsTheSecretKey

The encrypted text will appear in the same folder as a .txt labled "CipherOutput.txt"

You can decrypt it as follows:

>./VigenereCipher.exe decrypt CipherOutput.txt ThisIsTheSecretKey

The decrypted text will then be output to another file called CipherOutput.txt, overwriting the original if the name 
wasn't changed.

### Who do I talk to? ###

Author: Christopher Ramirez
Email: c.d.ramirez1987@gmail.com