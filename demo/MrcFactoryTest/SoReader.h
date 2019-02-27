#if !defined(_SoReader_)
#define _SoReader_

#include <dlfcn.h>
#include <string>
#include <iostream>

class SoReader {
private:
    void *_handle;
    std::string errorMsg;

public:
    SoReader(const std::string &soFile, int mode) try {
        if((this->_handle = dlopen(soFile.c_str(), mode)) == NULL)
            throw std::runtime_error("MRC: can not open .so.");
    } catch(std::runtime_error error) {
        std::cout << error.what() << std::endl;
    }
    SoReader(const std::string &soFile) try {
        if((this->_handle = dlopen(soFile.c_str(), RTLD_LAZY)) == NULL)
            throw std::runtime_error("MRC: can not open .so.");
    } catch(std::runtime_error error) {
        std::cout << error.what() << std::endl;
    }
    ~SoReader() {

    }

    bool closeSharedObject() {
        return dlclose(this->_handle) == 0;
    }

    void *fetchObject(const std::string &symbol) {
        return dlsym(this->_handle, symbol.c_str());
    }

    const std::string &getError() {
        this->errorMsg = dlerror();
        return this->errorMsg;
    }
};

#endif // _SoReader_
