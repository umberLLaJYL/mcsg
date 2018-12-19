#if !defined(_MrcContainer_)
#define _MrcContainer_

#include <map>

#if !defined(MrcObjcet)
#define MrcObject std::shared_ptr
#endif // MrcObjcet

template<class Element>
class MrcContainer {
private:
    std::map<std::string, MrcObject<Element>> res;

public:
    MrcContainer() {

    }
    virtual ~MrcContainer() {

    }

    virtual bool operator < (const std::string &) {
        
    }

    virtual MrcObject<Element> &operator [] (const std::string &idx) {
        return res.find(idx)->second;
    }
};

#endif // _MrcContainer_
