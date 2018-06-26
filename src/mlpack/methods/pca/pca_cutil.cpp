#include "pca_impl.hpp"
#include "pca.h"

namespace mlpack {

  extern "C" void C_mlpackMain()
  {
    pca::mlpackMain();
  }

} // namespace mlpack
