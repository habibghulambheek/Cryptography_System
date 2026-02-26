#pragma once
#include "Cipher.h"
#include<string>
enum UserType
{
	ADMIN = 0, ENCRYPTOR, DECRYPTOR, READER
};
class User
{
	string userName, credentials;
	UserType user;
	Cipher* cipher;
	// static variables
	static int noOfRecords;
	static int totalSize;
	static User** users;
	static string fileName;
public:
	User();
	User(string , string,UserType, Cipher*);
	void setUser(UserType);
	void setUserName(string);
	void setCredentials(string);
	string getUserName();
	string getCredentials();
	void setCipher(Cipher*);
	UserType getUser();
	Cipher* getCipher();
	static void readFile();
	static void writeFile();
	static User* searchUser(string UserName);
	static void addUser(User* user);
	static void resize();
	static void displayUsers();
	static void removeUser(string UserName, string credentials);
	static void deleteUsers();
	~User();

};

