#ifndef BOOK_HH
#define BOOK_HH

#include <string>

class Book {
public:
    Book(
        const std::string& title,
        const std::string& author,
        const unsigned short year,
        const std::string& classification,
        unsigned short type = Book::TYPE_BOOK
    ): title(title), author(author), year(year), classification(classification),
       type(type) { }

    
    static const int BOOK_CHECKOUT_PERIOD{21};
    static const int MOVIE_CHECKOUT_PERIOD{7};

    static const short BOOK_DAILY_FINE{10};

    enum BookType { TYPE_BOOK, TYPE_MOVIE };

    unsigned short getType() const {
        return type;
    }

private:
    std::string title;
    std::string author;
    unsigned short year;
    std::string classification;
    unsigned short type;
};


#endif /* BOOK_HH */
