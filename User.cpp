#include "User.h"

// Intializing static variaables
int User::noOfRecords = 0;
int User::totalSize = 100;
User** User::users = new User * [User::totalSize];
string User::fileName = "User.txt";

User::User() {};
User::User(string userName, string credentials, UserType _user, Cipher* cipher) : user(_user), cipher(cipher), userName(userName), credentials(credentials) {}
void User::setUser(UserType _user)
{
	user = _user;
}

void User::setUserName(string username)
{
	userName = username;
}
void User::setCredentials(string cred)
{
	credentials = cred;
}
string User::getUserName()
{
	return userName;
}
string User::getCredentials()
{
	return credentials;
}
void User::setCipher(Cipher* _cipher)
{
	cipher = _cipher;
}
UserType User::getUser()
{
	return user;
}
Cipher* User::getCipher()
{
	return cipher;
}

User::~User()
{
	delete cipher;
}
void User::resize()
{
	if (noOfRecords == totalSize)
	{
		totalSize += 50;
		User** temp = new User * [totalSize];
		for (int i = 0; i < noOfRecords; ++i)
		{
			// Copying the address
			temp[i] = users[i];
		}
		delete[]users;
		users = temp;
	}
}
void User::addUser(User* user)
{
	// resize if max capacity is reached
	if (noOfRecords == totalSize) resize();
	// if the record already exist it is not added
	if (searchUser(user->userName) == nullptr)users[noOfRecords++] = user;
}
User* User::searchUser(string userName)
{
	for (int i = 0; i < noOfRecords; ++i)
	{
		if (userName == users[i]->userName)
		{
			return users[i];
		}
	}
	// return nullptr if no such record exist
	return nullptr;
}
void User::readFile() //not done
{
	string userName, credentials;
	UserType user;
	int _user;
	ifstream fileInput(fileName);
	if (fileInput.is_open()) {
		while (fileInput >> userName)
		{
			fileInput >> credentials;
			fileInput >> _user;
			user = static_cast<UserType> (_user);
			// creating a ptr because an object created on heap will not be destroyed even after it goes out of scope of the function
			User* object = new User(userName, credentials, user, nullptr);
			addUser(object);
		}
	}
	else
	{
		cout << "User::readFile(): File not opened." << endl;
	}
	fileInput.close();
}
void User::writeFile()
{
	ofstream fileOutput(fileName);
	if (fileOutput.is_open()) {
		for (int i = 0; i < noOfRecords; ++i)
		{
			fileOutput << users[i]->userName << " " << users[i]->credentials << " " << users[i]->user << endl;
		}
	}
	else
	{
		cout << "User::writeFile(): File not opened." << endl;
	}
	fileOutput.close();
}
void User::displayUsers()
{
	cout << "------------------------------------------------ - DISPLAYING USERS - ------------------------------------------------" << endl;

	for (int i = 0; i < noOfRecords; ++i)
	{
		cout << users[i]->userName << " " << users[i]->credentials << " " << users[i]->user << endl;
	}
	cout << "------------------------------------------------ - DISPLAYED ALL USERS - ------------------------------------------------" << endl;

}
void User::removeUser(string userName, string credentials)
{
	User* obj = searchUser(userName);
	if (obj != nullptr)
	{

		cout << "User found, Deleting...." << endl;
		if (credentials == obj->credentials) {

			for (int i = 0; i < noOfRecords - 1; ++i)
			{
				if (userName == users[i]->userName)
				{
					obj = users[i];
					users[i] = users[i + 1];
					users[i + 1] = obj;
				}
			}
			--noOfRecords;

		}
		else
		{
			cout << "Incorrect Password..." << endl;
		}
	}
	else
	{
		cout << "User don't exist." << endl;
	}
}

void User::deleteUsers()
{
	// Deleting all the pointers in the array and their data

	for (int i = 0; i < noOfRecords; i++)
	{
		delete users[i];
	}
	noOfRecords = 0;
	delete[]users;
	users = nullptr;
}