#include "cli.hpp"
#include "cli_impl.hpp"
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

extern "C" void MLPACK_ResetTimers()
{
  CLI::GetSingleton().timer.Reset();
}

extern "C" void MLPACK_EnableTimers()
{
  Timer::EnableTiming();
}

extern "C" void MLPACK_DisableBacktrace()
{
  Log::Fatal.backtrace = false;
}

extern "C" void MLPACK_EnableVerbose()
{
  Log::Info.ignoreInput = false;
}

extern "C" void MLPACK_DisableVerbose()
{
  Log::Info.ignoreInput = true;
}

extern "C" void MLPACK_ClearSettings()
{
  CLI::ClearSettings();
}

extern "C" void MLPACK_SetPassed(const char *name)
{
  CLI::SetPassed(name);
}

extern "C" void MLPACK_RestoreSettings(const char *name)
{
  CLI::RestoreSettings(name);
}

extern "C" void MLPACK_SetParamDouble(const char *identifier, double value)
{
  util::SetParam(identifier, value);
}

extern "C" void MLPACK_SetParamInt(const char *identifier, int value)
{
  util::SetParam(identifier, value);
}

extern "C" void MLPACK_SetParamFloat(const char *identifier, float value)
{
  util::SetParam(identifier, value);
}

extern "C" void MLPACK_SetParamBool(const char *identifier, bool value)
{
  util::SetParam(identifier, value);
}

extern "C" void MLPACK_SetParamString(const char *identifier, const char *value)
{
  std::string val;
  val.assign(value);
  util::SetParam(identifier, val);
}

extern "C" void MLPACK_SetParamPtr(const char *identifier, const double *ptr, const bool copy)
{
  util::SetParamPtr(identifier, ptr, copy);
}

extern "C" bool MLPACK_HasParam(const char *identifier)
{
  return CLI::HasParam(identifier);
}

} // namespace mlpack
