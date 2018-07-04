#include "arma_util.h"
#include "arma_util.hpp"
#include "cli_util.hpp"

namespace mlpack {
namespace util {

extern "C"
{
  void to_matrix(const double mat[], int row, int col)
  {
    arma::mat input(const_cast<double*>(mat), row, col, false, true);
    arma::mat mult = 2*input;

    std::cout << "ARMA MATRIX:" << std::endl;
    input.print("input: ");
    mult.print("2*input: ");

    std::string identifier = "input";
    SetParam(identifier, input);
  }

  void *output(){
    std::string param = "input";
    arma::mat output = CLI::GetParam<arma::mat>(param);
    void *ptr = GetMemory(output);
    std::cout << "\nARMA TO GO " << std::endl;
    std::cout << "addr ptr from C: " << ptr << std::endl;
    return ptr;
  }


} // extern "C"

} // namespace util
} // namespace mlpack
