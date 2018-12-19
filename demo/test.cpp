#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>

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

int main(int argc, char const *argv[])
{
    DirectoryReader dr(".dsdddd");

    while(dr.readDirectory()) {
        std::cout << dr.getFileName() << std::endl;
    }
    std::cout << "after throw" << std::endl;
    // DIR *dir = opendir(".");
    // if(dir == NULL)
    //     perror("opendir");

    // struct dirent *cont;
    // while((cont = readdir(dir)) != NULL) {
    //     if(strcmp(cont->d_name, ".") == 0 || strcmp(cont->d_name, "..") == 0)
    //         continue;
    //     else
    //         printf("%s: %d\n", cont->d_name, cont->d_type);
    // }
    return 0;
}
