#ifndef GO_PERCEPTRON_H
#define GO_PERCEPTRON_H

#include <stdint.h>
#include <stddef.h>

struct Model;

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

typedef void *MLPACK_PerceptronModel;

extern void MLPACK_SetPerceptronModelPtr(const char* identifier, MLPACK_PerceptronModel value);

extern void *MLPACK_GetPerceptronModelPtr(const char* identifier);

extern void MLPACK_perceptron();

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif
