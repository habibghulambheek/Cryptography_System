#include <iostream>
#include <string>
#include "VigenereCipher.h"
#include "PlayfairCipher.h"
#include "HillCipher.h"
#include "AtbashCipher.h"
#include "CaesarCipher.h"
#include "User.h"
#include "MonoalphabeticCipher.h"
#include <limits> 
using namespace std;

//Decryption
void createAtbashDecryption()
{
	AtbashCipher* obj = new AtbashCipher;
	string  dec;
	cout << "Enter input to be decrypted:";
	cin >> dec;
	obj->setDecryptedInput(dec);
	obj->decrypt();
	cout << "Result: " << obj->getEncryptedInput() << endl;
	cout << "Result: " << obj->getEncryptedInput() << endl;
	obj->setPassword();
	AtbashCipher::addCipher(obj);
	cout << "Successfully decrypted, Password = " << obj->getPassword() << endl;
}
void createVigenereDecryption()
{
	VigenereCipher* obj = new VigenereCipher;
	string dec, key;

	cout << "Enter input to be decrypted:";
	cin >> dec;
	obj->setDecryptedInput(dec);

	cout << "Enter key:";
	cin >> key;

	obj->setKey(key);

	obj->vigenereDecrypt();
	cout << "Result: " << obj->getEncryptedInput() << endl;
	obj->setPassword();
	VigenereCipher::addCipher(obj);
	cout << "Successfully decrypted, Password = " << obj->getPassword() << endl;
}
void createPlayfairDecryption()
{
	PlayfairCipher* obj = new PlayfairCipher;
	string dec, key;

	cout << "Enter input to be decrypted:";
	cin >> dec;
	obj->setDecryptedInput(dec);

	cout << "Enter key:";
	cin >> key;

	obj->setKey(key);

	obj->decrypt();
	cout << "Result: " << obj->getEncryptedInput() << endl;
	obj->setPassword();
	PlayfairCipher::addCipher(obj);
	cout << "Successfully decrypted, Password = " << obj->getPassword() << endl;
}
void createHillDecryption()
{
	HillCipher* obj = new HillCipher;
	string dec, key;

	cout << "Enter key:";
	cin >> key;
	if (!obj->setKey(key))
	{
		delete obj;
		obj = nullptr;
		return;
	}

	int det = obj->calculateDeterminant();
	// for 26 and det to be coprime their gcd must be 1 and only then inverse of det will exist
	if (gcd(det, 26) != 1)
	{
		cout << "Key matrix not invertible with respect to 26." << endl;
		delete obj;
		obj = nullptr;
		return;
	}

	cout << "Enter input to be decrypted:";
	cin >> dec;
	if (!obj->setDecryptedInput(dec)) {
		delete obj;
		obj = nullptr;
		return;
	}


	obj->decrypt();
	cout << "Result: " << obj->getEncryptedInput() << endl;
	obj->setPassword();
	HillCipher::addCipher(obj);
	cout << "Successfully decrypted, Password = " << obj->getPassword() << endl;
}
void createCaesarDecryption()
{
	CaesarCipher* obj = new CaesarCipher;
	string dec, key;

	cout << "Enter input to be decrypted:";
	cin >> dec;
	obj->setDecryptedInput(dec);

	cout << "Enter key:";
	cin >> key;

	obj->setKey(key);
	if (obj->getKey() != "") {
		obj->decrypt();
		cout << "Result: " << obj->getEncryptedInput() << endl;
		obj->setPassword();
		CaesarCipher::addCipher(obj);
		cout << "Successfully decrypted, Password = " << obj->getPassword() << endl;
	}
	else {
		cout << "Unsuccessful decryption...." << endl;
		delete obj;
		obj = nullptr;
	}
}
void createMonoalphabeticDecryption()
{
	MonoalphabeticCipher* obj = new MonoalphabeticCipher;
	string dec;
	int choice;
	cout << "Enter input to be decrypted:";
	cin >> dec;
	cout << "Generating a key:" << endl;
	obj->generateKey();
	cout << "Key = " << obj->getKey();
	obj->setDecryptedInput(dec);
	obj->setEncryptedInput(obj->decrypt(dec));
	cout << "Result: " << obj->getEncryptedInput() << endl;
	obj->setPassword();
	MonoalphabeticCipher::addCipher(obj);
	cout << "Successfully decrypted, Password = " << obj->getPassword() << endl;
}

//----------------------------------------------------------

