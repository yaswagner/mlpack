#include "perceptron_impl.hpp"
#include "perceptron.hpp"
#include "perceptron_util.h"
#include "perceptron_util.hpp"

namespace mlpack {

extern "C" void *MLPACK_PerceptronModelPtr()
{
  return PerceptronModelPtr();
}

extern "C" void MLPACK_Perceptron()
{
  Perceptron_mlpackMain();
}

} // namespace mlpack
