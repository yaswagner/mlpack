#include "mlpack/core/util/cli_util.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]){
  C_ResetTimers();
  C_EnableTimers();
  C_DisableBacktrace();
  C_DisableVerbose();
  C_RestoreSettings("Principal Components Analysis");
  C_SetParamBool("copy_all_inputs", true);
}
