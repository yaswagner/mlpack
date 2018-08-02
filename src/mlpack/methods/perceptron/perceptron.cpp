#include "perceptron_impl.hpp"
#include "perceptron.hpp"
#include "perceptron.h"
#include "perceptron_main.cpp"
#include <mlpack/core/util/cli_util.hpp>

using namespace mlpack;
using namespace mlpack::perceptron;
using namespace mlpack::util;
using namespace std;
using namespace arma;


extern "C" void MLPACK_SetPerceptronModelPtr(const char* identifier,
              void *value)
{
    SetParamPtr<PerceptronModel>(identifier,
    static_cast<PerceptronModel*>(value),
    CLI::HasParam("copy_all_inputs"));
}

extern "C" void *MLPACK_GetPerceptronModelPtr(const char* identifier)
{
  PerceptronModel *modelptr = GetParamPtr<PerceptronModel>(identifier);
  cout << "\n C++ model: " << modelptr << endl;
  return modelptr;
}

static void perceptron_mlpackMain()
{
  mlpackMain();
}

extern "C" void MLPACK_perceptron()
{
  perceptron_mlpackMain();
}
