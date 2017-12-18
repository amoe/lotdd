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

    std::string encodedDigit() const {
        return "1";
    }

    std::string encodedDigits(const std::string& word) const {
        if (word.length() > 1)
            return encodedDigit();
        
        return "";
    }
};


#endif // SOUNDEX_HH
