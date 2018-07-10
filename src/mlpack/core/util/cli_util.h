#ifndef GO_CLI_UTIL_H
#define GO_CLI_UTIL_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define BINDING_TYPE BINDING_TYPE_PYX

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

typedef void MatrixInput;

extern void C_ResetTimers();
extern void C_EnableTimers();
extern void C_DisableBacktrace();
extern void C_EnableVerbose();
extern void C_DisableVerbose();
extern void C_ClearSettings();
extern void C_SetPassed(const char *name);
extern void C_RestoreSettings(const char *name);
extern void C_SetParamDouble(const char *identifier, double value);
extern void C_SetParamInt(const char *identifier, int value);
extern void C_SetParamFloat(const char *identifier, float value);
extern void C_SetParamBool(const char *identifier, bool value);
extern void C_SetParamString(const char *identifier, const char *value);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif
