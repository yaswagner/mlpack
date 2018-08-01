#ifndef GO_PERCEPTRON_H
#define GO_PERCEPTRON_H

#include <stdint.h>
#include <stddef.h>

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif


extern void MLPACK_SetPerceptronModelPtr(const char* identifier,
          void *value);

extern void *MLPACK_GetPerceptronModelPtr(const char* identifier);

extern void MLPACK_perceptron();

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif
