#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <dlfcn.h>

#include <string.h>
#include <ostream>
#include <iostream>
#include <stdexcept>

#include <memory>

#include "ITestObj.h"
#include "../class/MrcObject.h"

typedef struct dirent DirectoryInfo;

class DirectoryReader {
private:
    DIR *directory;
    DirectoryInfo *dirInfo;
    std::string fileName;
    // rapidjson::Document list;

    virtual bool readDirectoey() {
        return (this->dirInfo = readdir(this->directory)) != NULL;
    }

public:
    DirectoryReader(const std::string &dir) try : directory(NULL), dirInfo(NULL) {
        if((this->directory = opendir(dir.c_str())) == NULL)
            throw std::runtime_error("MRC: invalid directory.");
    } catch (const std::runtime_error error) {
        std::cout << error.what() << std::endl;
    }
    DirectoryReader() : directory(NULL), dirInfo(NULL) {

    }
    virtual ~DirectoryReader() {
        if((this->directory != NULL) && (this->dirInfo != NULL))
            closedir(this->directory);
    }

    virtual bool openDirectory(const std::string &file) {
        if((this->directory == NULL) && (this->dirInfo == NULL))
            if((this->directory = opendir(file.c_str())) == NULL)
                throw std::runtime_error("MRC: can not open directory.");
    }

    virtual bool closeDirectory() {
        this->directory = NULL;
        this->dirInfo = NULL;
        return closedir(this->directory) == 0;
    }

    virtual const std::string &getFileName() noexcept {
        return this->readDirectoey()?
            this->fileName = this->dirInfo->d_name:
            this->fileName = "MrcNullString";
    }

    virtual const std::string &getFileNameWithKey(const std::string &key) {
        while(this->readDirectoey()) {
            if((this->fileName = this->dirInfo->d_name).find(key) != std::string::npos)
                return this->fileName;
        }
        return this->fileName = "MrcNullString";
    }

    virtual const std::string &getFileList() {

    }
};

class SoReader {
private:
    void *_handle;
    std::string errorMsg;

public:
    SoReader(const std::string &soFile, int mode) try {
        if((this->_handle = dlopen(soFile.c_str(), mode)) == NULL)
            std::cout << "dlopen" << std::endl;
    } catch(std::runtime_error error) {
        std::cout << error.what() << std::endl;
    }
    ~SoReader() {

    }

    bool closeSharedObject() {
        return dlclose(this->_handle) == 0;
    }

    void *fetchSharedObject(const std::string &symbol) {
        // std::string s = symbol;
        return dlsym(this->_handle, symbol.c_str());
    }

    const std::string &getError() {
        this->errorMsg = dlerror();
        return this->errorMsg;
    }

    void *getHandle() {
        return this->_handle;
    }
};

int main(int argc, char const *argv[])
{
    std::string fileName;

    MrcObject<DirectoryReader> dirReader = std::make_shared<DirectoryReader>(".");

    // tObj->show("ncsjkbnskbckshbhksdb");

    // soReader.closeSharedObject();

    // void *handle = dlopen("./libobj.so", RTLD_NOW);
    // if(handle == NULL) {
    //     printf("depoen: %s\n", dlerror());
    //     return 1;
    // }

    // ITestObj *tObj = (ITestObj *)dlsym(handle, "testObj");
    // const char *dlmsg = dlerror();
    // if(dlmsg != NULL) {
    //     printf("dlsym: %s\n", dlmsg);
    //     dlclose(handle);
    //     return 1;
    // }

    // while((fileName = dirReader->getFileNameWithKey(".so")) != "MrcNullString") {
        // fileName.resize(fileName.size()-3);
        fileName = dirReader->getFileNameWithKey(".so");
        std::cout << fileName << std::endl;
        MrcObject<SoReader> soReader = std::make_shared<SoReader>(fileName, RTLD_LAZY);
        fileName.resize(fileName.size()-3);
        fileName.replace(0, 3, "");
        ITestObj *tObj = (ITestObj *)soReader->fetchSharedObject(fileName);
        MrcObject<ITestObj> stObj(tObj);
        // MrcObject<ITestObj> tObj = std::make_shared<ITestObj>(std::m)

    // }

    

    stObj->show("fssssss");
    // soReader->closeSharedObject();

    return 0;
}
