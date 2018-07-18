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
  arma::mat input(const_cast<double*>(mat), row, col, false, true);

  // Check if arma matrix is equivalent to Go's.
  std::cout << "\nARMA INPUT:" << std::endl;
  input.print();

  // Set input parameter with corresponding matrix in CLI.
  SetParam(identifier, input);
}

void *MLPACK_MatrixPtr(const char *identifier){
  arma::mat output = CLI::GetParam<arma::mat>(identifier);
  std::cout << "\nARMA OUTPUT:" << std::endl;
  output.print();
  void *ptr = GetMemory(output);
  return ptr;
}

// Return the number of rows.
int MLPACK_NumRows()
{
  std::string param = "output";
  arma::mat output = CLI::GetParam<arma::mat>(param);
  return output.n_rows;
}

// Return the number of cols.
int MLPACK_NumCols()
{
  std::string param = "output";
  arma::mat output = CLI::GetParam<arma::mat>(param);
  return output.n_cols;
}

// // Return the number of elems.
int MLPACK_NumElems()
{
  std::string param = "output";
  arma::mat output = CLI::GetParam<arma::mat>(param);
  return output.n_elem;
}

} // extern "C"


} // namespace util

} // namespace mlpack
