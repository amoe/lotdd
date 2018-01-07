#ifndef SOUNDEX_HH
#define SOUNDEX_HH

#include <iostream>
#include <unordered_map>
#include <string>

using std::string;

class Soundex {
    static const size_t MAX_CODE_LENGTH{4};
    const string NOT_A_DIGIT{"*"};

public:
    std::string encode(const std::string& word) const {
        return zeroPad(upperCaseFront(head(word)) + tail(encodedDigits(word)));
    }

    string upperCaseFront(const string& word) const {
        auto firstLetter = std::toupper(word.front());
        return string(1, firstLetter);
    }

    // We anticipated the general case by making this a function, so I guess now
    // we will just pass a char in.
    std::string encodedDigit(char letter) const {
        const std::unordered_map<char, std::string> encodings = {
            {'b', "1"}, {'f', "1"}, {'p', "1"}, {'v', "1"},

            {'c', "2"}, {'g', "2"}, {'j', "2"}, {'k', "2"}, {'q', "2"},
            {'s', "2"}, {'x', "2"}, {'z', "2"},

            {'d', "3"}, {'t', "3"},
            
            {'l', "4"},

            {'m', "5"}, {'n', "5"},

            {'r', "6"}
        };

        auto it = encodings.find(std::tolower(letter));
        if (it == encodings.end()) {
            return NOT_A_DIGIT;   // not found
        } else {
            return it->second;
        }
    }



private:
    // Return everything except for the start.
    string tail(const string& word) const {
        return word.substr(1);
    }
    
    std::string zeroPad(const std::string& word) const {
        auto zerosNeeded = MAX_CODE_LENGTH - word.length();

        return word + std::string(zerosNeeded, '0');
    }

    std::string head(const std::string& word) const {
        return word.substr(0, 1);
    }

    // equivalent to someStr[-1] in Python, I guess.
    string lastDigit(const string& encoding) const {
        if (encoding.empty()) 
            return NOT_A_DIGIT;

        return string(1, encoding.back());
    }

    void encodeHead(string& sink, const string& word) const {
        sink += encodedDigit(word.front());
    }

    void encodeTail(string& sink, const string& word) const {
        for (auto letter: tail(word)) {
            if (isComplete(sink)) break;

            encodeLetter(sink, letter);

        }
    }

    void encodeLetter(string& sink, char letter) const {
        auto digit = encodedDigit(letter);

        if (digit != NOT_A_DIGIT && digit != lastDigit(sink)) {
            sink += digit;
        }
    }

    std::string encodedDigits(const string& word) const {
        // iterate over word, return the encoded digit.  basically a map
        string encoding;

        // post refactor to SRP, this now determines the overall policy for
        // encoding.  The details are delegated to other functions.

        encodeHead(encoding, word);
        encodeTail(encoding, word);

        return encoding;
    }

    bool isComplete(const string& encodedSoFar) const {
        return encodedSoFar.length() >= MAX_CODE_LENGTH;
    }



};


#endif // SOUNDEX_HH
