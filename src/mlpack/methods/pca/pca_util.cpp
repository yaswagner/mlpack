#include "pca_impl.hpp"
#include "pca.hpp"
#include "pca_util.h"
#include "pca_util.hpp"

namespace mlpack {

extern "C" void C_pca_mlpackMain()
{
  pca_mlpackMain();
}

} // namespace mlpack
