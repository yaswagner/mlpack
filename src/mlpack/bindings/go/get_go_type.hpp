/**
 * @file get_python_type.hpp
 * @author Ryan Curtin
 *
 * Template metaprogramming to return the string representation of the Python
 * type for a given Python binding parameter.
 *
 * mlpack is free software; you may redistribute it and/or modify it under the
 * terms of the 3-clause BSD license.  You should have received a copy of the
 * 3-clause BSD license along with mlpack.  If not, see
 * http://www.opensource.org/licenses/BSD-3-Clause for more information.
 */
#ifndef MLPACK_BINDINGS_GO_GET_GO_TYPE_HPP
#define MLPACK_BINDINGS_GO_GET_GO_TYPE_HPP

#include <mlpack/prereqs.hpp>
#include <mlpack/core/util/is_std_vector.hpp>

namespace mlpack {
namespace bindings {
namespace go {

template<typename T>
inline std::string GetGoType(
    const util::ParamData& /* d */,
    const typename boost::disable_if<util::IsStdVector<T>>::type* = 0,
    const typename boost::disable_if<data::HasSerialize<T>>::type* = 0,
    const typename boost::disable_if<arma::is_arma_type<T>>::type* = 0)
{
  return "unknown";
}

template<>
inline std::string GetGoType<int>(
    const util::ParamData& /* d */,
    const typename boost::disable_if<util::IsStdVector<int>>::type*,
    const typename boost::disable_if<data::HasSerialize<int>>::type*,
    const typename boost::disable_if<arma::is_arma_type<int>>::type*)
{
  return "int32";
}

template<>
inline std::string GetGoType<float>(
    const util::ParamData& /* d */,
    const typename boost::disable_if<util::IsStdVector<float>>::type*,
    const typename boost::disable_if<data::HasSerialize<float>>::type*,
    const typename boost::disable_if<arma::is_arma_type<float>>::type*)
{
  return "float32";
}

template<>
inline std::string GetGoType<double>(
    const util::ParamData& /* d */,
    const typename boost::disable_if<util::IsStdVector<double>>::type*,
    const typename boost::disable_if<data::HasSerialize<double>>::type*,
    const typename boost::disable_if<arma::is_arma_type<double>>::type*)
{
  return "float64";
}

template<>
inline std::string GetGoType<std::string>(
    const util::ParamData& /* d */,
    const typename boost::disable_if<util::IsStdVector<std::string>>::type*,
    const typename boost::disable_if<data::HasSerialize<std::string>>::type*,
    const typename boost::disable_if<arma::is_arma_type<std::string>>::type*)
{
  return "string";
}

template<>
inline std::string GetGoType<size_t>(
    const util::ParamData& /* d */,
    const typename boost::disable_if<util::IsStdVector<size_t>>::type*,
    const typename boost::disable_if<data::HasSerialize<size_t>>::type*,
    const typename boost::disable_if<arma::is_arma_type<size_t>>::type*)
{
  return "size_t";
}

template<>
inline std::string GetGoType<bool>(
    const util::ParamData& /* d */,
    const typename boost::disable_if<util::IsStdVector<bool>>::type*,
    const typename boost::disable_if<data::HasSerialize<bool>>::type*,
    const typename boost::disable_if<arma::is_arma_type<bool>>::type*)
{
  return "bool";
}

template<typename T>
inline std::string GetGoType(
    const util::ParamData& d,
    const typename boost::enable_if<util::IsStdVector<T>>::type* = 0)
{
  return "list of " + GetGoType<typename T::value_type>(d) + "s";
}

template<typename T>
inline std::string GetGoType(
    const util::ParamData& /* d */,
    const typename boost::enable_if<arma::is_arma_type<T>>::type* = 0)
{
  std::string type = "mat.Dense";
  if (T::is_row)
    type = "mat.VecDense";
  else if (T::is_col)
    type = "mat.VecDense";

  return type;
}

template<typename T>
inline std::string GetGoType(
    const util::ParamData& d,
    const typename boost::disable_if<arma::is_arma_type<T>>::type* = 0,
    const typename boost::enable_if<data::HasSerialize<T>>::type* = 0)
{
  return d.cppType;
}

} // namespace go
} // namespace bindings
} // namespace mlpack

#endif
