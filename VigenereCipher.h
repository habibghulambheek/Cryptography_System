#pragma once
#include "Cipher.h"
using namespace std;

// Inherit vigenere class from class Cipher
class VigenereCipher : public Cipher
{
protected:
    // to check whether the input is alphabetic or not
    bool isABC(char ch)
    {
        return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
    }

    bool isSmall(char ch)
    {
        return ch >= 'a' && ch <= 'z';
    }

    bool isBIG(char ch)
    {
        return ch >= 'A' && ch <= 'Z';
    }

    static int noOfRecords;
    static int totalSize;
    static Cipher** ciphers;
public:
    VigenereCipher();
    void setKey(string key);
    string vigenereEncrypt();
    string vigenereDecrypt();
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