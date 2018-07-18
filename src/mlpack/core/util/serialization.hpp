
#ifndef GO_SERIALIZATION_UTIL_HPP
#define GO_SERIALIZATION_UTIL_HPP

#include "serialization_util.hpp"

namespace mlpack {
namespace bindings {
namespace python {

static std::string mlpack_SerializeOut(const char *ptr, const char *name)
{
  return SerializeOut(ptr, name);
}

static void mlpack_SerializeIn(const char *ptr, const char *str, const char *name)
{
  SerializeIn(ptr, str, name);
}

} // namespace python
} // namespace bindings
} // namespace mlpack


#endif