int getValidatedInteger() {
	int value;
	while (true) {
		cout << "\nEnter an integer: ";
		cin >> value;

		if (cin.fail()) {

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Please enter a valid integer.\n";
		}
		else {

			return value;
		}
	}
}

void readFiles()
{
	VigenereCipher::readFile("VigenereCipher.txt");
	PlayfairCipher::readFile("PlayfairCipher.txt");
	HillCipher::readFile("HillCipher.txt");
	User::readFile();
	AtbashCipher::readFile("AtbashCipher.txt");
	CaesarCipher::readFile("CaesarCipher.txt");
	MonoalphabeticCipher::readFile("MonoalphabeticCipher.txt");
}
void writeFiles()
{
	VigenereCipher::writeFile("VigenereCipher.txt");
	PlayfairCipher::writeFile("PlayfairCipher.txt");
	HillCipher::writeFile("HillCipher.txt");
	User::writeFile();
	AtbashCipher::writeFile("AtbashCipher.txt");
	CaesarCipher::writeFile("CaesarCipher.txt");
	MonoalphabeticCipher::writeFile("MonoalhabeticCipher.txt");
}
void displayFiles()
{
	VigenereCipher::displayCiphers();
	PlayfairCipher::displayCiphers();
	HillCipher::displayCiphers();

	AtbashCipher::displayCiphers();
	CaesarCipher::displayCiphers();
	MonoalphabeticCipher::displayCiphers();
}

User* login()
{

	User* user;
	string userName, credentials;
	cout << "Enter user name:";
	cin >> userName;
	user = User::searchUser(userName);
	if (user != nullptr) {
		cout << "User found..." << endl;
		cout << "Enter credentials:";
		cin >> credentials;
		if (credentials != user->getCredentials())
		{
			cout << "Incorrect password.\nLogin unsuccessful\n" << endl;
			return nullptr;
		}
		cout << "Login successful!" << endl;
	}
	else
	{
		cout << "Login unsuccessful\n" << endl;
	}
	return user;
}
User* createUser()
{
	int choice;
	UserType user;
	string userName, credentials;
	do {
		cout << "Choose User type:\n1.Encryptor\n2.Decryptor\n3.Reader" << endl;
		choice = getValidatedInteger();
	} while (choice > 3 || choice < 1);
	user = static_cast<UserType>(choice);
	User* existingUser;
	do {
		cout << "Choose a unique user name:";
		cin >> userName;
		existingUser = User::searchUser(userName);
		if (existingUser != nullptr)
		{
			cout << "User name already exist,Please choose another one" << endl;
		}
	} while (existingUser != nullptr);
	cout << "Enter credentials:";
	cin >> credentials;
	cout << "User successfully created." << endl;
	User* _user = new User(userName, credentials, user, nullptr);
	User::addUser(_user);
	return _user;
}
void createAtbashEncryption()
{
	AtbashCipher* obj = new AtbashCipher;
	string enc, dec;
	cout << "Enter input to be encrypted:";
	cin >> enc;
	obj->setEncryptedInput(enc);
	obj->encrypt();
	cout << "Result: " << obj->getDecryptedInput() << endl;
	obj->setPassword();
	AtbashCipher::addCipher(obj);
	cout << "Successfully encrypted, Password = " << obj->getPassword() << endl;
}
void createVigenereEncryption()
{
	VigenereCipher* obj = new VigenereCipher;
	string enc, key;

	cout << "Enter input to be encrypted:";
	cin >> enc;
	obj->setEncryptedInput(enc);

	cout << "Enter key:";
	cin >> key;

	obj->setKey(key);

	obj->vigenereEncrypt();
	cout << "Result: " << obj->getDecryptedInput() << endl;
	obj->setPassword();
	VigenereCipher::addCipher(obj);
	cout << "Successfully encrypted, Password = " << obj->getPassword() << endl;
}
void createPlayfairEncryption()
{
	PlayfairCipher* obj = new PlayfairCipher;
	string enc, key;

	cout << "Enter input to be encrypted:";
	cin >> enc;
	obj->setEncryptedInput(enc);

	cout << "Enter key:";
	cin >> key;

	obj->setKey(key);

	obj->encrypt();
	cout << "Result: " << obj->getDecryptedInput() << endl;
	obj->setPassword();
	PlayfairCipher::addCipher(obj);
	cout << "Successfully encrypted, Password = " << obj->getPassword() << endl;
}
void createHillEncryption()
{
	HillCipher* obj = new HillCipher;
	string enc, key;

	cout << "Enter key:";
	cin >> key;
	if (!obj->setKey(key))
	{

		delete obj;
		obj = nullptr;
		return;
	}

	int det = obj->calculateDeterminant();
	// for 26 and det to be coprime their gcd must be 1 and only then inverse of det will exist
	if (gcd(det, 26) != 1)
	{
		cout << "Key matrix not invertible with respect to 26." << endl;
		delete obj;
		obj = nullptr;
		return;
	}

	cout << "Enter input to be encrypted:";
	cin >> enc;
	if (!obj->setEncryptedInput(enc)) {

		delete obj;
		obj = nullptr;
		return;
	}


	obj->encrypt();
	cout << "Result: " << obj->getDecryptedInput() << endl;
	obj->setPassword();
	HillCipher::addCipher(obj);
	cout << "Successfully encrypted, Password = " << obj->getPassword() << endl;
}
void createCaesarEncryption()
{
	CaesarCipher* obj = new CaesarCipher;
	string enc, key;

	cout << "Enter input to be encrypted:";
	cin >> enc;
	obj->setEncryptedInput(enc);

	cout << "Enter key:";
	cin >> key;

	obj->setKey(key);
	if (obj->getKey() != "") {
		obj->encrypt();
		cout << "Result: " << obj->getDecryptedInput() << endl;
		obj->setPassword();
		CaesarCipher::addCipher(obj);
		cout << "Successfully encrypted, Password = " << obj->getPassword() << endl;
	}
	else {
		cout << "Unsuccessful encryption...." << endl;
		delete obj;
		obj = nullptr;
	}
}
void createMonoalphabeticEncryption()
{
	MonoalphabeticCipher* obj = new MonoalphabeticCipher;
	string enc;
	int choice;
	cout << "Enter input to be encrypted:";
	cin >> enc;
	cout << "Generating a key:" << endl;
	obj->generateKey();
	cout << "Key = " << obj->getKey();
	obj->setEncryptedInput(enc);
	obj->setDecryptedInput(obj->encrypt(enc));
	cout << "Result: " << obj->getDecryptedInput() << endl;
	obj->setPassword();
	MonoalphabeticCipher::addCipher(obj);
	cout << "Successfully encrypted, Password = " << obj->getPassword() << endl;
}

void fetchRecordAtbash(int pasword)
{
	Cipher* obj = AtbashCipher::searchCipher(pasword);
	if (obj == nullptr)
	{
		cout << "Such record don't exist." << endl;
	}
	else
	{
		cout << "Password: " << obj->getPassword() << " Input to be encrypted: " << obj->getEncryptedInput() << " input to be decrypted: " << obj->getDecryptedInput() << endl;
	}
}
void fetchRecordCaesar(int pasword)
{
	Cipher* obj = CaesarCipher::searchCipher(pasword);
	if (obj == nullptr)
	{
		cout << "Such record don't exist." << endl;
	}
	else
	{
		cout << "Password: " << obj->getPassword() << " Input to be encrypted: " << obj->getEncryptedInput() << " input to be decrypted: " << obj->getDecryptedInput() << " Key used: " << obj->getKey() << endl;
	}
}
void fetchRecordHill(int pasword)
{
	Cipher* obj = HillCipher::searchCipher(pasword);
	if (obj == nullptr)
	{
		cout << "Such record don't exist." << endl;
	}
	else
	{
		cout << "Password: " << obj->getPassword() << " Input to be encrypted: " << obj->getEncryptedInput() << " input to be decrypted: " << obj->getDecryptedInput() << " Key used: " << obj->getKey() << endl;
	}
}
void fetchRecordMonoalphabetic(int pasword)
{
	Cipher* obj = MonoalphabeticCipher::searchCipher(pasword);
	if (obj == nullptr)
	{
		cout << "Such record don't exist." << endl;
	}
	else
	{
		cout << "Password: " << obj->getPassword() << " Input to be encrypted: " << obj->getEncryptedInput() << " input to be decrypted: " << obj->getDecryptedInput() << " Key used: " << obj->getKey() << endl;
	}
}
void fetchRecordPlayfair(int pasword)
{
	Cipher* obj = PlayfairCipher::searchCipher(pasword);
	if (obj == nullptr)
	{
		cout << "Such record don't exist." << endl;
	}
	else
	{
		cout << "Password: " << obj->getPassword() << " Input to be encrypted: " << obj->getEncryptedInput() << " input to be decrypted: " << obj->getDecryptedInput() << " Key used: " << obj->getKey() << endl;
	}
}
void fetchRecordVigenere(int pasword)
{
	Cipher* obj = VigenereCipher::searchCipher(pasword);
	if (obj == nullptr)
	{
		cout << "Such record don't exist." << endl;
	}
	else
	{
		cout << "Password: " << obj->getPassword() << " Input to be encrypted: " << obj->getEncryptedInput() << " input to be decrypted: " << obj->getDecryptedInput() << " Key used: " << obj->getKey() << endl;
	}
}
//login or create -> menu for each user with their powers -> function for each power
void menu()
{

	readFiles();
	User* user;
	string enc, dec, key;
	int choice, password;
	bool exit = 0;
	bool roleExit = 0;
	cout << "----------------------------------------- - WELCOME TO CRYPTOGRAPHY SYSTEM - ----------------------------------------" << endl;
	while (!exit) {
		cout << "Choose one.\n1.login into the system\n2.Create account\n3.exit";
		choice = getValidatedInteger();

		switch (choice)
		{
		case 1:
			user = login();
			if (user != nullptr)
			{
				roleExit = 0;
				switch (user->getUser())
				{
				case ENCRYPTOR:
					while (!roleExit) {
						cout << "Choose one.\n1.Encrypt \n2.Fetch Cipher Record\n3.logout" << endl;
						choice = getValidatedInteger();

						switch (choice)
						{
						case 1:
							cout << "Choose one.\n1.Encrypt using Atbash cipher\n2.Encrypt using Caesar cipher\n3.Encrypt using HillCipher cipher\n4.Encrypt using Monoalphabetic cipher\n5.Encrypt using Playfair cipher\n6.Encrypt using Vigenère cipher" << endl;
							choice = getValidatedInteger();
							switch (choice)
							{
							case 1:
								createAtbashEncryption();
								break;
							case 2:
								createCaesarEncryption();
								break;
							case 3:
								createHillEncryption();
								break;
							case 4:
								createMonoalphabeticEncryption();
								break;
							case 5:
								createPlayfairEncryption();
								break;
							case 6:
								createVigenereEncryption();
								break;
							default:
								cout << "Invalid Input" << endl;

							}
							break;
						case 2:
							cout << "Choose one.\n1.Search Atbash cipher\n2.Search Caesar cipher\n3.Search HillCipher cipher\n4.Search Monoalphabetic cipher\n5.Search Playfair cipher\n6.Search Vigenère cipher" << endl;
							choice = getValidatedInteger();
							cout << "Enter password:";
							password = getValidatedInteger();
							switch (choice)
							{
							case 1:
								fetchRecordAtbash(password);
								break;
							case 2:
								fetchRecordCaesar(password);
								break;
							case 3:
								fetchRecordHill(password);
								break;
							case 4:
								fetchRecordMonoalphabetic(password);
								break;
							case 5:
								fetchRecordPlayfair(password);
								break;
							case 6:
								fetchRecordVigenere(password);
								break;
								break;
							default:
								cout << "Invalid Input" << endl;

							}
							break;
						case 3:
							cout << "Logging out..." << endl;
							roleExit = 1;
							break;
						default:
							cout << "Invalid choice" << endl;
						}
					}
					break;
				case DECRYPTOR:
					while (!roleExit) {
						cout << "Choose one.\n1.Decrypt \n2.Fetch Cipher Record\n3.logout" << endl;
						choice = getValidatedInteger();

						switch (choice)
						{
						case 1:
							cout << "Choose one.\n1.Decrypt using Atbash cipher\n2.Decrypt using Caesar cipher\n3.Decrypt using HillCipher cipher\n4.Decrypt using Monoalphabetic cipher\n5.Decrypt using Playfair cipher\n6.Decrypt using Vigenère cipher" << endl;
							choice = getValidatedInteger();
							switch (choice)
							{
							case 1:
								createAtbashDecryption();
								break;
							case 2:
								createCaesarDecryption();
								break;
							case 3:
								createHillDecryption();
								break;
							case 4:
								createMonoalphabeticDecryption();
								break;
							case 5:
								createPlayfairDecryption();
								break;
							case 6:
								createVigenereDecryption();
								break;
							default:
								cout << "Invalid Input" << endl;

							}
							break;
						case 2:
							cout << "Choose one.\n1.Search Atbash cipher\n2.Search Caesar cipher\n3.Search HillCipher cipher\n4.Search Monoalphabetic cipher\n5.Search Playfair cipher\n6.Search Vigenère cipher" << endl;
							choice = getValidatedInteger();
							cout << "Enter password:";
							password = getValidatedInteger();
							switch (choice)
							{
							case 1:
								fetchRecordAtbash(password);
								break;
							case 2:
								fetchRecordCaesar(password);
								break;
							case 3:
								fetchRecordHill(password);
								break;
							case 4:
								fetchRecordMonoalphabetic(password);
								break;
							case 5:
								fetchRecordPlayfair(password);
								break;
							case 6:
								fetchRecordVigenere(password);
								break;
							default:
								cout << "Invalid Input" << endl;

							}
							break;
						case 3:
							cout << "Logging out..." << endl;
							roleExit = 1;
							break;
						default:
							cout << "Invalid choice" << endl;
						}


					}
					break;
				case READER:
					while (!roleExit) {
						cout << "Choose one.\n1.View Complete file \n2.Fetch Cipher Record\n3.logout\n4.View all files" << endl;
						choice = getValidatedInteger();

						switch (choice)
						{
						case 1:
							cout << "Choose one.\n1.View AtbashCipher.txt\n2.View CaesarCipher.txt\n3.View HillCipher.txt\n4.View MonoalphabeticCipher.txt\n5.View PlayfairCipher.txt\n6.View VigenèreCipher.txt" << endl;
							choice = getValidatedInteger();
							switch (choice)
							{
							case 1:
								AtbashCipher::displayCiphers();
								break;
							case 2:
								CaesarCipher::displayCiphers();
								break;
							case 3:
								HillCipher::displayCiphers();
								break;
							case 4:
								MonoalphabeticCipher::displayCiphers();
								break;
							case 5:
								PlayfairCipher::displayCiphers();
								break;
							case 6:
								VigenereCipher::displayCiphers();
								break;
							default:
								cout << "Invalid Input" << endl;

							}
							break;
						case 2:
							cout << "Choose one.\n1.Search Atbash cipher\n2.Search Caesar cipher\n3.Search HillCipher cipher\n4.Search Monoalphabetic cipher\n5.Search Playfair cipher\n6.Search Vigenère cipher" << endl;
							choice = getValidatedInteger();
							cout << "Enter password:";
							password = getValidatedInteger();
							switch (choice)
							{
							case 1:
								fetchRecordAtbash(password);
								break;
							case 2:
								fetchRecordCaesar(password);
								break;
							case 3:
								fetchRecordHill(password);
								break;
							case 4:
								fetchRecordMonoalphabetic(password);
								break;
							case 5:
								fetchRecordPlayfair(password);
								break;
							case 6:
								fetchRecordVigenere(password);
								break;
							default:
								cout << "Invalid Input" << endl;

							}
							break;
						case 3:
							cout << "Logging out..." << endl;
							roleExit = 1;
						case 4:
							displayFiles();
						default:
							cout << "Invalid choice" << endl;
						}
					}
					break;
				default:
					while (!roleExit)
					{

						cout << "Choose one.\n1.Decrypt \n2.Encrypt\n3.Fetch Cipher Record\n4.Delete Cipher Record\n5.View files\n6.View all files\n7.Empty files\n8.logout" << endl;
						choice = getValidatedInteger();


						switch (choice)
						{
						case 7:
							cout << "Choose one.\n1.Empty Atbash file\n2.Empty Caesar cipher file\n3.Empty HillCipher cipher file\n4.Empty Monoalphabetic cipher file\n5.Empty playfair cipher file\n6.Empty vigenère cipher file" << endl;
							choice = getValidatedInteger();

							switch (choice)
							{
							case 1:
								AtbashCipher::deleteCiphers();
								break;
							case 2:
								CaesarCipher::deleteCiphers();
								break;
							case 3:
								HillCipher::deleteCiphers();
								break;
							case 4:
								MonoalphabeticCipher::deleteCiphers();
								break;
							case 5:
								PlayfairCipher::deleteCiphers();
								break;
							case 6:
								VigenereCipher::deleteCiphers();
								break;
							default:
								cout << "Invalid Input" << endl;

							}

							break;

						case 4:
							cout << "Choose one.\n1.Delete Atbash cipher record\n2.Delete Caesar cipher record\n3.Delete HillCipher cipher record\n4.Delete Monoalphabetic cipher record\n5.Delete playfair cipher record\n6.Delete vigenère cipher record" << endl;
							choice = getValidatedInteger();
							cout << "Enter password:";
							password = getValidatedInteger();
							switch (choice)
							{
							case 1:
								AtbashCipher::removeCipher(password);
								break;
							case 2:
								CaesarCipher::removeCipher(password);
								break;
							case 3:
								HillCipher::removeCipher(password);
								break;
							case 4:
								MonoalphabeticCipher::removeCipher(password);
								break;
							case 5:
								PlayfairCipher::removeCipher(password);
								break;
							case 6:
								VigenereCipher::removeCipher(password);
								break;
							default:
								cout << "Invalid Input" << endl;

							}

							break;
						case 2:
							cout << "Choose one.\n1.Encrypt using Atbash cipher\n2.Encrypt using Caesar cipher\n3.Encrypt using HillCipher cipher\n4.Encrypt using Monoalphabetic cipher\n5.Encrypt using Playfair cipher\n6.Encrypt using Vigenère cipher" << endl;
							choice = getValidatedInteger();
							switch (choice)
							{
							case 1:
								createAtbashEncryption();
								break;
							case 2:
								createCaesarEncryption();
								break;
							case 3:
								createHillEncryption();
								break;
							case 4:
								createMonoalphabeticEncryption();
								break;
							case 5:
								createPlayfairEncryption();
								break;
							case 6:
								createVigenereEncryption();
								break;
							default:
								cout << "Invalid Input" << endl;

							}
							break;
						case 1:
							cout << "Choose one.\n1.Decrypt using Atbash cipher\n2.Decrypt using Caesar cipher\n3.Decrypt using HillCipher cipher\n4.Decrypt using Monoalphabetic cipher\n5.Decrypt using Playfair cipher\n6.Decrypt using Vigenère cipher" << endl;
							choice = getValidatedInteger();
							switch (choice)
							{
							case 1:
								createAtbashDecryption();
								break;
							case 2:
								createCaesarDecryption();
								break;
							case 3:
								createHillDecryption();
								break;
							case 4:
								createMonoalphabeticDecryption();
								break;
							case 5:
								createPlayfairDecryption();
								break;
							case 6:
								createVigenereDecryption();
								break;
							default:
								cout << "Invalid Input" << endl;
							}
							break;
						case 5:
							cout << "Choose one.\n1.View AtbashCipher.txt\n2.View CaesarCipher.txt\n3.View HillCipher.txt\n4.View MonoalphabeticCipher.txt\n5.View PlayfairCipher.txt\n6.View VigenèreCipher.txt" << endl;
							choice = getValidatedInteger();
							switch (choice)
							{
							case 1:
								AtbashCipher::displayCiphers();
								break;
							case 2:
								CaesarCipher::displayCiphers();
								break;
							case 3:
								HillCipher::displayCiphers();
								break;
							case 4:
								MonoalphabeticCipher::displayCiphers();
								break;
							case 5:
								PlayfairCipher::displayCiphers();
								break;
							case 6:
								VigenereCipher::displayCiphers();
								break;
							default:
								cout << "Invalid Input" << endl;

							}
							break;
						case 3:
							cout << "Choose one.\n1.Search Atbash cipher\n2.Search Caesar cipher\n3.Search HillCipher cipher\n4.Search Monoalphabetic cipher\n5.Search Playfair cipher\n6.Search Vigenère cipher" << endl;
							choice = getValidatedInteger();
							cout << "Enter password:";
							password = getValidatedInteger();
							switch (choice)
							{
							case 1:
								fetchRecordAtbash(password);
								break;
							case 2:
								fetchRecordCaesar(password);
								break;
							case 3:
								fetchRecordHill(password);
								break;
							case 4:
								fetchRecordMonoalphabetic(password);
								break;
							case 5:
								fetchRecordPlayfair(password);
								break;
							case 6:
								fetchRecordVigenere(password);
								break;
							default:
								cout << "Invalid Input" << endl;

							}
							break;
						case 8:
							cout << "Logging out..." << endl;
							roleExit = 1;
							break;
						case 6:
							displayFiles();
							break;
						default:
							cout << "Invalid choice" << endl;
						}
					}
				}


			}
			break;
		case 2:
			createUser();
			break;
		case 3:
			cout << "Exiting the system" << endl;
			exit = true;
			break;
		default:
			cout << "Invalid choice!" << endl;
		}


		writeFiles();
	}
	cout << "----------------------------------------- - EXITING THE SYSTEM - ----------------------------------------" << endl;
	writeFiles();
}
int main()
{
	menu();
	return 0;
}