#include "arma_util.h"
#include "arma_util.hpp"
#include "cli_util.hpp"

namespace mlpack {
namespace util {

extern "C"
{
  void to_matrix(const double mat[], int row, int col)
  {
    arma::mat input(mat, row, col);
    arma::mat mult = 2*input;

    std::cout << "ARMA:" << std::endl;
    input.print("input: ");
    mult.print("2*input: ");
    std::cout << "addr mat: " << mat << std::endl;
    std::cout << "input n_rows: " << input.n_rows << std::endl;
    std::cout << "input n_rows: " << input.n_cols << std::endl;
    std::cout << "input n_elems: " << input.n_elem << std::endl;

    std::string identifier = "input";
    SetParam(identifier, input);
  }

} // extern "C"

} // namespace util
} // namespace mlpack
