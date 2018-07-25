/**
 * @file print_class_defn.hpp
 * @author Ryan Curtin
 *
 * Print the class definition for generating a .pyx binding.
 *
 * mlpack is free software; you may redistribute it and/or modify it under the
 * terms of the 3-clause BSD license.  You should have received a copy of the
 * 3-clause BSD license along with mlpack.  If not, see
 * http://www.opensource.org/licenses/BSD-3-Clause for more information.
 */
#ifndef MLPACK_BINDINGS_GO_PRINT_CLASS_DEFN_HPP
#define MLPACK_BINDINGS_GO_PRINT_CLASS_DEFN_HPP

#include "strip_type.hpp"

namespace mlpack {
namespace bindings {
namespace python {

/**
 * Non-serializable models don't require any special definitions, so this prints
 * nothing.
 */
template<typename T>
void PrintClassDefnCPP(
    const util::ParamData& /* d */,
    const typename boost::disable_if<arma::is_arma_type<T>>::type* = 0,
    const typename boost::disable_if<data::HasSerialize<T>>::type* = 0)
{
  // Do nothing.
}

/**
 * Matrices don't require any special definitions, so this prints nothing.
 */
template<typename T>
void PrintClassDefnCPP(
    const util::ParamData& /* d */,
    const typename boost::enable_if<arma::is_arma_type<T>>::type* = 0)
{
  // Do nothing.
}

/**
 * Serializable models require a special class definition.
 */
template<typename T>
void PrintClassDefnCPP(
    const util::ParamData& d,
    const typename boost::disable_if<arma::is_arma_type<T>>::type* = 0,
    const typename boost::enable_if<data::HasSerialize<T>>::type* = 0)
{
  // First, we have to parse the type.  If we have something like, e.g.,
  // 'LogisticRegression<>', we must convert this to 'LogisticRegression[].'
  std::string strippedType, printedType, defaultsType;
  StripType(d.cppType, strippedType, printedType, defaultsType);

  /**
   * This will produce code like:
   *
   * cdef class <ModelType>Type:
   *   cdef <ModelType>* modelptr
   *
   *   def __cinit__(self):
   *     self.modelptr = new <ModelType>()
   *
   *   def __dealloc__(self):
   *     del self.modelptr
   *
   *   def __getstate__(self):
   *     return SerializeOut(self.modelptr, "<ModelType>")
   *
   *   def __setstate__(self, state):
   *     SerializeIn(self.modelptr, state, "<ModelType>")
   *
   *   def __reduce_ex__(self):
   *     return (self.__class__, (), self.__getstate__())
   */
   const std::string prefix = std::string(indent, ' ');
   std::cout << "void *" << strippedType << "_ptr()" << std::endl;
   std::cout << "{" << std::endl;
   std::cout << prefix << "void *ptr = CLI::GetParam<"
     << strippedType << "*>(\"output_model\");" << std::endl;
   std::cout << "return ptr;" << std::endl;
   std::cout << "}" << std::endl;
   std::cout << prefix << std::endl;
   std::cout << "extern \"C\" void *MLPACK_" << strippedType << "_ptr()" << std::endl;
   std::cout << "{" << std::endl;
   std::cout << prefix << "return "
     << strippedType << "_ptr();" << std::endl;
   std::cout << "return ptr;" << std::endl;
   std::cout << "}" << std::endl;
   std::cout << prefix << std::endl;
}

/**
 * Print the class definition to stdout.  Only serializable models require a
 * different class definition, so anything else does nothing.
 *
 * @param d Parameter data.
 * @param input Unused parameter.
 * @param output Unused parameter.
 */
template<typename T>
void PrintClassDefnCPP(const util::ParamData& d,
                    const void* /* input */,
                    void* /* output */)
{
  PrintClassDefn<typename std::remove_pointer<T>::type>(d);
}

} // namespace python
} // namespace bindings
} // namespace mlpack

#endif
