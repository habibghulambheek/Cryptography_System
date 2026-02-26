#pragma once
#include "Cipher.h"
class HillCipher : public Cipher
{
	int keyMatrixSize;
	int** keyMatrix;

	static int noOfRecords;
	static int totalSize;
	static Cipher** ciphers;
public:
	HillCipher();
	HillCipher(int password, string enc, string dec,string key);
	bool setKey(string key);
	static string validStr(string str);
	void populateKeyMatrix();
	bool setEncryptedInput(string enc);
	bool setDecryptedInput(string dec);

	int minor(int i, int j);
	int cofactor(int i, int j);
	int** adjoint();
	int calculateDeterminant();
	int* multiply(int**,int*);
	void encrypt();
	void decrypt();
	int** inverse();
	~HillCipher();


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
int gcd(int num1, int num2);
int mod(int X,int M);
void deallocator2DArray(int** arr, int rows);