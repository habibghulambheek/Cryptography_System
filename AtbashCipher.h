#pragma once
#include<iostream>
#include"Cipher.h"

using namespace std;
class AtbashCipher :public Cipher
{
	static int noOfRecords;
	static int totalSize;
	static Cipher** ciphers;
public:
	AtbashCipher();
	AtbashCipher(int _password,string encInput,string decInput);
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

