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
#include "print_go.hpp"
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
 * generated .go file to stdout.
 *
 * @param parameters List of parameters the program will use (from CLI).
 * @param programInfo Documentation for the program.
 * @param functionName Name of the function (i.e. "pca").
 */
void PrintGo(const util::ProgramDoc& programInfo,
              const std::string& functionName)
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

  // First, we must generate the header comment.

  // Now import all the necessary packages.
  cout << "package mlpack" << endl;
  cout << endl;
  cout << "/*" << endl;
  cout << "#cgo CFLAGS: -I. -g -Wall" << endl;
  cout << "#cgo LDFLAGS: -L/usr/local/lib -lm -L/usr/local/lib/ "
        << "-lmlpack -lmlpack_go_" << functionName << endl;
  cout << "#include <" << functionName << ".h>" << endl;
  cout << " */" << endl;
  cout << "import \"C\" " << endl;
  cout << endl;

  cout << "import (" << endl;
  cout << "  " << "\"gonum.org/v1/gonum/mat\" " << endl;
  cout << ")" << endl;
  cout << endl;


  // Print Go method configuration struct
  std::string goFunctionName = functionName;
  goFunctionName[0] = std::toupper(goFunctionName[0]);

  cout << "type " << goFunctionName << "OptionalParam struct {"
      << std::endl;
  for (size_t i = 0; i < inputOptions.size(); ++i)
  {
    const util::ParamData& d = parameters.at(inputOptions[i]);
    size_t indent = 2;
    CLI::GetSingleton().functionMap[d.tname]["PrintMethodConfig"](d,
        (void*) &indent, NULL);

  }
  cout << "}" << endl;
  cout << endl;

  // Print Go method configurate struct initialization
  cout << "func Initialize" << goFunctionName << "() *"
      << goFunctionName << "OptionalParam {"
      << endl;
  cout << "  " << "return &" << goFunctionName << "OptionalParam{" << endl;
  for (size_t i = 0; i < inputOptions.size(); ++i)
  {
    const util::ParamData& d = parameters.at(inputOptions[i]);
    size_t indent = 4;
    CLI::GetSingleton().functionMap[d.tname]["PrintMethodInit"](d,
        (void*) &indent, NULL);

  }
  cout << "  " << "}" << endl;
  cout << "}" << endl;
  cout << endl;

  // Print any extra class definitions we might need.
  for (ParamIter it = parameters.begin(); it != parameters.end(); ++it)
  {
    const util::ParamData& d = it->second;
    if (d.input)
      CLI::GetSingleton().functionMap[d.tname]["PrintClassDefnGo"](d, NULL, NULL);
  }

  // Print the comment describing the function and its parameters.
  cout << "/*" << endl;
  cout << "  " << HyphenateString(programInfo.documentation(), 2) << endl;
  cout << endl << endl;
  cout << "  Input parameters:" << endl;
  cout << endl;
  for (size_t i = 0; i < inputOptions.size(); ++i)
  {
    const util::ParamData& d = parameters.at(inputOptions[i]);

    cout << "  ";
    size_t indent = 4;
    CLI::GetSingleton().functionMap[d.tname]["PrintDoc"](d, (void*) &indent,
        NULL);
    cout << endl;
  }
  cout << endl;
  cout << "  Output parameters:" << endl;
  cout << endl;
  for (size_t i = 0; i < outputOptions.size(); ++i)
  {
    const util::ParamData& d = parameters.at(outputOptions[i]);

    cout << "  ";
    size_t indent = 4;
    CLI::GetSingleton().functionMap[d.tname]["PrintDoc"](d, (void*) &indent,
        NULL);
    cout << endl;
  }
  cout << endl;
  cout <<  "*/" << endl;


  // Print the function definition.
  cout << "func " << goFunctionName << "(";
  size_t counter = 0;
  size_t indent = 4 /* 'def ' */ + functionName.size() + 1 /* '(' */;
  for (size_t i = 0; i < inputOptions.size(); ++i)
  {
    const util::ParamData& d = parameters.at(inputOptions[i]);
    if (d.required)
    {
      if (i != 0)
        cout << "," << endl << std::string(indent, ' ');

      CLI::GetSingleton().functionMap[d.tname]["PrintDefnInput"](d, NULL, NULL);
      counter++;
    }

  }
  if (counter == 0)
  {
    cout << "param *" << goFunctionName << "OptionalParam) (";
  }
  else
  {
      cout << ", param *" << goFunctionName << "OptionalParam) (";
  }

  // Print output variables
  for (size_t i = 0; i < outputOptions.size(); ++i)
  {
    const util::ParamData& d = parameters.at(outputOptions[i]);

    if (i != 0)
      cout << ", ";

    std::tuple<size_t, bool> t = std::make_tuple(2, false);
    CLI::GetSingleton().functionMap[d.tname]["PrintDefnOutput"](d,
        (void*) &t, NULL);
  }

  // Print opening brace for function definition.
  cout << ") {" << endl;

  // Reset any timers and disable backtraces.
  cout << "  ResetTimers()" << endl;
  cout << "  EnableTimers()" << endl;
  cout << "  DisableBacktrace()" << endl;
  cout << "  DisableVerbose()" << endl;

  // Restore the parameters.
  cout << "  RestoreSettings(\"" << programInfo.programName << "\")"
      << endl;
  cout << endl;

  // Determine whether or not we need to copy parameters.
  cout << "   // Detect if the parameter was passed; set if so." << endl;
  cout << "  if param.Copy_all_inputs == true {" << endl;
  cout << "    SetParamBool(\"copy_all_inputs\", param.Copy_all_inputs)" << endl;
  cout << "    SetPassed(\"copy_all_inputs\")" << endl;
  cout << "  }" << endl;
  cout << endl;

  // Do any input processing.
  for (size_t i = 0; i < inputOptions.size(); ++i)
  {
    const util::ParamData& d = parameters.at(inputOptions[i]);

    size_t indent = 2;
    CLI::GetSingleton().functionMap[d.tname]["PrintInputProcessing"](d,
        (void*) &indent, NULL);
  }

  // Set all output options as passed.
  cout << "  // Mark all output options as passed." << endl;
  for (size_t i = 0; i < outputOptions.size(); ++i)
  {
    const util::ParamData& d = parameters.at(outputOptions[i]);
    cout << "  SetPassed(\"" << d.name << "\")" << endl;
  }
  cout << "" << endl;

  // Call the method.
  cout << "  // Call the mlpack program." << endl;
  cout << "  C.MLPACK_" << functionName << "()" << endl;
  cout << endl;

  // Do any output processing and return.
  cout << "  // Initialize result variable and get output." << endl;

  for (size_t i = 0; i < outputOptions.size(); ++i)
  {
    const util::ParamData& d = parameters.at(outputOptions[i]);

    CLI::GetSingleton().functionMap[d.tname]["PrintOutputProcessing"](d,
        NULL, NULL);
  }

  // Clear the parameters.
  cout << endl;
  cout << "  " << "// Clear settings." << endl;
  cout << "  " << "ClearSettings()" << endl;
  cout << endl;

  // Return output parameters.
  cout << "  " << "// Return output(s)." << endl;
  cout << "  " << "return ";
  for (size_t i = 0; i < outputOptions.size(); ++i)
  {
    if (i != 0)
      cout << ", ";

    const util::ParamData& d = parameters.at(outputOptions[i]);
    cout << d.name;
  }
  cout << endl;

  // Print closing bracket.
  cout << "}" << endl;
}

} // namespace go
} // namespace bindings
} // namespace mlpack
