#pragma once
#include<iostream>
#include"Cipher.h"
#include<string>
using namespace std;
class CaesarCipher :public Cipher
{
	int caesarKey;

	static int noOfRecords;
	static int totalSize;
	static Cipher** ciphers;

public:
	CaesarCipher();
	void setKey(string);
	void encrypt();

	void decrypt();
	void generatekey();
	
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

