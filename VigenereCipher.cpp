#include "VigenereCipher.h"

int VigenereCipher::noOfRecords = 0;
int VigenereCipher::totalSize = 150;
Cipher** VigenereCipher::ciphers = new Cipher * [VigenereCipher::totalSize];

void VigenereCipher::deleteCiphers()
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

Cipher* VigenereCipher::searchCipher(int password)
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

void VigenereCipher::setPassword()
{
    //Generating a unique password for the cipher
    int password = 1;
    while (searchCipher(password) != nullptr) {
        ++password;
    }
    this->password = password;
}

void VigenereCipher::resize()
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

void VigenereCipher::addCipher(Cipher* cipher)
{
    // resize if max capacity is reached
    if (noOfRecords == totalSize) resize();
    // if the record already exist it is not added
    if (searchCipher(cipher->getPassword()) == nullptr && cipher->getPassword() != 0)
        ciphers[noOfRecords++] = cipher;
}

void VigenereCipher::readFile(string fileName)
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
        cout << "VigenereCipher::readFile(): File not opened." << endl;
    }
    fileInput.close();
}

void VigenereCipher::writeFile(string fileName)
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
        cout << "VigenereCipher::writeFile(): File not opened." << endl;
    }
    fileOutput.close();
}

void VigenereCipher::displayCiphers()
{
    // displaying cipher
    cout << "------------------------------------------------ - DISPLAYING VIGENERE CIPHERS - ------------------------------------------------" << endl;
    for (int i = 0; i < noOfRecords; ++i)
    {
        cout << ciphers[i]->getPassword() << " "  // use getter
            << ciphers[i]->getEncryptedInput() << " "  // use getter
            << ciphers[i]->getDecryptedInput() << " "  // use getter
            << ciphers[i]->getKey() << endl;  // use getter
    }
    cout << "----------------------------------------------- - DISPLAYED ALL VIGENERE CIPHERS - ----------------------------------------------" << endl;
}

void VigenereCipher::removeCipher(int password)
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


// DEFAULT CONSTRUCTOR
VigenereCipher::VigenereCipher(){}
void VigenereCipher::setKey(string key)
{
	this->key = validStr(key);
}

string VigenereCipher::vigenereEncrypt()
{
	string text = "";
	int keyIndex = 0;
	int keyAdd = 0;
	for (int i = 0; i < encryptedInput.length(); i++)
	{
		char temp;
		if (isSmall(encryptedInput[i]))
		{
			keyAdd = 0;
			temp = 'a';
		}
		else if (isBIG(encryptedInput[i]))
		{
	
			cout << encryptedInput[i] << endl;
			keyAdd = 32;
			temp = 'A';
		}
		if (isABC(encryptedInput[i]))
		{
			char keyChar = key[keyIndex % key.length()] - keyAdd;
		//	cout <<"kc = " << keyChar << endl;
			keyIndex++;
			text += (encryptedInput[i] - temp + (keyChar - temp)) % 26 + temp;
		}
		else
		{
			text += encryptedInput[i];

		}
	}
	decryptedInput = text;
	return text;
}

string VigenereCipher::vigenereDecrypt() {
	string text = "";
	int keyIndex = 0;
	int keyAdd = 0;
	for (int i = 0; i < decryptedInput.length(); i++)
	{
		char temp;
		if (isSmall(decryptedInput[i]))
		{
			keyAdd = 0;
			temp = 'a';
		}
		else if (isBIG(decryptedInput[i]))
		{
			keyAdd = 32;
			temp = 'A';
		}
		if (isABC(decryptedInput[i]))
		{
			char keyChar = key[keyIndex % key.length()] - keyAdd;
			keyIndex++;
			text += (decryptedInput[i] - temp - (keyChar - temp) + 26) % 26 + temp;
		}
		else
		{
			text += decryptedInput[i];
		}
	}
	encryptedInput = text;
	return text;
}

string VigenereCipher::validStr(string enc)
{
	string _enc = "";
	bool add;
	for (int i = 0; i < enc.length(); ++i)
	{
		add = true;
		// The alphabet must not be in uppercase.
		if (enc[i] >= 'A' && enc[i] <= 'Z') enc[i] += 32;
		// It should be an alphabet
		if (enc[i] > 'z' || enc[i] < 'a') add = false;
		if (add) _enc += enc[i];
	}
	return _enc;
}