#include "HillCipher.h"
void deallocator2DArray(int** arr, int rows)
{
	for (int i = 0; i < rows; i++)
	{
		delete[]arr[i];
	}
	delete[]arr;
	arr = nullptr;
}

HillCipher::HillCipher() :keyMatrix(nullptr) {}
HillCipher::HillCipher(int password, string enc, string dec, string key) :Cipher(password, enc, dec, key) {}
int gcd(int num1, int num2)
{ 
	if (num1 == 0) return num2;
	if (num2 == 0) return num1;
	int _min = min(num1, num2);

	// choosing smaller number
	for (int i = _min; i > 1; --i) 
	{
		if (num1 % i == 0 && num2 % i == 0) return i;
	}
	return 1;
}

int mod(int X, int M)
{
	X = X % M;
	if (X < 0) X += M;
	return X;
}

string HillCipher::validStr(string str)
{
	string _str = "";
	bool add;
	for (int i = 0; i < str.length(); ++i)
	{
		add = true;
		// The alphabet must not be in uppercase.
		if (str[i] >= 'A' && str[i] <= 'Z') str[i] += 32;
		// It should be an alphabet
		if (str[i] > 'z' || str[i] < 'a') add = false;
		if (add) _str += str[i];
	}
	return _str;
}


bool HillCipher::setKey(string key)
{
	key = validStr(key);
	int size = key.length();
	if (size == 4 || size == 9) this->key = key;
	else {
		cout << "bool HillCipher:: setKey(string key) Invalid Input" << endl;
		return false;
	}
	keyMatrixSize = sqrt(size);
	populateKeyMatrix();
	return true;

}

void HillCipher::populateKeyMatrix()
{
	keyMatrix = new int* [keyMatrixSize];
	int keyCh = 0;
	for (int i = 0; i < keyMatrixSize; ++i)
	{
		keyMatrix[i] = new int[keyMatrixSize];
	}
	for (int i = 0; i < keyMatrixSize; ++i)
	{
		for (int j = 0; j < keyMatrixSize; ++j)
		{
			keyMatrix[i][j] = key[keyCh++] - 'a';

		}
	}
}
bool HillCipher::setEncryptedInput(string enc)
{
	enc = validStr(enc);
	if (enc.length() % keyMatrixSize == 0) encryptedInput = enc;
	else
	{
		cout << "HillCipher::setEncryptedInput() Invalid Input" << endl;
		return false;
	}
	return true;
}
bool HillCipher::setDecryptedInput(string dec)
{
	dec = validStr(dec);
	if (dec.length() % keyMatrixSize == 0) decryptedInput = dec;
	else
	{
		cout << "HillCipher::setDecryptedInput() Invalid Input" << endl;
		return false;
	}
	return true;
}

int HillCipher::minor(int i, int j)
{
	int arr[2][2];
	int indexI = 0;
	int indexJ = 0;
	for (int a = 0; a < keyMatrixSize; ++a)
	{
		for (int b = 0; b < keyMatrixSize; ++b)
		{
			if (a != i && b != j) {

				arr[indexI][indexJ] = keyMatrix[a][b];
				++indexJ;

				if (indexJ >= 2)
				{
					indexJ = 0;
					++indexI;
				}
			}
		}
	}
	return (arr[0][0] * arr[1][1]) - (arr[0][1] * arr[1][0]);
}

int HillCipher::cofactor(int i, int j)
{
	return pow(-1, i + j) * minor(i, j);
}
int** HillCipher::adjoint()
{
	int** adjKeyMatrix = new int* [keyMatrixSize];
	int temp = 0;
	for (int i = 0; i < keyMatrixSize; ++i)
	{
		adjKeyMatrix[i] = new int[keyMatrixSize];
	}
	if (keyMatrixSize == 3) {

		// storing all the cofactors
		for (int i = 0; i < keyMatrixSize; ++i)
		{
			for (int j = 0; j < keyMatrixSize; ++j)
			{
				adjKeyMatrix[i][j] = mod(cofactor(i, j),26);
			}
		}


		for (int i = 0; i < keyMatrixSize; ++i)
		{
			for (int j = i; j < keyMatrixSize; ++j)
			{
				temp = adjKeyMatrix[i][j];
				adjKeyMatrix[i][j] = adjKeyMatrix[j][i];
				adjKeyMatrix[j][i] = temp;
			}
		}

	}
	else if (keyMatrixSize == 2)
	{
		adjKeyMatrix[0][0] = keyMatrix[1][1];
		adjKeyMatrix[1][1] = keyMatrix[0][0];
		adjKeyMatrix[0][1] = mod(- keyMatrix[0][1], 26);
		adjKeyMatrix[1][0] = mod(- keyMatrix[1][0], 26);
	}
	return adjKeyMatrix;
}

