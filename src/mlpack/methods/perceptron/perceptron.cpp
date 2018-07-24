#include "perceptron_impl.hpp"
#include "perceptron.hpp"
#include "perceptron.h"
#include "perceptron_main.cpp"

namespace mlpack {

void *perceptron_modelPtr()
{
  void *ptr = CLI::GetParam<PerceptronModel*>("output_model");
  return ptr;
}

extern "C" void *MLPACK_perceptron_modelPtr()
{
  return perceptron_modelPtr();
}

static void perceptron_mlpackMain()
{
  mlpackMain();
}

extern "C" void MLPACK_perceptron()
{
  perceptron_mlpackMain();
}

} // namespace mlpack
