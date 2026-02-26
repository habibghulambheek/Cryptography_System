#include "Cipher.h"
using namespace std;

// Default constructor
Cipher::Cipher() : password(0), key(""), encryptedInput(""), decryptedInput("") {};
void Cipher::setKey(string _key)
{
	key = _key;
}
int Cipher::getPassword() const { return password; }

void Cipher::setEncryptedInput(string input)
{
	encryptedInput = input;
}
void Cipher::setDecryptedInput(string input)
{
	decryptedInput = input;
}

string Cipher::getDecryptedInput() const
{
	return decryptedInput;
}

string Cipher::getEncryptedInput() const
{
	return encryptedInput;
}



string Cipher::getKey() const
{
	return key;
}



// A constructor created for readFile()
Cipher::Cipher(int password, string enc, string dec, string key)
{
	this->key = key;
	setEncryptedInput(enc);
	setDecryptedInput(dec);
	this->password = password;
}
