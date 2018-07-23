#include "arma_util.h"
#include "arma_util.hpp"
#include "cli.hpp"
#include "cli_util.hpp"

namespace mlpack {

namespace util {

extern "C" {

void MLPACK_NewMatrix(const char *identifier, const double mat[], int row, int col)
{
  // Advanced constructor.
  arma::mat m(const_cast<double*>(mat), row, col, false, true);

  // Check if arma matrix is equivalent to Go's.
  std::cout << "\nARMA INPUT:" << std::endl;
  m.print();

  // Set input parameter with corresponding matrix in CLI.
  SetParam(identifier, m);
}

void *MLPACK_MatrixPtr(const char *identifier){
  arma::mat output = CLI::GetParam<arma::mat>(identifier);
  std::cout << "\nARMA OUTPUT:" << std::endl;
  output.print();
  void *ptr = GetMemory(output);
  return ptr;
}

// Return the number of rows.
int MLPACK_NumRows(const char *identifier)
{
  arma::mat output = CLI::GetParam<arma::mat>(identifier);
  return output.n_rows;
}

// Return the number of cols.
int MLPACK_NumCols(const char *identifier)
{
  arma::mat output = CLI::GetParam<arma::mat>(identifier);
  return output.n_cols;
}

// // Return the number of elems.
int MLPACK_NumElems(const char *identifier)
{
  arma::mat output = CLI::GetParam<arma::mat>(identifier);
  return output.n_elem;
}

} // extern "C"


} // namespace util

} // namespace mlpack