int* HillCipher::multiply(int** keyMatrix, int* polygraph)
{
	if (polygraph == nullptr) return nullptr;
	int* encryptedMat = new int[keyMatrixSize];
	for(int i = 0; i < keyMatrixSize; ++i)
	{
		encryptedMat[i] = 0;
		for (int j = 0; j< keyMatrixSize; ++j)
		{
			encryptedMat[i] += keyMatrix[i][j] * polygraph[j];
		}
		encryptedMat[i] %= 26;
		if (encryptedMat[i]< 0) encryptedMat[i] += 26;
	}
	return encryptedMat;
}
void HillCipher::encrypt()
{   // input to be encrypted   encryptedInput --> two data members
	// input to be decrypted   decryptedInput
	decryptedInput = ""; 
	int* polygraph = new int[keyMatrixSize];
	int* encryptedPolygraph = new int[keyMatrixSize];

	int size = encryptedInput.length();
	int noOfGraphs = size / keyMatrixSize;
	// formula for ch of encrypted Input 
	// i * keyMatrixSize + j;
	for(int i = 0; i < noOfGraphs; ++i)
	{
		for(int j =0; j < keyMatrixSize; ++j)
		{
			polygraph[j] = encryptedInput[i * keyMatrixSize + j] - 'a';
		}
		encryptedPolygraph = multiply(keyMatrix,polygraph);
		for(int k = 0 ; k < keyMatrixSize; ++k)
		{
			decryptedInput += 'a' + encryptedPolygraph[k];
		}
		delete[]encryptedPolygraph;
	}
	delete[]polygraph;
}
int HillCipher::calculateDeterminant()
{
	int determinant= 0;
	if (keyMatrixSize == 3) {
		determinant =  (keyMatrix[0][0] * cofactor(0, 0) +
			keyMatrix[0][1] * cofactor(0, 1) +
			keyMatrix[0][2] * cofactor(0, 2));
	}
	else if(keyMatrixSize == 2)
	{
		determinant = (keyMatrix[0][0] * keyMatrix[1][1] -
			keyMatrix[1][0] * keyMatrix[0][1]);
	}
	determinant %= 26;
	if (determinant < 0) determinant += 26;
	return determinant;
}

HillCipher::~HillCipher()
{
	if (keyMatrix != nullptr)
	{
		for (int i = 0; i < keyMatrixSize; ++i) delete[]keyMatrix[i];
	}
	delete[]keyMatrix;
	keyMatrix = nullptr;
}

int** HillCipher::inverse()
{
	int det = calculateDeterminant();
	int inverseDet;
	// for 26 and det to be coprime their gcd must be 1 and only then inverse of det will exist
	if(gcd(det,26)!=1)
	{
		cout << "HillCipher::inverse() Matrix not invertible with respect to 26." << endl;
		return nullptr;
	}
	for(inverseDet = 1; inverseDet < 26;inverseDet++)
	{
		if ((det * inverseDet) % 26 == 1) break;
	}
	
	int** adjKeyMatrix= adjoint();
    int** inverseKeyMatrix = new int* [keyMatrixSize];

	for (int i = 0; i < keyMatrixSize; ++i)
	{
		inverseKeyMatrix[i] = new int[keyMatrixSize];
	}
	for (int i = 0; i < keyMatrixSize; ++i)
	{
		for (int j = 0; j < keyMatrixSize; ++j)
		{
			inverseKeyMatrix[i][j] = mod(adjKeyMatrix[i][j] * inverseDet,26);
		}
	}
	// deleting adjA
	deallocator2DArray(adjKeyMatrix, keyMatrixSize);
	return inverseKeyMatrix;
}

void HillCipher::decrypt()
{
	int** inverseKeyMatrix = inverse();
	if(inverseKeyMatrix == nullptr)
	{
		cout << "HillCipher::decrypt() Matrix not invertible with respect to 26." << endl;
		return;
	}
	encryptedInput = "";
	int* polygraph = new int[keyMatrixSize];
	int* decryptedPolygraph = new int[keyMatrixSize];

	int size = decryptedInput.length();
	int noOfGraphs = size / keyMatrixSize;
	// formula for ch of encrypted Input 
	// i * keyMatrixSize + j;
	for (int i = 0; i < noOfGraphs; ++i)
	{
		for (int j = 0; j < keyMatrixSize; ++j)
		{
			polygraph[j] = decryptedInput[i * keyMatrixSize + j] - 'a';
		}
		decryptedPolygraph = multiply(inverseKeyMatrix,polygraph);
		for (int k = 0; k < keyMatrixSize; ++k)
		{
			encryptedInput += 'a' + decryptedPolygraph[k];
		}
		delete[]decryptedPolygraph;
	}
	delete[]polygraph;
	deallocator2DArray(inverseKeyMatrix, keyMatrixSize);
}




int HillCipher::noOfRecords = 0;
int HillCipher::totalSize = 150;
Cipher** HillCipher::ciphers = new Cipher * [HillCipher::totalSize];

void HillCipher::deleteCiphers()
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

Cipher* HillCipher::searchCipher(int password)
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

void HillCipher::setPassword()
{
	//Generating a unique password for the cipher
	int password = 1;
	while (searchCipher(password) != nullptr) {
		++password;
	}
	this->password = password;
}

void HillCipher::resize()
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

void HillCipher::addCipher(Cipher* cipher)
{
	// resize if max capacity is reached
	if (noOfRecords == totalSize) resize();
	// if the record already exist it is not added
	if (searchCipher(cipher->getPassword()) == nullptr && cipher->getPassword() != 0)
		ciphers[noOfRecords++] = cipher;
}

void HillCipher::readFile(string fileName)
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
		cout << "HillCipher::readFile(): File not opened." << endl;
	}
	fileInput.close();
}

void HillCipher::writeFile(string fileName)
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
		cout << "HillCipher::writeFile(): File not opened." << endl;
	}
	fileOutput.close();
}

void HillCipher::displayCiphers()
{
	// displaying cipher
	cout << "------------------------------------------------ - DISPLAYING HILL CIPHERS - ------------------------------------------------" << endl;
	for (int i = 0; i < noOfRecords; ++i)
	{
		cout << ciphers[i]->getPassword() << " "  // use getter
			<< ciphers[i]->getEncryptedInput() << " "  // use getter
			<< ciphers[i]->getDecryptedInput() << " "  // use getter
			<< ciphers[i]->getKey() << endl;  // use getter
	}
	cout << "----------------------------------------------- - DISPLAYED ALL HILL CIPHERS - ----------------------------------------------" << endl;
}

void HillCipher::removeCipher(int password)
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

