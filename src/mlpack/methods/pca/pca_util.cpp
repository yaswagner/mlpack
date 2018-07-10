#include "pca_impl.hpp"
#include "pca.hpp"
#include "pca_main.h"
#include "pca_util.hpp"

namespace mlpack {

extern "C" void C_mlpackMain()
{
  pca_mlpackMain();
}

} // namespace mlpack
