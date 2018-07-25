#ifndef MLPACK_BINDINGS_GO_CLI_UTIL_H
#define MLPACK_BINDINGS_GO_CLI_UTIL_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

extern void MLPACK_ResetTimers();

extern void MLPACK_EnableTimers();

extern void MLPACK_DisableBacktrace();

extern void MLPACK_EnableVerbose();

extern void MLPACK_DisableVerbose();

extern void MLPACK_ClearSettings();

extern void MLPACK_SetPassed(const char *name);

extern void MLPACK_RestoreSettings(const char *name);

extern void MLPACK_SetParamDouble(const char *identifier, double value);

extern void MLPACK_SetParamInt(const char *identifier, int value);

extern void MLPACK_SetParamFloat(const char *identifier, float value);

extern void MLPACK_SetParamBool(const char *identifier, bool value);

extern void MLPACK_SetParamString(const char *identifier, const char *value);

extern void MLPACK_SetParamPtr(const char *identifier, const double *ptr, const bool copy);

extern bool MLPACK_HasParam(const char *identifier);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif
