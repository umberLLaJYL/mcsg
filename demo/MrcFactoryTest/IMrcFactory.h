#if !defined(_IMrcFactory_)
#define _IMrcFactory_

#include <map>
#include <memory>

#include "SoReader.h"
#include "DirectoryReader.h"

#include "TestObj/ITestObj.h"

#if !defined(MrcObject)
#define MrcObject std::shared_ptr
#endif // MrcObject

class IMrcFactory {
private:
    DirectoryReader factoryDirReader;
    std::map<std::string, std::pair<MrcObject<SoReader>, MrcObject<ITestObj>>> resFactory;

public:
    IMrcFactory() try {

    } catch (const std::runtime_error error) {
        std::cout << error.what() << std::endl;
    }

    virtual ~IMrcFactory() {
        this->factoryDirReader.closeDirectory();
    }

    virtual bool initialize(const std::string &launchFile) {
        std::string factoryFileName;

        this->factoryDirReader.openDirectory(launchFile);
        while((factoryFileName = this->factoryDirReader.getFileNameWithKey(".so")) != MrcNullString) {
            MrcObject<SoReader> soReader = std::make_shared<SoReader>(factoryFileName);
    //         factoryFileName.resize(factoryFileName.size()-3);
            MrcObject<ITestObj> sharedObject = std::make_shared<ITestObj>(soReader->fetchObject(factoryFileName));
    //         this->resFactory.insert({factoryFileName, {soReader, sharedObject}});
        }
    }

    bool addFactory(MrcObject<ITestObj> &factory) {

    }

    virtual MrcObject<IMrController> create(const std::string &) = 0;
};

#endif // _IMrcFactory_
