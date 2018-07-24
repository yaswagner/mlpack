# Use this as add_go_binding(name)
macro (add_go_binding name)
# create, e.g., libmlpack_go_pca.so.
add_library(mlpack_go_${name} SHARED ${CMAKE_SOURCE_DIR}/src/mlpack/methods/${name}/${name}_main.cpp)
target_link_libraries(mlpack_go_${name} mlpack ${MLPACK_LIBRARIES})
target_compile_definitions(mlpack_go_${name} PUBLIC "BINDING_TYPE=BINDING_TYPE_PYX")

# Now we also want to create the header file ${name}.h.
# But in order to use configure_file() with arguments, we actually
# have to create a separate file... more on that later.

# This command will create the .h file in, e.g.,
# build/src/mlpack/bindings/go/methods/pca.h, from the file
# src/mlpack/bindings/go/go_include.h.in.
add_custom_command(OUTPUT ${CMAKE_BINARY_DIR}/src/mlpack/bindings/go/${name}.h
   COMMAND ${CMAKE_COMMAND}
       -DGENERATE_H_IN=${CMAKE_SOURCE_DIR}/src/mlpack/bindings/go/go_include.h.in
       -DGENERATE_H_OUT=${CMAKE_BINARY_DIR}/src/mlpack/bindings/go/${name}.h
       -DPROGRAM_NAME=${name}
       -P ${CMAKE_SOURCE_DIR}/CMake/GenerateGoInclude.cmake
   DEPENDS ${CMAKE_SOURCE_DIR}/src/mlpack/bindings/go/go_include.h.in)

# This command will create the .cpp file in, e.g.,
# build/src/mlpack/bindings/go/methods/pca.cpp, from the file
# src/mlpack/bindings/go/go_include.cpp.in.
add_custom_command(OUTPUT ${CMAKE_BINARY_DIR}/src/mlpack/bindings/go/${name}.cpp
   COMMAND ${CMAKE_COMMAND}
       -DGENERATE_CPP_IN=${CMAKE_SOURCE_DIR}/src/mlpack/bindings/go/go_include.cpp.in
       -DGENERATE_CPP_OUT=${CMAKE_BINARY_DIR}/src/mlpack/bindings/go/${name}.cpp
       -DPROGRAM_NAME=${name}
       -P ${CMAKE_SOURCE_DIR}/CMake/GenerateGoIncludeCPP.cmake
   DEPENDS ${CMAKE_SOURCE_DIR}/src/mlpack/bindings/go/go_include.cpp.in)

add_custom_target(go_${name} DEPENDS ${CMAKE_BINARY_DIR}/src/mlpack/bindings/go/${name}.h ${CMAKE_BINARY_DIR}/src/mlpack/bindings/go/${name}.cpp )

endmacro ()
