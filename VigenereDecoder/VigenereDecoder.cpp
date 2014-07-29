// VigenereDecoder.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"

using namespace std;

const int ALPHABET_SIZE = 26;

char letterToNum(const char letter) {
    // converts a letter to its numeric value in the alphabet
    return (letter - 'a') % ALPHABET_SIZE + 1;          // + 1 to stay consistent with codes where A == 1 is important
}

char numToLetter(const char num) {
    // converts number value into the corresponding letter in the alphabet
    return ((num - 1 + ALPHABET_SIZE) % ALPHABET_SIZE) + 'a';
}

char difLetterNums(const char lhs, const char rhs) {
    // substracts a numeric value representing a letter from another
    char returnValue = lhs - rhs;
    while (returnValue < 0) {
        returnValue += ALPHABET_SIZE;
    }
    return returnValue;
}

string simpleKeyDecode(const string message, const string key) {
    // decodes a crypted message by "substracting" the key from the coded message
    // if the coded message is longer than the key, the function cycles back at the start of the key
    // WARNING: the function doesn't handle non-lowercase letters in the key
    auto currentCode = message.begin();
    auto currentKey = key.begin();

    string decoded = "";

    while (currentCode != message.end()) {
        char letter = tolower(*currentCode); // only handling lowercase letter

        // skips character that are not letters
        if (letter >= 'a' && letter <= 'z') {
            char codeLetter = letterToNum(letter);
            char keyLetter = letterToNum(*currentKey);
            char decodedLetter = numToLetter(difLetterNums(codeLetter, keyLetter));

            // check if we need to restore the original case of the letter
            if (letter == *currentCode) {
                decoded.push_back(decodedLetter);
            }
            else {
                decoded.push_back(toupper(decodedLetter));
            }

            // check if we reached the end of the key, cycles back to the start if needed
            if (++currentKey == key.end()) {
                currentKey = key.begin();
            }
        }
        else {
            // in case of any other character, preserve it as is
            decoded.push_back(*currentCode);
        }
        ++currentCode;
    }
    return decoded;
}

int _tmain(int argc, _TCHAR* argv[])
{
    //const string newMessage = "ewamgbdpmqpiipanlznwuvptzzpphishomseqkbwbdnquteubttsjcmlpnajqmfjqpmgquhpmf";
    const string newMessage = "Ewa mgb dpm? Qpii pa nlz nwuv Ptzzp’p “hishoms eqkbwbd nqute?” U’b ttsjcml pnajq mfj…qpmgq uh pmf?";
    cout << simpleKeyDecode(newMessage, "hollowearth") << endl;

    cin.get();
    return 0;
}

