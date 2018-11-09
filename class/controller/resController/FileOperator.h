#if !defined(_FileOperator_)
#define _FileOperator_

#include <unistd.h>
#include <fcntl.h>

#include <string>

#if !defined(WRLen)
#define WRLen 8
#endif // WRLen

#if !defined(WritePos)
#define WritePos 20
#endif // WritePos

class FileOperator {
private:

protected:
    std::string _directory;

    std::string &_setDirectory(const int idx){
        return this->_directory.replace(WritePos, this->_directory.find_last_of("/")-WritePos, std::to_string(idx));
    }

public:
    FileOperator() {

    }
    ~FileOperator() {

    }
};

#endif // _FileOperator_
