#ifndef ARMA__UTIL_H
#define ARMA__UTIL_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

extern void MLPACK_NewMatrix(const char *identifier, const double mat[], int row, int col);

extern void *MLPACK_MatrixPtr(const char *identifier);

extern int MLPACK_NumRows(const char *identifier);

extern int MLPACK_NumCols(const char *identifier);

extern int MLPACK_NumElems(const char *identifier);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif
