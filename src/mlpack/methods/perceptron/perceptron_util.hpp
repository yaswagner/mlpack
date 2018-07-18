
#ifndef GO_PERCEPTRON_UTIL_HPP
#define GO_PERCEPTRON_UTIL_HPP

#include "perceptron_impl.hpp"
#include "perceptron.hpp"
#include "perceptron_main.cpp"

using namespace mlpack;
using namespace mlpack::perceptron;
using namespace mlpack::util;
using namespace std;

static void *PerceptronModelPtr()
{
  return new PerceptronModel();
}

static void Perceptron_mlpackMain()
{
  mlpackMain();
}

#endif
