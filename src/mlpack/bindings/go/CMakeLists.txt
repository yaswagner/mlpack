
# Nothing in this directory will be compiled into mlpack.
set(BINDING_SOURCES
  import_decl.hpp
  print_class_defn.hpp
  print_go.hpp
  print_go.cpp
  strip_type.hpp
)

# Add a macro to build a go binding.
macro (add_go_binding name)
set (MLPACK_PYXS ${MLPACK_PYXS} "${name}.pyx")
set (MLPACK_PYXS ${MLPACK_PYXS} PARENT_SCOPE)

# create, e.g., libmlpack_go_pca.so.
add_library(mlpack_go_${name} SHARED ${CMAKE_SOURCE_DIR}/src/mlpack/methods/${name}/${name}_main.cpp)
target_link_libraries(mlpack_go_${name} mlpack ${MLPACK_LIBRARIES})
target_compile_definitions(mlpack_go_${name} PUBLIC "BINDING_TYPE=BINDING_TYPE_PYX")

add_custom_command(OUTPUT ${CMAKE_BINARY_DIR}/src/mlpack/bindings/go/generate_go_${name}.cpp
   COMMAND ${CMAKE_COMMAND}
       -DGENERATE_CPP_IN=${CMAKE_SOURCE_DIR}/src/mlpack/bindings/go/generate_go.cpp.in
       -DGENERATE_CPP_OUT=${CMAKE_BINARY_DIR}/src/mlpack/bindings/go/generate_go_${name}.cpp
       -DPROGRAM_MAIN_FILE=${CMAKE_CURRENT_SOURCE_DIR}/${name}_main.cpp
       -DPROGRAM_NAME=${name}
       -P ${CMAKE_SOURCE_DIR}/CMake/GenerateGoCPP.cmake
   DEPENDS ${CMAKE_SOURCE_DIR}/src/mlpack/bindings/go/generate_go.cpp.in)

add_custom_target(go_${name}
    DEPENDS ${CMAKE_BINARY_DIR}/src/mlpack/bindings/go/generate_go_${name}.cpp)

add_executable(generate_go_${name}
    ${CMAKE_BINARY_DIR}/src/mlpack/bindings/go/generate_go_${name}.cpp
    ${CMAKE_SOURCE_DIR}/src/mlpack/bindings/go/print_go.hpp
    ${CMAKE_SOURCE_DIR}/src/mlpack/bindings/go/print_go.cpp)
target_link_libraries(generate_go_${name} mlpack ${MLPACK_LIBRARIES})
set_target_properties(generate_go_${name} PROPERTIES COMPILE_FLAGS
    -DBINDING_TYPE=BINDING_TYPE_PYX)
add_custom_command(TARGET generate_go_${name} POST_BUILD
    COMMAND ${CMAKE_COMMAND}
        -DGENERATE_CPP_PROGRAM=${CMAKE_BINARY_DIR}/bin/generate_go_${name}
        -DCPP_OUTPUT_FILE=${CMAKE_BINARY_DIR}/src/mlpack/bindings/go/${name}.cpp
        -P ${CMAKE_SOURCE_DIR}/CMake/GenerateCPP.cmake)

add_custom_target(generate_${name}
    DEPENDS ${CMAKE_BINARY_DIR}/src/mlpack/bindings/go/{name}.cpp)

add_custom_target(build_go_${name}
    DEPENDS generate_go_${name}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/src/mlpack/bindings/go/
    COMMENT "Building Go binding ${name}.cpp...")

add_dependencies(build_go_${name} generate_go_${name})

endmacro ()
