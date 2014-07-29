// VigenereDecoder.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"

using namespace std;

char letterToNum(const char letter) {
    return (letter - 'a') % 26 + 1;
}

char difLetterNums(const char lhs, const char rhs) {
    char returnValue = lhs - rhs;
    while (returnValue < 0) {
        returnValue += 26;
    }
    return returnValue;
}

char numToLetter(const char num) {
    return num - 1 + 'a';
}

string simpleKeyDecode(const string message, const string decoder) {
    auto currentCode = message.begin();
    auto currentKey = decoder.begin();

    string decoded = "";

    while (currentCode != message.end()) {
        char letter = tolower(*currentCode);
        if (letter >= 'a' && letter <= 'z') {
            char codeLetter = letterToNum(letter);
            char keyLetter = letterToNum(*currentKey);
            char decodedLetter = numToLetter(difLetterNums(codeLetter, keyLetter));
            if (letter == *currentCode) {
                decoded.push_back(decodedLetter);
            }
            else {
                decoded.push_back(toupper(decodedLetter));
            }
            if (++currentKey == decoder.end()) {
                currentKey = decoder.begin();
            }
        }
        else {
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

