
# Nothing in this directory will be compiled into mlpack.
set(BINDING_SOURCES
  get_type.hpp
  get_param.hpp
  get_printable_param.hpp
  go_option.hpp
  print_class_defn.hpp
  print_defn_input.hpp
  print_defn_output.hpp
  print_doc.hpp
  print_doc_functions.hpp
  print_doc_functions_impl.hpp
  print_input_processing.hpp
  print_method_config.hpp
  print_method_init.hpp
  print_output_processing.hpp
  print_cpp.hpp
  print_cpp.cpp
  print_go.hpp
  print_go.cpp
  print_h.hpp
  print_h.cpp
  strip_type.hpp
)

# Add a macro to build a go binding.
macro (add_go_binding name)

# Create, e.g., libmlpack_go_pca.so.
add_library(mlpack_go_${name} SHARED ${CMAKE_SOURCE_DIR}/src/mlpack/methods/${name}/${name}_main.cpp)
target_link_libraries(mlpack_go_${name} mlpack ${MLPACK_LIBRARIES})
target_compile_definitions(mlpack_go_${name} PUBLIC "BINDING_TYPE=BINDING_TYPE_GO")

# Create .cpp file for C API, e.g. pca.cpp.
add_custom_command(OUTPUT ${CMAKE_BINARY_DIR}/src/mlpack/bindings/go/generate_cpp_${name}.cpp
   COMMAND ${CMAKE_COMMAND}
       -DGENERATE_CPP_IN=${CMAKE_SOURCE_DIR}/src/mlpack/bindings/go/generate_go.cpp.in
       -DGENERATE_CPP_OUT=${CMAKE_BINARY_DIR}/src/mlpack/bindings/go/generate_cpp_${name}.cpp
       -DPROGRAM_MAIN_FILE=${CMAKE_CURRENT_SOURCE_DIR}/${name}_main.cpp
       -DPROGRAM_NAME=${name}
       -P ${CMAKE_SOURCE_DIR}/CMake/GenerateGoCPP.cmake
   DEPENDS ${CMAKE_SOURCE_DIR}/src/mlpack/bindings/go/generate_go.cpp.in)

add_executable(generate_cpp_${name}
    ${CMAKE_BINARY_DIR}/src/mlpack/bindings/go/generate_cpp_${name}.cpp
    ${CMAKE_SOURCE_DIR}/src/mlpack/bindings/go/print_cpp.hpp
    ${CMAKE_SOURCE_DIR}/src/mlpack/bindings/go/print_cpp.cpp)
target_link_libraries(generate_cpp_${name} mlpack ${MLPACK_LIBRARIES})
set_target_properties(generate_cpp_${name} PROPERTIES COMPILE_FLAGS
    -DBINDING_TYPE=BINDING_TYPE_GO)
add_custom_command(TARGET generate_cpp_${name} POST_BUILD
    COMMAND ${CMAKE_COMMAND}
        -DGENERATE_CPP_PROGRAM=${CMAKE_BINARY_DIR}/bin/generate_cpp_${name}
        -DCPP_OUTPUT_FILE=${CMAKE_BINARY_DIR}/src/mlpack/bindings/go/${name}.cpp
        -P ${CMAKE_SOURCE_DIR}/CMake/GenerateCPP.cmake)

add_custom_target(build_cpp_${name}
    DEPENDS generate_cpp_${name}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/src/mlpack/bindings/go/
    COMMENT "Building ${name}.cpp for Go binding ...")

add_dependencies(build_cpp_${name} generate_cpp_${name})


# Create .h file for C API, e.g. pca.h.
add_custom_command(OUTPUT ${CMAKE_BINARY_DIR}/src/mlpack/bindings/go/generate_h_${name}.cpp
   COMMAND ${CMAKE_COMMAND}
       -DGENERATE_H_IN=${CMAKE_SOURCE_DIR}/src/mlpack/bindings/go/generate_go.h.in
       -DGENERATE_H_OUT=${CMAKE_BINARY_DIR}/src/mlpack/bindings/go/generate_h_${name}.cpp
       -DPROGRAM_MAIN_FILE=${CMAKE_CURRENT_SOURCE_DIR}/${name}_main.cpp
       -DPROGRAM_NAME=${name}
       -P ${CMAKE_SOURCE_DIR}/CMake/GenerateGoH.cmake
   DEPENDS ${CMAKE_SOURCE_DIR}/src/mlpack/bindings/go/generate_go.h.in)

