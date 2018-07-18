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

extern int MLPACK_NumRows();

// Return the number of cols.
extern int MLPACK_NumCols();

// Return the number of elems.
extern int MLPACK_NumElems();

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif
