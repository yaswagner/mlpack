package main

import (
  "fmt"
  //"gonum.org/v1/gonum/mat"
  mlpack "mlpack/build/src/mlpack/bindings/go/mlpack"
)

func main() {
    //testRunBindingNoFlag()
    // testRunBindingCorrectly()
    // testRunBindingWrongString()
    // testRunBindingWrongInt()
    // testRunBindingWrongDouble()
    testRunBadFlag()
}

func testRunBindingNoFlag() {
  param := mlpack.InitializeTest_go_binding()
  param.Copy_all_inputs = true
  d := 4.0
  i := 12
  s := "hello"
  double_out, int_out, _, _, _, _, string_out, _, _ := mlpack.Test_go_binding(d, i, s, param)

  if double_out == 5.0 {
    fmt.Println("error double_out: %v", double_out)
  }
  if int_out == 13 {
    fmt.Println("error int_out %v", int_out)
  }
  if string_out == "hello2" {
    fmt.Println("error string %v", string_out)
  }
}

func testRunBindingCorrectly()  {
  param := mlpack.InitializeTest_go_binding()
  param.Copy_all_inputs = true
  param.Flag1 = true
  d := 4.0
  i := 12
  s := "hello"
  double_out, int_out, _, _, _, _, string_out, _, _ := mlpack.Test_go_binding(d, i, s, param)

  if double_out != 5.0 {
    fmt.Println("error double %v", double_out)
  }

  if int_out != 13 {
    fmt.Println("error int %v", int_out)
  }

  if string_out != "hello2" {
    fmt.Println("error string %v", string_out)
  }
}

func testRunBindingWrongString() {
  param := mlpack.InitializeTest_go_binding()
  param.Flag1 = true
  d := 4.0
  i := 12
  s := "goodbye"
  _, _, _, _, _, _, string_out, _, _ := mlpack.Test_go_binding(d, i, s, param)

  if string_out == "hello2" {
    fmt.Println("error string %v", string_out)
  }
}

func testRunBindingWrongInt()  {
  param := mlpack.InitializeTest_go_binding()
  param.Flag1 = true
  d := 4.0
  i := 15
  s := "hello"
  _, int_out, _, _, _, _, _, _, _ := mlpack.Test_go_binding(d, i, s, param)

  if int_out == 13 {
    fmt.Println("error string %v", int_out)
  }
}

func testRunBindingWrongDouble() {
  param := mlpack.InitializeTest_go_binding()
  param.Flag1 = true
  d := 2.0
  i := 12
  s := "hello"
  double_out, _, _, _, _, _, _, _, _ := mlpack.Test_go_binding(d, i, s, param)

  if double_out == 5.0 {
    fmt.Println("error string %v", double_out)
  }
}

func testRunBadFlag() {
  param := mlpack.InitializeTest_go_binding()
  param.Flag1 = true
  param.Flag2 = true
  d := 2.0
  i := 12
  s := "hello"
  double_out, int_out, _, _, _, _, string_out, _, _ := mlpack.Test_go_binding(d, i, s, param)

  if double_out == 5.0 {
    fmt.Println("error double_out: %v", double_out)
  }
  if int_out == 13 {
    fmt.Println("error int_out %v", int_out)
  }
  if string_out == "hello2" {
    fmt.Println("error string %v", string_out)
  }
}

func testMatrixForceCopy() {
  param := mlpack.InitializeTest_go_binding()
  param.Copy_all_inputs = true
  param.Flag1 = true
  param.Flag2 = true
  d := 2.0
  i := 12
  s := "hello"
  double_out, int_out, _, _, _, _, string_out, _, _ := mlpack.Test_go_binding(d, i, s, param)

  if double_out == 5.0 {
    fmt.Println("error double_out: %v", double_out)
  }
  if int_out == 13 {
    fmt.Println("error int_out %v", int_out)
  }
  if string_out == "hello2" {
    fmt.Println("error string %v", string_out)
  }
}