add_executable(generate_h_${name}
    ${CMAKE_BINARY_DIR}/src/mlpack/bindings/go/generate_h_${name}.cpp
    ${CMAKE_SOURCE_DIR}/src/mlpack/bindings/go/print_h.hpp
    ${CMAKE_SOURCE_DIR}/src/mlpack/bindings/go/print_h.cpp)
target_link_libraries(generate_h_${name} mlpack ${MLPACK_LIBRARIES})
set_target_properties(generate_h_${name} PROPERTIES COMPILE_FLAGS
    -DBINDING_TYPE=BINDING_TYPE_GO)
add_custom_command(TARGET generate_h_${name} POST_BUILD
    COMMAND ${CMAKE_COMMAND}
        -DGENERATE_H_PROGRAM=${CMAKE_BINARY_DIR}/bin/generate_h_${name}
        -DH_OUTPUT_FILE=${CMAKE_BINARY_DIR}/src/mlpack/bindings/go/${name}.h
        -P ${CMAKE_SOURCE_DIR}/CMake/GenerateH.cmake)

add_custom_target(build_h_${name}
    DEPENDS generate_h_${name}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/src/mlpack/bindings/go/
    COMMENT "Building ${name}.h for Go binding ...")

add_dependencies(build_h_${name} generate_h_${name})


# Create .go file, pca.go.
add_custom_command(OUTPUT ${CMAKE_BINARY_DIR}/src/mlpack/bindings/go/generate_go_${name}.cpp
   COMMAND ${CMAKE_COMMAND}
       -DGENERATE_GO_IN=${CMAKE_SOURCE_DIR}/src/mlpack/bindings/go/generate_go.go.in
       -DGENERATE_GO_OUT=${CMAKE_BINARY_DIR}/src/mlpack/bindings/go/generate_go_${name}.cpp
       -DPROGRAM_MAIN_FILE=${CMAKE_CURRENT_SOURCE_DIR}/${name}_main.cpp
       -DPROGRAM_NAME=${name}
       -P ${CMAKE_SOURCE_DIR}/CMake/GenerateGoGo.cmake
   DEPENDS ${CMAKE_SOURCE_DIR}/src/mlpack/bindings/go/generate_go.go.in)

add_executable(generate_go_${name}
    ${CMAKE_BINARY_DIR}/src/mlpack/bindings/go/generate_go_${name}.cpp
    ${CMAKE_SOURCE_DIR}/src/mlpack/bindings/go/print_go.hpp
    ${CMAKE_SOURCE_DIR}/src/mlpack/bindings/go/print_go.cpp)
target_link_libraries(generate_go_${name} mlpack ${MLPACK_LIBRARIES})
set_target_properties(generate_go_${name} PROPERTIES COMPILE_FLAGS
    -DBINDING_TYPE=BINDING_TYPE_GO)
add_custom_command(TARGET generate_go_${name} POST_BUILD
    COMMAND ${CMAKE_COMMAND}
        -DGENERATE_GO_PROGRAM=${CMAKE_BINARY_DIR}/bin/generate_go_${name}
        -DGO_OUTPUT_FILE=${CMAKE_BINARY_DIR}/src/mlpack/bindings/go/${name}.go
        -P ${CMAKE_SOURCE_DIR}/CMake/GenerateGo.cmake)

add_custom_target(build_go_${name}
    DEPENDS generate_go_${name}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/src/mlpack/bindings/go/
    COMMENT "Building ${name}.go for Go binding ...")

add_dependencies(build_go_${name} generate_go_${name})

endmacro ()
