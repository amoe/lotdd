#ifndef SOUNDEX_HH
#define SOUNDEX_HH

#include <unordered_map>
#include <string>

using std::string;

class Soundex {
    static const size_t MAX_CODE_LENGTH{4};

public:
    std::string encode(const std::string& word) const {
        return zeroPad(head(word) + encodedDigits(tail(word)));
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

    std::string encodedDigits(const string& word) const {
        if (word.empty())
            return "";

        return encodedDigit(word.front());
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

        auto it = encodings.find(letter);
        if (it == encodings.end()) {
            return "";   // not found
        } else {
            return it->second;
        }
    }

};


#endif // SOUNDEX_HH
