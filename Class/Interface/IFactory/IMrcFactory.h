#if !defined(_IMrcFactory_)
#define _IMrcFactory_

#include "IFactory.h"
#include "SoReader.h"
#include "DirectoryReader.h"

// #include "../IMrController/IMrController.h"

#if !defined(MrcObject)
#define MrcObject std::shared_ptr
#endif // MrcObject

class IMrcFactory {
private:
    DirectoryReader factoryDirReader;
    std::map<std::string, std::pair<MrcObject<SoReader>, MrcObject<IResourceFactory>>> resFactory;

public:
    IMrcFactory(const std::string &dir) try : factoryDirReader(dir) {

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
            MrcObject<SoReader> soReader = MrcObject<SoReader>::make_shared(factoryFileName);
            factoryFileName.resize(factoryFileName.size()-3);
            MrcObject<IResourceFactory> sharedObject = MrcObject<IResourceFactory>::make_shared(soReader->fetchObject(factoryFileName));
            
            this->resFactory.insert({factoryFileName, {soReader, sharedObject}});
        }
    }

    bool addFactory(MrcObject<IResourceFactory> &factory) {

    }

    // virtual MrcObject<IMrController> create(const std::string &) = 0;
};

#endif // _IMrcFactory_
