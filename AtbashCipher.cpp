#include "AtbashCipher.h"

AtbashCipher::AtbashCipher() :Cipher() {}
void AtbashCipher::encrypt() {
	decryptedInput = "";

	for (int i = 0; i < encryptedInput.length(); i++) {
		char temp = encryptedInput[i];
		if ((temp >= 'a') && (temp <= 'z')) {
			temp = 'z' - (temp - 'a');
			decryptedInput += temp;
		}
		else if ((temp >= 'A') && (temp <= 'Z')) {
			temp = 'Z' - (temp - 'A');
			decryptedInput += temp;
		}
		else {
			decryptedInput += temp;
		}
	}
}


void AtbashCipher::decrypt() {

	encryptedInput = "";
	for (int i = 0; i < decryptedInput.length(); i++) {
		char temp = decryptedInput[i];
		if ((temp >= 'a') && (temp <= 'z')) {
			temp = 'z' - (temp - 'a');
			encryptedInput += temp;
		}
		else if ((temp >= 'A') && (temp <= 'Z')) {
			temp = 'Z' - (temp - 'A');
			encryptedInput += temp;
		}
		else {
			encryptedInput += temp;
		}
	}
}

void AtbashCipher::writeFile(string fileName)
{
	ofstream fileOutput(fileName);
	if (fileOutput.is_open()) {
		for (int i = 0; i < noOfRecords; ++i)
		{
			fileOutput << ciphers[i]->getPassword() << " " << ciphers[i]->getEncryptedInput() << " " << ciphers[i]->getDecryptedInput() << " " << endl;
		}
	}
	else
	{
		cout << "Cipher::writeFile(): File not opened." << endl;
	}
	fileOutput.close();
}
void AtbashCipher::readFile(string fileName)
{
	string encInput, decInput;
	int _password;
	ifstream fileInput(fileName);
	if (fileInput.is_open()) {
		while (fileInput >> _password)
		{
			fileInput >> encInput;
			fileInput >> decInput;

			// creating a ptr because an object created on heap will not be destroyed even after it goes out of scope of the function
			Cipher* object = new AtbashCipher(_password, encInput, decInput);
			addCipher(object);
		}
	}
	else
	{
		cout << "Cipher::readFile(): File not opened." << endl;
	}
	fileInput.close();
}


AtbashCipher::AtbashCipher(int _password, string encInput, string decInput)
{
	password = _password;
	encryptedInput = encInput;
	decryptedInput = decInput;
}





int AtbashCipher::noOfRecords = 0;
int AtbashCipher::totalSize = 150;
Cipher** AtbashCipher::ciphers = new Cipher * [AtbashCipher::totalSize];

void AtbashCipher::deleteCiphers()
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

Cipher* AtbashCipher::searchCipher(int password)
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

void AtbashCipher::setPassword()
{
    //Generating a unique password for the cipher
    int password = 1;
    while (searchCipher(password) != nullptr) {
        ++password;
    }
    this->password = password;
}

void AtbashCipher::resize()
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

void AtbashCipher::addCipher(Cipher* cipher)
{
    // resize if max capacity is reached
    if (noOfRecords == totalSize) resize();
    // if the record already exist it is not added
    if (searchCipher(cipher->getPassword()) == nullptr && cipher->getPassword() != 0)
        ciphers[noOfRecords++] = cipher;
}



void AtbashCipher::displayCiphers()
{
    // displaying cipher
    cout << "------------------------------------------------ - DISPLAYING ATBASH CIPHERS - ------------------------------------------------" << endl;
    for (int i = 0; i < noOfRecords; ++i)
    {
        cout << ciphers[i]->getPassword() << " "  // use getter
            << ciphers[i]->getEncryptedInput() << " "  // use getter
            << ciphers[i]->getDecryptedInput() << " "  // use getter
            << ciphers[i]->getKey() << endl;  // use getter
    }
    cout << "----------------------------------------------- - DISPLAYED ALL ATBASH CIPHERS - ----------------------------------------------" << endl;
}

void AtbashCipher::removeCipher(int password)
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

