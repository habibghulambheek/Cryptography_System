#include<cstdlib>
#include<ctime>

#include "CaesarCipher.h"
using namespace std;
CaesarCipher::CaesarCipher() :Cipher() {}


void CaesarCipher::setKey(string _key) {

	key = _key;
	caesarKey = 0; //Intialize the data member
	try {
		caesarKey = stoi(_key); // converting to number
		caesarKey %= 26;  // wrapping the numnber between 25 and -25
		if (caesarKey < 0) caesarKey += 26;	// Adding 26 if negaive
	}
	catch (exception& e) //The number was not an integer
	{
		key = "";
		cout << "CaesarCipher::setKey() Invalid number" << endl;
		return;
	}
}

void CaesarCipher::encrypt() {
	decryptedInput = "";

	for (int i = 0; i < encryptedInput.length(); i++) {
		char currentChar = encryptedInput[i];
		if (currentChar >= 'a' && currentChar <= 'z') {

			currentChar = (currentChar - 'a' + caesarKey) % 26 + 'a';
			decryptedInput += currentChar;

		}
		else if (currentChar >= 'A' && currentChar <= 'Z') {

			currentChar = (currentChar + caesarKey - 'A') % 26 + 'A';
			decryptedInput += currentChar;
		}
		else
		{
			decryptedInput += currentChar;
		}
	}
}
void CaesarCipher::decrypt() {
	encryptedInput = "";

	for (int i = 0; i < decryptedInput.length(); i++) {
		char currentChar = decryptedInput[i];
		if (currentChar >= 'a' && currentChar <= 'z') {

			currentChar = (currentChar - caesarKey - 'a' + 26) % 26 + 'a';
			encryptedInput += currentChar;
		}
		else if (currentChar >= 'A' && currentChar <= 'Z') {
			currentChar = (currentChar - caesarKey - 'A' + 26) % 26 + 'A';
			encryptedInput += currentChar;
		}
		else
		{
			encryptedInput += currentChar;
		}
	}
}

void CaesarCipher::generatekey() {
	srand(time(0));
	this->key = rand() % 25 + 1;     //we want to generate  key

}


int CaesarCipher::noOfRecords = 0;
int CaesarCipher::totalSize = 150;
Cipher** CaesarCipher::ciphers = new Cipher * [CaesarCipher::totalSize];

void CaesarCipher::deleteCiphers()
{
    // Deleting all the pointers in the array and their data
    for (int i = 0; i < noOfRecords; i++)
    {
        delete ciphers[i];
    }
    noOfRecords = 0;
    delete[] ciphers;
    ciphers = nullptr;
}

Cipher* CaesarCipher::searchCipher(int password)
{
    // Iterate through all the array 
    for (int i = 0; i < noOfRecords; ++i)
    {
        // returning a pointer to the Cipher record if the password matches
        if (password == ciphers[i]->getPassword())  // use getter
        {
            return ciphers[i];
        }
    }
    // return nullptr if no such record exist
    return nullptr;
}

void CaesarCipher::setPassword()
{
    //Generating a unique password for the cipher
    int password = 1;
    while (searchCipher(password) != nullptr) {
        ++password;
    }
    this->password = password;
}

void CaesarCipher::resize()
{
    if (noOfRecords == totalSize)
    {
        totalSize += 50;
        Cipher** temp = new Cipher * [totalSize];
        for (int i = 0; i < noOfRecords; ++i)
        {
            // Copying the address
            temp[i] = ciphers[i];
        }
        delete[] ciphers;
        ciphers = temp;
    }
}

void CaesarCipher::addCipher(Cipher* cipher)
{
    // resize if max capacity is reached
    if (noOfRecords == totalSize) resize();
    // if the record already exist it is not added
    if (searchCipher(cipher->getPassword()) == nullptr && cipher->getPassword() != 0)
        ciphers[noOfRecords++] = cipher;
}

void CaesarCipher::readFile(string fileName)
{
    string encInput, decInput, _key;
    int _password;
    ifstream fileInput(fileName);
    if (fileInput.is_open()) {
        while (fileInput >> _password)
        {
            fileInput >> encInput;
            fileInput >> decInput;
            fileInput >> _key;
            // creating a ptr because an object created on heap will not be destroyed even after it goes out of scope of the function
            Cipher* object = new Cipher(_password, encInput, decInput, _key);
            addCipher(object);
        }
    }
    else
    {
        cout << "CaesarCipher::readFile(): File not opened." << endl;
    }
    fileInput.close();
}

void CaesarCipher::writeFile(string fileName)
{
    ofstream fileOutput(fileName);
    if (fileOutput.is_open()) {
        for (int i = 0; i < noOfRecords; ++i)
        {
            fileOutput << ciphers[i]->getPassword() << " "   // use getter
                << ciphers[i]->getEncryptedInput() << " "  // use getter
                << ciphers[i]->getDecryptedInput() << " "  // use getter
                << ciphers[i]->getKey() << endl;  // use getter
        }
    }
    else
    {
        cout << "CaesarCipher::writeFile(): File not opened." << endl;
    }
    fileOutput.close();
}

void CaesarCipher::displayCiphers()
{
    // displaying cipher
    cout << "------------------------------------------------ - DISPLAYING CAESAR CIPHERS - ------------------------------------------------" << endl;
    for (int i = 0; i < noOfRecords; ++i)
    {
        cout << ciphers[i]->getPassword() << " "  // use getter
            << ciphers[i]->getEncryptedInput() << " "  // use getter
            << ciphers[i]->getDecryptedInput() << " "  // use getter
            << ciphers[i]->getKey() << endl;  // use getter
    }
    cout << "----------------------------------------------- - DISPLAYED ALL CAESAR CIPHERS - ----------------------------------------------" << endl;
}

void CaesarCipher::removeCipher(int password)
{
    if (searchCipher(password) != nullptr)
    {
        Cipher* obj;
        for (int i = 0; i < noOfRecords - 1; ++i)
        {
            if (password == ciphers[i]->getPassword())  // use getter
            {
                obj = ciphers[i];
                ciphers[i] = ciphers[i + 1];
                ciphers[i + 1] = obj;
            }
        }
        --noOfRecords;
        cout << "Removed Successfuly" << endl;
    }
    else
    {
        cout << "Cipher not found...." << endl;
    }
}


