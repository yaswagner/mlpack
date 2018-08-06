/**
 * @file print_go.cpp
 * @author Yasmine Dumouchel
 *
 * Implementation of function to generate a .go file given a list of parameters
 * for the function.
 *
 * mlpack is free software; you may redistribute it and/or modify it under the
 * terms of the 3-clause BSD license.  You should have received a copy of the
 * 3-clause BSD license along with mlpack.  If not, see
 * http://www.opensource.org/licenses/BSD-3-Clause for more information.
 */
#include "print_cpp.hpp"
#include <mlpack/core/util/cli.hpp>
#include <mlpack/core/util/hyphenate_string.hpp>
#include <set>

using namespace mlpack::util;
using namespace std;

namespace mlpack {
namespace bindings {
namespace go {

/**
 * Given a list of parameter definition and program documentation, print a
 * generated .cpp file to stdout.
 *
 * @param parameters List of parameters the program will use (from CLI).
 * @param programInfo Documentation for the program.
 * @param functionName Name of the function (i.e. "pca").
 */
void PrintCPP(const ProgramDoc& programInfo,
              const string& functionName)
{
  // Restore parameters.
  CLI::RestoreSettings(programInfo.programName);

  const std::map<std::string, util::ParamData>& parameters = CLI::Parameters();
  typedef std::map<std::string, util::ParamData>::const_iterator ParamIter;

  // Split into input and output parameters.  Take two passes on the input
  // parameters, so that we get the required ones first.
  vector<string> inputOptions, outputOptions;
  for (ParamIter it = parameters.begin(); it != parameters.end(); ++it)
  {
    const util::ParamData& d = it->second;
    if (d.input && d.required)
    {
      // Ignore some parameters.
      if (d.name != "help" && d.name != "info" &&
          d.name != "version")
        inputOptions.push_back(it->first);
    }
    else if (!d.input)
    {
      outputOptions.push_back(it->first);
    }
  }

  for (ParamIter it = parameters.begin(); it != parameters.end(); ++it)
  {
    const util::ParamData& d = it->second;
    if (d.input && !d.required &&
        d.name != "help" && d.name != "info" &&
        d.name != "version")
      inputOptions.push_back(it->first);
  }

  // First, we must generate the header comment and namespace.
  cout << "#include \"" << functionName << "_impl.hpp\""<< endl;
  cout << "#include \"" << functionName << ".hpp\""<< endl;
  cout << "#include \"" << functionName << ".h\""<< endl;
  cout << "#include \"" << functionName << "_main.cpp\""<< endl;
  cout << "#include <mlpack/methods/" << functionName << "/"
        << functionName << ".hpp>" <<endl;
  cout << "#include <mlpack/methods/" << functionName << "/"
        << functionName << "_main.cpp>" <<endl;
  cout << "#include <mlpack/core/util/cli_util.hpp>" << endl;
  cout << endl;
  cout << "namespace mlpack {" << endl;
  cout << endl;

  // Then we must print any class definitions if needed.
  // Print any extra class definitions we might need.
  for (ParamIter it = parameters.begin(); it != parameters.end(); ++it)
  {
    const util::ParamData& d = it->second;
    if (d.input)
      CLI::GetSingleton().functionMap[d.tname]["PrintClassDefnCPP"](d, NULL, NULL);
  }

  // Finally, we generate the wrapper for mlpackMain()
  cout << "static void " << functionName << "_mlpackMain()" << endl;
  cout << "{" << endl;
  cout << "  " << "mlpackMain();" << endl;
  cout << "}" << endl;
  cout << endl;
  cout << "extern \"C\" void MLPACK_" << functionName << "()" << endl;
  cout << "{" << endl;
  cout << "  " << functionName << "_mlpackMain();" << endl;
  cout << "}" << endl;

  // Closing bracket for namespace mlpack.
  cout << endl;
  cout << "} // namespace mlpack" << endl;
  cout << endl;
}

} // namespace go
} // namespace bindings
} // namespace mlpack
