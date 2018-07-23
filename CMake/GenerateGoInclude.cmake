# GenerateGoInclude.cmake: generate an mlpack .h include file for a Go
# binding.
#
# This file depends on the following variables being set:
#
#  * GENERATE_H_IN: the .h.in file to configure.
#  * GENERATE_H_OUT: the .h file we'll generate.
#  * PROGRAM_NAME: the name of the program (i.e. "pca").
configure_file(${GENERATE_H_IN} ${GENERATE_H_OUT})
