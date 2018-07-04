#ifndef ARMA__UTIL_H
#define ARMA__UTIL_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>


#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

extern void to_matrix(const double mat[], int row, int col);

extern void *output();


#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif
