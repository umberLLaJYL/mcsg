#if !defined(_IReader_)
#define _IReader_

#include <string>
#include <fstream>

class IReader {
private:
    std::ifstream configFile;
    
public:
    IReader() {

    }
    virtual ~IReader() {

    }

    virtual void parse(const std::string &) = 0;
};

#endif // _IReader_
