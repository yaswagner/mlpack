#include "arma_util.h"
#include "arma_util.hpp"
#include "cli.hpp"
#include "cli_util.hpp"

namespace mlpack {

namespace util {

extern "C" {

void MLPACK_NewMatrix(const double mat[], int row, int col)
{
  arma::mat input(const_cast<double*>(mat), row, col, false, true);
  arma::mat mult = 2*input;
  int rows = mult.n_rows;
  int cols = mult.n_cols;
  int elem = mult.n_elem;


  std::cout << "ARMA MATRIX:" << std::endl;
  input.print("input: ");
  mult.print("2*input: ");
  std::cout << "rows: " << rows << std::endl;
  std::cout << "cols: " << cols << std::endl;
  std::cout << "elem: " << elem << std::endl;
  std::cout << "size: " << size(mult) << std::endl;

  std::string identifier = "input";
  SetParam(identifier, input);
}

void *MLPACK_MatrixPtr(){
  std::string param = "input";
  arma::mat output = CLI::GetParam<arma::mat>(param);
  void *ptr = GetMemory(output);
  return ptr;
}

// Return the number of rows.
int MLPACK_NumRows()
{
  std::string param = "input";
  arma::mat output = CLI::GetParam<arma::mat>(param);
  return output.n_rows;
}

// Return the number of cols.
int MLPACK_NumCols()
{
  std::string param = "input";
  arma::mat output = CLI::GetParam<arma::mat>(param);
  return output.n_cols;

}

// // Return the number of elems.
int MLPACK_NumElems()
{
  std::string param = "input";
  arma::mat output = CLI::GetParam<arma::mat>(param);
  return output.n_elem;
}

} // extern "C"


} // namespace util

} // namespace mlpack
