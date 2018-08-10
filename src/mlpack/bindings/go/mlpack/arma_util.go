package mlpack

/*
#cgo CFLAGS: -I. -I/capi -g -Wall
#cgo LDFLAGS: -L. -lmlpack -lgo_util
#include <stdlib.h>
#include <stdio.h>
#include <capi/cli_util.h>
#include <capi/arma_util.h>
*/
import "C"

import (
	// "fmt"
	"runtime"
	"gonum.org/v1/gonum/mat"
	"unsafe"
	"time"
	// "reflect"
)

type MLPACK_Arma struct {
	mem unsafe.Pointer
}

// Function alloc allocates a C memory Pointer via cgo and registers the finalizer
// in order to free the C memory once the input has been registered in Go.
func (m *MLPACK_Arma) allocArmaMatPtr(identifier string) {
	m.mem = C.MLPACK_ArmaPtr(C.CString(identifier))
	runtime.SetFinalizer(m, freeMatrix)
}

// Function alloc allocates a C memory Pointer via cgo and registers the finalizer
// in order to free the C memory once the input has been registered in Go.
func (m *MLPACK_Arma) allocArmaRowPtr(identifier string) {
	m.mem = C.MLPACK_ArmaRowPtr(C.CString(identifier))
	runtime.SetFinalizer(m, freeMatrix)
}

// Function free is used to free memory when the object leaves Go's scope.
func freeMatrix(m *MLPACK_Arma) {
	C.free(unsafe.Pointer(m.mem))
}

// GonumToArma passes a gonum matrix to C by using it's gonums underlying blas64.
func GonumToArmaMat(identifier string, m *mat.Dense) {
	// Get matrix dimension, underlying blas64General matrix, and data.
	r, c := m.Dims()
	blas64General := m.RawMatrix()
	data := blas64General.Data

	// Pass pointer of the underlying matrix to Mlpack.
	ptr := unsafe.Pointer(&data[0])
	C.MLPACK_ToArma(C.CString(identifier), (*C.double)(ptr), C.int(c), C.int(r))
}

// GonumToArma passes a gonum matrix to C by using it's gonums underlying blas64.
func GonumToArmaRow(identifier string, m *mat.VecDense) {
	// Get matrix dimension, underlying blas64General matrix, and data.
	r, c := m.Dims()
	blas64 := m.RawVector()
	data := blas64.Data

	// Pass pointer of the underlying matrix to Mlpack.
	ptr := unsafe.Pointer(&data[0])
	C.MLPACK_ToArma(C.CString(identifier), (*C.double)(ptr), C.int(c), C.int(r))
}

// GonumToArma passes a gonum matrix to C by using it's gonums underlying blas64.
func GonumToArmaCol(identifier string, m *mat.Dense) {
	// Get matrix dimension, underlying blas64General matrix, and data.
	r, c := m.Dims()
	blas64General := m.RawMatrix()
	data := blas64General.Data

	// Pass pointer of the underlying matrix to Mlpack.
	ptr := unsafe.Pointer(&data[0])
	C.MLPACK_ToArma(C.CString(identifier), (*C.double)(ptr), C.int(c), C.int(r))
}

// ArmaToGonum returns a gonum matrix based on the memory pointer
// of an armadillo matrix.
func (m *MLPACK_Arma) ArmaToGonumMat(identifier string) *mat.Dense {
	// Armadillo row and col
	c := int(C.MLPACK_NumRows(C.CString(identifier)))
	r := int(C.MLPACK_NumCols(C.CString(identifier)))
	e := int(C.MLPACK_NumElems(C.CString(identifier)))

	// Allocate Go memory pointer to the armadillo matrix.
	m.allocArmaMatPtr(identifier)
 	time.Sleep(time.Second)

	// Convert pointer to slice of data, to then pass it to a gonum matrix.
	array := (*[1<<30 - 1]float64)(m.mem)
	data := array[:e]

	// Initialize result matrix.
	output := mat.NewDense(r, c, data)

	runtime.GC()
	time.Sleep(time.Second)

	// Return gonum matrix.
	return output
}

// ArmaRowToGonum returns a gonum vector based on the memory pointer
// of the underlying armadillo object.
func (m *MLPACK_Arma) ArmaToGonumRow(identifier string) *mat.VecDense {
	// Armadillo row and col
	e := int(C.MLPACK_NumElemsRow(C.CString(identifier)))

	// Allocate Go memory pointer to the armadillo matrix.
	m.allocArmaRowPtr(identifier)

	time.Sleep(time.Second)
	// runtime.GC()

	// Convert pointer to slice of data, to then pass it to a gonum matrix.
	array := (*[1<<30 - 1]float64)(m.mem)
	data := array[:e]

	runtime.GC()
	time.Sleep(time.Second)

	// Initialize result matrix.
	output := mat.NewVecDense(e, data)

	// Return gonum vector.
	return output
}

// GonumToArma passes a gonum matrix to C by using it's gonums underlying blas64.
func ArmaToGonumCol(identifier string, m *mat.Dense) {
	// Get matrix dimension, underlying blas64General matrix, and data.
	r, c := m.Dims()
	blas64 := m.RawMatrix()
	data := blas64.Data

	// Pass pointer of the underlying matrix to Mlpack.
	ptr := unsafe.Pointer(&data[0])
	C.MLPACK_ToArma(C.CString(identifier), (*C.double)(ptr), C.int(c), C.int(r))
}
