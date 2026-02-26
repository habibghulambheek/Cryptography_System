#include "PlayfairCipher.h"
void PlayfairCipher::setKey(string _key)
{
	key = "";
	bool add;


	for (int i = 0; i < _key.length(); i++)
	{

		add = true;
		if (_key[i] == 'j') add = false; // the key can't have j
		if (_key[i] >= 'A' && _key[i] <= 'Z') _key[i] += 32; //  THE KEY WILL ONLY HAVE SMALL ALPHABETS
		if (_key[i] > 'z' || _key[i] < 'a') add = false; // THE KEY WILL NOT HAVE CHARACTER OTHER THAN SMALL ALPHABETS
		else {
			for (int j = i - 1; j >= 0; --j)
			{
				if (_key[i] == _key[j])
				{
					add = false;
					break;
				}
			}
		}
	//	cout << _key[i] << endl;
		if (add) key += _key[i];
	}
//	cout << "KEY" << key;
	// Setting the keyMatrix
	setKeyMatrix();
}

PlayfairCipher::PlayfairCipher(int password, string enc, string dec, string key) :Cipher(password, enc, dec, key)
{}

int PlayfairCipher::noOfRecords = 0;
int PlayfairCipher::totalSize = 150;
Cipher** PlayfairCipher::ciphers = new Cipher * [PlayfairCipher::totalSize];

void PlayfairCipher::deleteCiphers()
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

Cipher* PlayfairCipher::searchCipher(int password)
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

void PlayfairCipher::setPassword()
{
    //Generating a unique password for the cipher
    int password = 1;
    while (searchCipher(password) != nullptr) {
        ++password;
    }
    this->password = password;
}

void PlayfairCipher::resize()
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

void PlayfairCipher::addCipher(Cipher* cipher)
{
    // resize if max capacity is reached
    if (noOfRecords == totalSize) resize();
    // if the record already exist it is not added
    if (searchCipher(cipher->getPassword()) == nullptr && cipher->getPassword() != 0)
        ciphers[noOfRecords++] = cipher;
}

void PlayfairCipher::readFile(string fileName)
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
        cout << "PlayfairCipher::readFile(): File not opened." << endl;
    }
    fileInput.close();
}

void PlayfairCipher::writeFile(string fileName)
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
        cout << "PlayfairCipher::writeFile(): File not opened." << endl;
    }
    fileOutput.close();
}

void PlayfairCipher::displayCiphers()
{
    // displaying cipher
    cout << "------------------------------------------------ - DISPLAYING PLAYFAIR CIPHERS - ------------------------------------------------" << endl;
    for (int i = 0; i < noOfRecords; ++i)
    {
        cout << ciphers[i]->getPassword() << " "  // use getter
            << ciphers[i]->getEncryptedInput() << " "  // use getter
            << ciphers[i]->getDecryptedInput() << " "  // use getter
            << ciphers[i]->getKey() << endl;  // use getter
    }
    cout << "----------------------------------------------- - DISPLAYED ALL PLAYFAIR CIPHERS - ----------------------------------------------" << endl;
}

void PlayfairCipher::removeCipher(int password)
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


PlayfairCipher::PlayfairCipher(){}

bool PlayfairCipher::isValid(char ch)
{
	// KeyMatrix should not have j.
	if (ch == 'j') return false;

	for (int i = 0; i < key.length(); ++i)
	{
		// KeyMatrix should not contain duplicate alphabets.
		if (ch == key[i]) return false;
	}
	// Both conditions are satisfied
	return  true;
}

void PlayfairCipher::setKeyMatrix()
{
	int keyChar = key.length();
	char ch = 'a'; // starting with 'a'
	int chNum = 0;
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; j++)
		{

			if (chNum < keyChar) keyMatrix[i][j] = key[chNum];
			else
			{
				while (!(isValid(ch)) && ch <= 'z') ++ch;
				keyMatrix[i][j] = ch++;
			}
			// printing for debugging
		//	cout << keyMatrix[i][j] << " ";
			++chNum;
		}
		//cout << endl;
	}
}
string PlayfairCipher::validStr(string enc)
{
	string _enc = "";
	bool add;
	for (int i = 0; i < enc.length(); ++i)
	{
		add = true;
		// The alphabet must not be in uppercase.
		if (enc[i] >= 'A' && enc[i] <= 'Z') enc[i] += 32;
		// converting j to i.
		if (enc[i] == 'j') enc[i] = 'i';
		// It should be an alphabet
		if (enc[i] > 'z' || enc[i] < 'a') add = false;
		if (add) _enc += enc[i];
	}
	return _enc;
}

int* PlayfairCipher::getIndex(char ch)
{
	int* index =  new int[2];
	for(int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{

			if(ch == keyMatrix[i][j]) 
			{
				index[0] = i;
				index[1] = j;
				return index;
			}
		}
	}
	return nullptr;
}
void PlayfairCipher::setEncryptedInput(string enc)
{
	enc = validStr(enc);
	int size = enc.length();
	string digraph = "";
	char bogusCh = 'x';
	encryptedInput = "";
	//applep

	for (int i = 0; i < size; i++)
	{
		bogusCh = 'x'; // Bogus should be x at the start of each cycle
		digraph = "";
		digraph += enc[i];// Addig firt ch
		// That means there must be odd number of characters
		if (i == size - 1)  // so that the i won't go out of bound
		{
			if (enc[i] == bogusCh) bogusCh = 'z';
			digraph += bogusCh;
		}
		else {
			++i; 
			if (enc[i] == enc[i - 1])
			{
				if (enc[i - 1] == bogusCh) bogusCh = 'z';
				digraph += bogusCh;
				--i;
			}
			else digraph += enc[i];
		}

		encryptedInput += digraph;
	}
}

void PlayfairCipher::encrypt()
{
	int size = encryptedInput.length();
	decryptedInput = "";
	int* index1;
	int* index2;
	string digraph = "";
	int indexI,indexJ;
	//alix 
	//0,2, 
	for(int i = 0; i <size; i+=2)
	{
		digraph = "";
	//	cout << encryptedInput[i] << encryptedInput[i+1];
		digraph += encryptedInput[i];
		digraph+=encryptedInput[i + 1];
		
		cout << digraph << endl;
		index1 = getIndex(digraph[0]);
		index2 = getIndex(digraph[1]);
//		cout << "hello" << endl;

		if (index1[0] == index2[0]) // same row
		{
			indexI = index1[0];
			indexJ = (index1[1] + 1) % 5;
			decryptedInput += keyMatrix[indexI][indexJ];
			indexJ = (index2[1] + 1) % 5;
			decryptedInput += keyMatrix[indexI][indexJ];
		}
		else if (index1[1] == index2[1]) // same column
		{
			indexI = (index1[0] + 1) % 5;
			indexJ = index2[1];
			decryptedInput += keyMatrix[indexI][indexJ];
			indexI = (index2[0] + 1) % 5;
			decryptedInput += keyMatrix[indexI][indexJ];
		}
		else
		{   
			indexI = index1[0]; // will take the row of first and column of second
			indexJ = index2[1];
			decryptedInput += keyMatrix[indexI][indexJ];
			indexI = index2[0];// will take the row of second and column of first
			indexJ = index1[1];
			decryptedInput += keyMatrix[indexI][indexJ];

		}
//		cout << "Zinga" << endl;
		delete[]index1;
		index1 = nullptr;
		delete[]index2;
		index2 = nullptr;
		//cout << "binga" << endl;
	}
}

void PlayfairCipher::decrypt()
{
	int size = decryptedInput.length();
	encryptedInput = "";
	int* index1;
	int* index2;
	string digraph = "";
	int indexI, indexJ;
	for (int i = 0; i < size; i += 2)
	{
		digraph = "";
		digraph += decryptedInput[i];
		digraph += decryptedInput[i + 1];

		index1 = getIndex(digraph[0]);
		index2 = getIndex(digraph[1]);

		if (index1[0] == index2[0]) // same row
		{
			indexI = index1[0];
			indexJ = (index1[1] - 1) % 5;
			if (indexJ < 0) indexJ += 5;
			encryptedInput += keyMatrix[indexI][indexJ];
			indexJ = (index2[1] - 1) % 5;
			if (indexJ < 0) indexJ += 5;
			encryptedInput += keyMatrix[indexI][indexJ];
		}
		else if (index1[1] == index2[1]) // same column
		{
			indexI = (index1[0] - 1) % 5;
			if (indexI < 0) indexI += 5;
			indexJ = index2[1];
			encryptedInput += keyMatrix[indexI][indexJ];
			indexI = (index2[0] - 1) % 5;
			if (indexI < 0) indexI += 5;
			encryptedInput += keyMatrix[indexI][indexJ];
		}
		else
		{
			indexI = index1[0]; // will take the row of first and column of second
			indexJ = index2[1];
			encryptedInput += keyMatrix[indexI][indexJ];
			indexI = index2[0];// will take the row of second and column of first
			indexJ = index1[1];
			encryptedInput += keyMatrix[indexI][indexJ];

		}
		delete[]index1;
		index1 = nullptr;
		delete[]index2;
		index2 = nullptr;
	}
}