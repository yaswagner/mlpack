#ifndef MLPACK_BINDINGS_GO_MLPACK_SERIALIZATION_H
#define MLPACK_BINDINGS_GO_MLPACK_SERIALIZATION_H

#include "serialization.hpp"
#include "serialization.h"
#include <mlpack/core.hpp>

namespace mlpack {
namespace bindings {
namespace python {

extern "C" const char* C_SerializeOut(const char *ptr, const char *name)
{
  std::string str = mlpack_SerializeOut(ptr, name);
  const char* cstr = str.c_str();
  return cstr;
}

extern "C" void C_SerializeIn(const char *ptr, const char *str, const char *name)
{
  mlpack_SerializeIn(ptr, str, name);
}

} // namespace python
} // namespace bindings
} // namespace mlpack

#endif
