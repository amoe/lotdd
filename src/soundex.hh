#ifndef SOUNDEX_HH
#define SOUNDEX_HH

#include <string>

class Soundex {
    static const size_t MAX_CODE_LENGTH{4};

public:
    std::string encode(const std::string& word) const {
        return zeroPad(head(word) + encodedDigits(word));
    }
private:
    std::string zeroPad(const std::string& word) const {
        auto zerosNeeded = MAX_CODE_LENGTH - word.length();
        
        return word + std::string(zerosNeeded, '0');
    }

    std::string head(const std::string& word) const {
        return word.substr(0, 1);
    }

    // We anticipated the general case by making this a function, so I guess now
    // we will just pass a char in.
    std::string encodedDigit(char letter) const {
        if (letter == 'c')
            return "2";
                
        return "1";
    }

    std::string encodedDigits(const std::string& word) const {
        if (word.length() > 1)
            return encodedDigit(word[1]);
        
        return "";
    }
};


#endif // SOUNDEX_HH
