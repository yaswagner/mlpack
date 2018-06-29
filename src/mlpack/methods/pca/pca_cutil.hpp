#include "pca_impl.hpp"
#include "pca.h"
#include "pca_main.cpp"

namespace mlpack {
namespace util {

extern "C" void C_mlpackMain()
{
  mlpackMain();
}

} // namespace pca
} // namespace mlpack
