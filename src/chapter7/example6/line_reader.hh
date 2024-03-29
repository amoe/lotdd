class LineReader {
public:
    LineReader(const int fd): fd(fd) {  }

    bool getNextLine(const char** line, unsigned int* len);

    void popLine(unsigned int len) const;

private:
    int fd;
    char* buffer;
};

