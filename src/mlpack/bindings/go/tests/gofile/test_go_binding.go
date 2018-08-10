package main

import (
  "fmt"
  //"gonum.org/v1/gonum/mat"
  mlpack "mlpack/build/src/mlpack/bindings/go/mlpack"
)

func main() {
    testRunBindingNoFlag()
}

func testRunBindingNoFlag() {
  param := mlpack.InitializeTest_go_binding();
  d := 4.0
  var i int32 = 2
  s := "hello"
  double_out, int_out, _, _, _, _, string_out,  _, _ := mlpack.Test_go_binding(d, i, s, param)

  if double_out != 5.0 {
    fmt.Println("error double")
  }

  if int_out != 13 {
    fmt.Println("error int")
  }

  if string_out != "hello2" {
    fmt.Println("error string")
  }
}
