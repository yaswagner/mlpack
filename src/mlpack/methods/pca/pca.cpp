#include "pca_impl.hpp"
#include "pca.hpp"
// #include "pca_main.cpp"
#include "pca.h"

namespace mlpack {

static void pca_mlpackMain()
{
  mlpackMain();
}

extern "C" void MLPACK_pca()
{
  pca_mlpackMain();
}

} // namespace mlpack
