#ifndef GO_PCA_CUTIL_HPP
#define GO_PCA_CUTIL_HPP


#include "pca_main.cpp"


namespace mlpack {


extern "C" void C_mlpackMain()
{
  mlpackMain();
}

} // namespace mlpack

#endif
