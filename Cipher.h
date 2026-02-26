#pragma once
#include <iostream>
#include <fstream>
using namespace std;
class Cipher
{
protected:

	string key;
	string encryptedInput;
	string decryptedInput;
	int password;


public:
	Cipher();
	

	Cipher(int password, string enc, string dec, string key);
	int getPassword() const;
	void setEncryptedInput(string input);
	void setDecryptedInput(string input);
	string getEncryptedInput() const;
	string getDecryptedInput() const;
	string getKey() const;
	void setKey(string);


};

