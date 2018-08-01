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
#ifndef MLPACK_BINDINGS_GO_PRINT_GO_STRUCT_HPP
#define MLPACK_BINDINGS_GO_PRINT_GO_STRUCT_HPP

#include "strip_type.hpp"

namespace mlpack {
namespace bindings {
namespace go {

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
   * extern "C" void MLPACK_SetPerceptronModelPtr(const char* identifier,
                  MLPACK_PerceptronModel* value)
   * {
   *   SetParamPtr<PerceptronModel>(identifier, reinterpret_cast<PerceptronModel*>(value), CLI::HasParam("copy_all_inputs"));
   * }

   * extern "C" void *MLPACK_GetPerceptronModelPtr(const char* identifier)
   * {
   *   PerceptronModel *modelptr = GetParamPtr<PerceptronModel>(identifier);
   *   return modelptr;
   * }
   */
   std::cout << std::endl;
   std::cout << "extern \"C\" void MLPACK_Set" << strippedType
              << "Ptr(const char* identifier," << std::endl;
   std::cout << "               MLPACK_" << strippedType << "* value)" << std::endl;
   std::cout << "{" << std::endl;
   std::cout << "    SetParamPtr<" << strippedType
              << ">(identifier," << std::endl;
   std::cout << "    reinterpret_cast<" << strippedType
              << "*(value)," << std::endl;
   std::cout << "    CLI::HasParam(\"copy_all_inputs\"));" << std::endl;
   std::cout << "}" << std::endl;
   std::cout << std::endl;
   std::cout << "extern \"C\" void *MLPACK_Get" << strippedType
              << "Ptr(const char* identifier)" << std::endl;
   std::cout << "{" << std::endl;
   std::cout << "    " << strippedType << "*modelptr = GetParamPtr<"
              << strippedType << ">(identifier);" << strippedType
              << "return modelptr;" << std::endl;
   std::cout << "}" << std::endl;
   std::cout << std::endl;
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
  PrintClassDefnCPP<typename std::remove_pointer<T>::type>(d);
}


/**
 * Non-serializable models don't require any special definitions, so this prints
 * nothing.
 */
template<typename T>
void PrintClassDefnH(
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
void PrintClassDefnH(
    const util::ParamData& /* d */,
    const typename boost::enable_if<arma::is_arma_type<T>>::type* = 0)
{
  // Do nothing.
}

/**
 * Serializable models require a special class definition.
 */
template<typename T>
void PrintClassDefnH(
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
   * typedef void *MLPACK_PerceptronModel;
   *
   * extern void MLPACK_SetPerceptronModelPtr(const char* identifier,
   *         MLPACK_PerceptronModel* value);
   *
   * extern void *MLPACK_GetPerceptronModelPtr(const char* identifier);
   *
   */
   std::cout << "typedef void *MLPACK_" << strippedType
              << ";" << std::endl;
   std::cout << std::endl;
   std::cout << "extern void *MLPACK_Set" << strippedType
              << "Ptr(const char* identifier," << std::endl;
   std::cout << "         MLPACK_" << strippedType << "* value);"
              << std::endl;
   std::cout << std::endl;
   std::cout << "extern void *MLPACK_Get" << strippedType
              << "Ptr(const char* identifier);" << std::endl;
   std::cout << std::endl;
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
void PrintClassDefnH(const util::ParamData& d,
                    const void* /* input */,
                    void* /* output */)
{
  PrintClassDefnH<typename std::remove_pointer<T>::type>(d);
}

/**
 * Non-serializable models don't require any special definitions, so this prints
 * nothing.
 */
template<typename T>
void PrintClassDefnGo(
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
void PrintClassDefnGo(
    const util::ParamData& /* d */,
    const typename boost::enable_if<arma::is_arma_type<T>>::type* = 0)
{
  // Do nothing.
}

/**
 * Serializable models require a special class definition.
 */
template<typename T>
void PrintClassDefnGo(
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
   * }
   */
   std::cout << std::endl;
   std::cout << "func (m *" << strippedType
              << ") alloc(identifier string) {" << std::endl;
   std::cout << " m.mem = C.MLPACK_Get" << strippedType
              << "Ptr(C.CString(identifier))" << std::endl;
   std::cout << " runtime.SetFinalizer(m, free"
              << strippedType << ")" << std::endl;
   std::cout << "}" << std::endl;
   std::cout << std::endl;
   std::cout << std::endl;
   std::cout << "func free" << strippedType
              << "(m *" << strippedType << ") {" << std::endl;
   std::cout << " C.free(unsafe.Pointer(m.mem))" << std::endl;
   std::cout << "}" << std::endl;
   std::cout << std::endl;
   std::cout << "func (m *" << strippedType << ") get"
              << strippedType << "(identifier string) {" << std::endl;
   std::cout << " m.alloc(identifier)" << std::endl;
   std::cout << " time.Sleep(time.Second)" << std::endl;
   std::cout << std::endl;
   std::cout << " modelptr := (*[1<<30-1]float64)(m.mem)" << std::endl;
   std::cout << " m.model = (C.MLPACK_" << strippedType
              << ")(modelptr)" << std::endl;
   std::cout << std::endl;
   std::cout << " runtime.GC()" << std::endl;
   std::cout << " time.Sleep(time.Second)" << std::endl;
   std::cout << "}" << std::endl;
   std::cout << std::endl;
   std::cout << "func set" << strippedType
              << "(identifier string, c *C.MLPACK_"
              << strippedType <<  ") {" << std::endl;
   std::cout << " C.MLPACK_Set" << strippedType
              << "Ptr(C.CString(identifier), c)" << std::endl;
   std::cout << "}" << std::endl;
   std::cout << std::endl;
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
void PrintClassDefnGo(const util::ParamData& d,
                    const void* /* input */,
                    void* /* output */)
{
  PrintClassDefnGo<typename std::remove_pointer<T>::type>(d);
}

} // namespace go
} // namespace bindings
} // namespace mlpack

#endif
