
#ifndef MLPACK_BINDINGS_GO_MLPACK_SERIALIZATION_H
#define MLPACK_BINDINGS_GO_MLPACK_SERIALIZATION_H

#include <mlpack/core.hpp>

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

extern const char* C_SerializeOut(const char *ptr, const char *name);

extern void C_SerializeIn(const char *ptr, const char *str, const char *name);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif
