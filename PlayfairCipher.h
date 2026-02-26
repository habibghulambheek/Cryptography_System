#pragma once
#include "Cipher.h"
class PlayfairCipher : public Cipher
{
	static int noOfRecords;
	static int totalSize;
	static Cipher** ciphers;
	char keyMatrix[5][5];
	void setKeyMatrix();
	bool isValid(char ch);
	int* getIndex(char ch);
	static string validStr(string);
public:
	PlayfairCipher(int password, string enc, string dec, string key);
	PlayfairCipher();
	void setKey(string _key);
	static void setFileName();
	void setEncryptedInput(string enc);
	void encrypt();
	void decrypt();
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

