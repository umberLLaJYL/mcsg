#if !defined(_Object_)
#define _Object_

#include <memory>

#define Object(Type) std::shared_ptr<Type>

#endif // _Object_
