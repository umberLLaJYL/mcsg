#include "testdl.h"
#include "testso.h"

#include <memory>

std::shared_ptr<Test> getObject()
{
    return std::make_shared<TestDl>();
}

std::shared_ptr<Test> getSobject()
{
    return std::make_shared<TestSo>();
}
