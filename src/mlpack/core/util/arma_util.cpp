#include "arma_util.h"
#include "arma_util.hpp"
#include "cli.hpp"
#include "cli_util.hpp"

namespace mlpack {

namespace util {

extern "C" {

void MLPACK_ToArma(const char *identifier, const double mat[], int row, int col)
{
  // Advanced constructor.
  arma::mat m(const_cast<double*>(mat), row, col, false, true);

  // Check if arma matrix is equivalent to Go's.
  std::cout << "\nARMA INPUT:" << std::endl;
  m.print();

  // Set input parameter with corresponding matrix in CLI.
  SetParam(identifier, m);
}

void *MLPACK_ArmaPtr(const char *identifier){
  arma::mat output = CLI::GetParam<arma::mat>(identifier);
  std::cout << "\nARMA OUTPUT:" << std::endl;
  output.print();
  void *ptr = GetMemory(output);
  return ptr;
}

void *MLPACK_ArmaRowPtr(const char *identifier){
  std::cout << "\nARMA ROW:" << std::endl;
  arma::Row<size_t> output = CLI::GetParam<arma::Row<size_t>>(identifier);
  std::cout << "\nARMA ROW OUTPUT:" << std::endl;
  output.print();
  void *ptr = GetMemory(output);
  return ptr;
}

void *MLPACK_ArmaColPtr(const char *identifier){
  arma::Col<size_t> output = CLI::GetParam<arma::Col<size_t>>(identifier);
  std::cout << "\nARMA ROW OUTPUT:" << std::endl;
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

int MLPACK_RowSize(const char *identifier)
{
  arma::Row<size_t> output = CLI::GetParam<arma::Row<size_t>>(identifier);
  return output.n_rows;
}

// Return the number of cols.
int MLPACK_ColSize(const char *identifier)
{
  arma::Col<size_t> output = CLI::GetParam<arma::Col<size_t>>(identifier);
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
