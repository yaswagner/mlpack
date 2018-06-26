#include "mlpack/core/util/cli.hpp"
#include "mlpack/core/util/cli_impl.hpp"
#include "cli_util.h"
#include "cli_util.hpp"
#include <list>
#include <iostream>
#include <map>
#include <string>

#include <boost/any.hpp>

#include <mlpack/prereqs.hpp>

#include "timers.hpp"
#include "program_doc.hpp"
#include "version.hpp"

#include "param_data.hpp"

namespace mlpack {

extern "C" void C_ResetTimers()
{
  CLI::GetSingleton().timer.Reset();
}

extern "C" void C_EnableTimers()
{
  Timer::EnableTiming();
}

extern "C" void C_DisableBacktrace()
{
  Log::Fatal.backtrace = false;
}

extern "C" void C_EnableVerbose()
{
  Log::Info.ignoreInput = false;
}

extern "C" void C_DisableVerbose()
{
  Log::Info.ignoreInput = true;
}

extern "C" void C_ClearSettings()
{
  CLI::ClearSettings();
}

extern "C" void C_SetPassed(const char* name)
{
  CLI::SetPassed(name);
}

extern "C" void C_RestoreSettings(const char *name)
{
  CLI::RestoreSettings(name);
}

extern "C" void C_SetParamDouble(const char *identifier, double value)
{
  util::SetParam(identifier, value);
}

extern "C" void C_SetParamInt(const char *identifier, int value)
{
  util::SetParam(identifier, value);
}

extern "C" void C_SetParamFloat(const char *identifier, float value)
{
  util::SetParam(identifier, value);
}

extern "C" void C_SetParamBool(const char *identifier, bool value)
{
  util::SetParam(identifier, value);
}

extern "C" void C_SetParamString(const char *identifier, const char *value)
{
  util::SetParam(identifier, value);
}

extern "C" void C_SetParamMat(const char *identifier, const MatrixInput *m)
{
  util::SetParam(identifier, m);
}

} // namespace mlpack
