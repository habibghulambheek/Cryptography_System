# Classical Cryptography System

A modular encryption and decryption system built in **C++** implementing 6 classical ciphers with a **role-based user management system** and **file persistence**. Built around an abstract base class using core OOP principles — each cipher is independently encapsulated, polymorphic, and fully testable.

---

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Ciphers Implemented](#ciphers-implemented)
- [Project Structure](#project-structure)
- [OOP Design](#oop-design)
- [User Roles](#user-roles)
- [How It Works](#how-it-works)
- [How to Run](#how-to-run)
- [Tech Stack](#tech-stack)
- [Team](#team)

---

## Overview

This project was built to demonstrate how classical cryptographic algorithms can be cleanly implemented using OOP design patterns. All 6 ciphers inherit from a shared abstract base class `Cipher`, which defines the common interface and shared data members. The system also includes a `User` management layer with 4 distinct roles, credential-based authentication, and file I/O for persisting cipher records and user data between sessions.

---

## Features

- 6 classical ciphers with full encrypt and decrypt support
- Role-based user system (Admin, Encryptor, Decryptor, Reader)
- File persistence — cipher records and user data saved and loaded automatically
- Password-based cipher record lookup and management
- Dynamic array with auto-resize (initial capacity 150, grows by 50)
- Random key generation for Caesar and Monoalphabetic ciphers
- Full matrix math for Hill cipher including modular inverse and determinant calculation

---

## Ciphers Implemented

### 1. Caesar Cipher
Shifts each letter by a fixed integer key. Supports positive and negative shifts, wraps using modulo 26, and preserves letter case. Includes a `generateKey()` method that picks a random shift between 1–25.

```
Key:    7
Input:  zohaib
Output: gvohpi
```

### 2. Atbash Cipher
A keyless substitution cipher that mirrors the alphabet — `a` maps to `z`, `b` to `y`, and so on. Encryption and decryption are identical operations since the mapping is its own inverse.

```
Input:  Hello
Output: Svool
```

### 3. Monoalphabetic Cipher
Each letter is mapped to a fixed character in a custom 26-character substitution key. Includes `generateKey()` which creates a random permutation of the alphabet using a Fisher-Yates shuffle. Only operates on lowercase letters.

```
Key:    qazwsxedcrfvtgbyhnujmikolp
Input:  hello
Output: xsvvy
```

### 4. Playfair Cipher
A digraph substitution cipher using a 5×5 key matrix. Input is automatically prepared — `j` is converted to `i`, repeated letters in a digraph are separated with a bogus character (`x` or `z`), and odd-length input is padded. Supports same-row, same-column, and rectangle substitution rules.

```
Key Matrix built from keyword (duplicates and j removed, remaining alphabet fills rest)
Input pairs are encrypted based on their positions in the 5x5 matrix
```

### 5. Vigenère Cipher
A polyalphabetic cipher that uses a repeating keyword to shift each letter. Preserves both uppercase and lowercase. The key cycles across all alphabetic characters while non-alphabetic characters pass through unchanged.

```
Key:    key
Input:  AdanMasih
Output: TwtgFtlba
```

### 6. Hill Cipher
A linear-algebra-based cipher that encrypts letter blocks using matrix multiplication modulo 26. Supports **2×2** and **3×3** key matrices. Decryption computes the modular inverse of the key matrix — the system validates that the determinant is coprime with 26 before attempting decryption.

```
Key matrix size: 2x2 (key length = 4) or 3x3 (key length = 9)
Input length must be a multiple of the matrix size
```

---

## Project Structure

```
Cryptography_System/
│
├── Cipher.h / Cipher.cpp                  # Base class — shared data & interface
│
├── CaesarCipher.h / CaesarCipher.cpp      # Shift-based substitution
├── AtbashCipher.h / AtbashCipher.cpp      # Mirror substitution (keyless)
├── MonoalphabeticCipher.h / .cpp          # Fixed 26-char substitution key
├── PlayfairCipher.h / PlayfairCipher.cpp  # 5x5 matrix digraph cipher
├── VigenereCipher.h / VigenereCipher.cpp  # Repeating keyword cipher
├── HillCipher.h / HillCipher.cpp          # Matrix multiplication cipher
│
├── User.h / User.cpp                      # User management & authentication
├── Source.cpp                             # Main entry point & menu driver
│
├── Cipher.txt                             # Persisted Caesar cipher records
├── HillCipher.txt                         # Persisted Hill cipher records
├── VigenereCipher.txt                     # Persisted Vigenère cipher records
├── User.txt                               # Persisted user records
│
└── CryptographySystem.vcxproj             # Visual Studio project file
```

---

## OOP Design

All 6 ciphers extend a common base class:

```
Cipher  (Base Class)
│   Protected: key, encryptedInput, decryptedInput, password
│   Public:    getters/setters, parameterized constructor for file loading
│
├── CaesarCipher         (+ caesarKey int, generateKey())
├── AtbashCipher         (no extra key — cipher is self-inverse)
├── MonoalphabeticCipher (+ generateKey() with Fisher-Yates shuffle)
├── PlayfairCipher       (+ char keyMatrix[5][5], digraph prep logic)
├── VigenereCipher       (+ isABC / isSmall / isBIG helpers)
└── HillCipher           (+ int** keyMatrix, inverse(), determinant())
```

### Design Principles Applied

- **Encapsulation** — Each cipher's key parsing, input validation, and encryption logic are fully self-contained within its own class
- **Inheritance** — All ciphers inherit shared fields (`key`, `encryptedInput`, `decryptedInput`, `password`) and the file-loading constructor from `Cipher`
- **Polymorphism** — The system stores `Cipher*` pointers, allowing all cipher types to be managed through a uniform interface
- **Static record management** — Each cipher class independently manages its own static dynamic array of `Cipher*` records with `addCipher()`, `removeCipher()`, `searchCipher()`, and `resize()`

---

## User Roles

The system has a 4-tier role system defined as an enum:

| Role | Value | Description |
|---|---|---|
| `ADMIN` | 0 | Full access — manage users and all cipher operations |
| `ENCRYPTOR` | 1 | Can encrypt messages and save records |
| `DECRYPTOR` | 2 | Can decrypt stored cipher records |
| `READER` | 3 | Read-only access to stored cipher records |

Users are stored with a username, credentials (password), and assigned role. The `User` class handles its own file persistence via `User.txt` and supports `addUser()`, `removeUser()`, `searchUser()`, and `displayUsers()`.

---

## How It Works

### Cipher Record Lifecycle
1. User provides input and a key for their chosen cipher
2. System auto-generates a unique integer password for the record
3. Cipher encrypts/decrypts and stores both `encryptedInput` and `decryptedInput`
4. Record is added to the static cipher array and written to file via `writeFile()`
5. On next run, records are reloaded from file using `readFile()`

### Key Validation Per Cipher
| Cipher | Validation |
|---|---|
| Caesar | `stoi()` converts key, wrapped to `[0–25]`, negatives adjusted by `+26` |
| Atbash | No key required |
| Monoalphabetic | `validStr()` strips non-alphabetics; key must be 26 chars |
| Playfair | Duplicates and `j` removed from key; 5×5 matrix filled with remaining alphabet |
| Vigenère | Key lowercased and stripped of non-alphabetics via `validStr()` |
| Hill | Key must be exactly 4 or 9 chars; `gcd(det, 26) == 1` required for decryption |

---

## How to Run

### Prerequisites
- C++ compiler supporting C++11 or later (GCC / MSVC / Clang)
- Visual Studio (optional — `.vcxproj` included)

### Compile with g++

```bash
g++ -o Cryptography_System Source.cpp Cipher.cpp \
    CaesarCipher.cpp AtbashCipher.cpp MonoalphabeticCipher.cpp \
    PlayfairCipher.cpp VigenereCipher.cpp HillCipher.cpp User.cpp \
    -std=c++11 -lm
```

### Run

```bash
./Cryptography_System
```

### Visual Studio
Open `CryptographySystem.vcxproj` and press **F5** to build and run.

> ⚠️ **Important:** The `.txt` files (`Cipher.txt`, `HillCipher.txt`, `VigenereCipher.txt`, `User.txt`) must be in the **same directory as the executable** for file persistence to work correctly.

---

## Tech Stack

- **Language:** C++
- **Standard:** C++11
- **Paradigm:** Object-Oriented Programming (OOP)
- **IDE:** Visual Studio
- **Data Storage:** Plain text file I/O via `fstream`

---

## Team

Developed as an Object-Oriented Programming course project.

| Name | Student ID |
|---|---|
| Habib Ghulam Bheek | BITF23M020 |
| Zohaib Haider      | BITF23M017 |
| Ali Raza           | BITF23M039 |
