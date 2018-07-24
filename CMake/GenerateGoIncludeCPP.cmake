# GenerateGoInclude.cmake: generate an mlpack .h include file for a Go
# binding.
#
# This file depends on the following variables being set:
#
#  * GENERATE_CPP_IN: the .h.in file to configure.
#  * GENERATE_CPP_OUT: the .h file we'll generate.
#  * PROGRAM_NAME: the name of the program (i.e. "pca").
configure_file(${GENERATE_CPP_IN} ${GENERATE_CPP_OUT})
