#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <dlfcn.h>

#include <string.h>
#include <ostream>
#include <iostream>
#include <stdexcept>

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

int main(int argc, char const *argv[])
{
    std::string fileName;
    DirectoryReader dirReader;

    dirReader.openDirectory(".");
    
    while((fileName = dirReader.getFileNameWithKey(".so")) != "MrcNullString") {
        fileName.resize(fileName.size()-3);
        std::cout << fileName << std::endl;
    }

    return 0;
}
