#include "MonoalphabeticCipher.h"
int MonoalphabeticCipher::noOfRecords = 0;
int MonoalphabeticCipher::totalSize = 150;
Cipher** MonoalphabeticCipher::ciphers = new Cipher * [MonoalphabeticCipher::totalSize];

void MonoalphabeticCipher::deleteCiphers()
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

Cipher* MonoalphabeticCipher::searchCipher(int password)
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

void MonoalphabeticCipher::setPassword()
{
    //Generating a unique password for the cipher
    int password = 1;
    while (searchCipher(password) != nullptr) {
        ++password;
    }
    this->password = password;
}

void MonoalphabeticCipher::resize()
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

void MonoalphabeticCipher::addCipher(Cipher* cipher)
{
    // resize if max capacity is reached
    if (noOfRecords == totalSize) resize();
    // if the record already exist it is not added
    if (searchCipher(cipher->getPassword()) == nullptr && cipher->getPassword() != 0)
        ciphers[noOfRecords++] = cipher;
}

void MonoalphabeticCipher::readFile(string fileName)
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
        cout << "MonoalphabeticCipher::readFile(): File not opened." << endl;
    }
    fileInput.close();
}

void MonoalphabeticCipher::writeFile(string fileName)
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
        cout << "MonoalphabeticCipher::writeFile(): File not opened." << endl;
    }
    fileOutput.close();
}

void MonoalphabeticCipher::displayCiphers()
{
    // displaying cipher
    cout << "------------------------------------------------ - DISPLAYING MONOALPHABTEIC CIPHERS - ------------------------------------------------" << endl;
    for (int i = 0; i < noOfRecords; ++i)
    {
        cout << ciphers[i]->getPassword() << " "  // use getter
            << ciphers[i]->getEncryptedInput() << " "  // use getter
            << ciphers[i]->getDecryptedInput() << " "  // use getter
            << ciphers[i]->getKey() << endl;  // use getter
    }
    cout << "----------------------------------------------- - DISPLAYED ALL MONOALPHABTEIC CIPHERS - ----------------------------------------------" << endl;
}

void MonoalphabeticCipher::removeCipher(int password)
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

MonoalphabeticCipher::MonoalphabeticCipher() : Cipher()
{}

void MonoalphabeticCipher::setEncryptedInput(string enc)
{
    encryptedInput = validStr(enc);
}
void MonoalphabeticCipher::setDecryptedInput(string dec)
{
    decryptedInput = validStr(dec);
}


string MonoalphabeticCipher::encrypt(string plaintext)
{
  
    plaintext = validStr(plaintext);
    string ciphertext = "";//0
    for (int i = 0; i < plaintext.length(); i++)
    {
       
        // as validStr allows only small case ...so,
        int keyPos = plaintext[i] - 'a';
        ciphertext += key[keyPos];
    }
    decryptedInput = ciphertext;
    return ciphertext;
}

string MonoalphabeticCipher::decrypt(string ciphertext)
{
    ciphertext = validStr(ciphertext);
    string plaintext = "";
    for (int i = 0; i < ciphertext.length(); ++i)
    {
        int pos = -1;
        for (int j = 0; j < key.length(); ++j)
        {
            if (ciphertext[i] == key[j])
            {
                pos = j;
                break;
            }
        }
        // Only applicable if character is found in the key
        if (pos != -1)
        {
            
            plaintext += 'a' + pos;
        }
    }
    encryptedInput = plaintext;
    return plaintext;
}


string MonoalphabeticCipher::validStr(string enc)
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

void MonoalphabeticCipher:: generateKey()
{
    //Generating a random key
    srand(time(0));
    key = "abcdefghijklmnopqrstuvwxyz";
    char temp;
    int index1, index2;
    for(int i =0; i < 26;++i)
    {
        index1 = rand() % 26;
        index2 = rand() % 26;
        temp = key[index1];
        key[index1] = key[index2];
        key[index2] = temp;
    }


}