#if !defined(_DirectoryReader_)
#define _DirectoryReader_

#include <dirent.h>

#include <string>
#include <iostream>

#include "../../Library/json/rapidjson/document.h"

typedef struct dirent DirectoryInfo;

class DirectoryReader {
private:
    DIR *directory;
    DirectoryInfo *dirInfo;
    std::string fileName;
    rapidjson::Document list;

public:
    DirectoryReader(const std::string &dir) try : directory(NULL), dirInfo(NULL) {
        if((directory = opendir(dir.c_str())) == NULL)
            throw std::runtime_error("MRC: invalid directory.");
    } catch (const std::runtime_error error) {
        std::cout << error.what() << std::endl;
    }
    ~DirectoryReader() {
        closedir(this->directory);
    }

    bool readDirectory() {
        return ((this->dirInfo = readdir(this->directory)) != NULL);
    }

    const std::string &getFileName() noexcept {
        return (this->fileName = this->dirInfo->d_name);
    }

    const std::string &getFileList() {

    }
};

#endif // _DirectoryReader_
