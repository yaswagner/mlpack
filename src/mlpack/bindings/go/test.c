#include "cli_util.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]){
  C_ResetTimers();
  C_EnableTimers();
  C_DisableBacktrace();
  C_DisableVerbose();
  C_RestoreSettings("Principal Components Analysis");
  C_SetParamBool("copy_all_inputs", true);
  C_SetPassed("copy_all_inputs");
  C_SetParamString("decomposition_method", "exact");
  C_SetPassed("decomposition_method");
  C_SetParamInt("new_dimensionality",5);
  C_SetPassed("new_dimensionality");
  C_SetParamBool("var_to_retain", 50);
  C_SetPassed("var_to_retain");
  C_SetParamBool("scale", true);
  C_SetPassed("scale");
  C_SetParamBool("verbose", true);
  C_SetPassed("verbose");
}
