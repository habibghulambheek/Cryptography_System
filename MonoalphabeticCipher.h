#pragma once
#include "Cipher.h"
#include <cstdlib>
#include <ctime>
using namespace std;



class MonoalphabeticCipher : public Cipher
{
    static int noOfRecords;
    static int totalSize;
    static Cipher** ciphers;
public:
    MonoalphabeticCipher();
    void generateKey();
    void setEncryptedInput(string enc);
    void setDecryptedInput(string dec);
    // ENCRYPTS PLAINTEXT BY MONOALPHABETIC CIPHER
    string encrypt(string plaintext);
    // DECRYPTS PLAINTEXT BY MONOALPHABETIC CIPHER
    string decrypt(string ciphertext);

    string validStr(string enc);

    static void removeCipher(int password);
    static void readFile(string);
    static void writeFile(string);
    static Cipher* searchCipher(int password);
    static void addCipher(Cipher* cipher);
    static void resize();
    static void displayCiphers();
    static void deleteCiphers();
    void setPassword();
};
