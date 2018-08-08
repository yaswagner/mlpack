#ifndef MLPACK_BINDINGS_GO_MLPACK_ARMA_UTIL_H
#define MLPACK_BINDINGS_GO_MLPACK_ARMA_UTIL_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

extern void MLPACK_ToArma(const char *identifier, const double mat[], int row, int col);

extern void *MLPACK_ArmaPtr(const char *identifier);

extern void *MLPACK_ArmaRowPtr(const char *identifier);

extern int MLPACK_NumRows(const char *identifier);

extern int MLPACK_NumCols(const char *identifier);

extern int MLPACK_NumElems(const char *identifier);

extern int MLPACK_RowSize(const char *identifier);

extern int MLPACK_ColSize(const char *identifier);

extern int MLPACK_NumElemsRow(const char *identifier);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif
