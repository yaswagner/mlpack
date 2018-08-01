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

/**
 * Given a list of parameter definition and program documentation, print a
 * generated .h file to stdout.
 *
 * @param parameters List of parameters the program will use (from CLI).
 * @param programInfo Documentation for the program.
 * @param functionName Name of the function (i.e. "pca").
 */
void PrintH(const util::ProgramDoc& programInfo,
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

  // First, we must generate the header comment and namespace.
  cout << "#include <stdint.h>" << endl;
  cout << "#include <stddef.h>" << endl;
  cout << endl;
  cout << "#if defined(__cplusplus) || defined(c_plusplus)" << endl;
  cout << "extern \"C\" {" << endl;
  cout << "#endif" << endl;
  cout << endl;

  // Then we must print any class definitions if needed.
  // Print any extra class definitions we might need.
  for (ParamIter it = parameters.begin(); it != parameters.end(); ++it)
  {
    const util::ParamData& d = it->second;
    if (d.input)
      CLI::GetSingleton().functionMap[d.tname]["PrintClassDefnH"](d, NULL, NULL);
  }

  // Finally, we generate the wrapper for mlpackMain()
  cout << "extern void MLPACK_" << functionName << "();" << endl;
  cout << endl;
  cout << "#if defined(__cplusplus) || defined(c_plusplus)" << endl;
  cout << "}" << endl;
  cout << "#endif" << endl;
}

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
  cout << "#include <mlpack/core/util/cli_util.h>" << endl;
  cout << "#include <mlpack/core/util/arma_util.h>" << endl;
  cout << "#include <mlpack/bindings/go/" << functionName << ".h>" << endl;
  cout << " */" << endl;
  cout << "import \"C\" " << endl;
  cout << endl;

  cout << "import (" << endl;
  cout << " \"gonum.org/v1/gonum/mat\" " << endl;
  cout << ")" << endl;
  cout << endl;


  // Print Go method configuration struct
  for (ParamIter it = parameters.begin(); it != parameters.end(); ++it)
  {
    const util::ParamData& d = it->second;
    if (d.input)
      CLI::GetSingleton().functionMap[d.tname]["PrintConfigStruct"](d, NULL, NULL);
  }

  // // Print any class definitions we need to have.
  // std::set<std::string> classes;
  // for (ParamIter it = parameters.begin(); it != parameters.end(); ++it)
  // {
  //   const util::ParamData& d = it->second;
  //   if (classes.count(d.cppType) == 0)
  //   {
  //     const size_t indent = 2;
  //     CLI::GetSingleton().functionMap[d.tname]["ImportDecl"](d, (void*) &indent,
  //         NULL);
  //
  //     // Make sure we don't double-print the definition.
  //     classes.insert(d.cppType);
  //   }
  // }
  //
  // cout << endl;

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
  cout << "func " << functionName << "(";
  // size_t indent = 4 /* 'def ' */ + functionName.size() + 1 /* '(' */;
  // for (size_t i = 0; i < inputOptions.size(); ++i)
  // {
  //   const util::ParamData& d = parameters.at(inputOptions[i]);
  //
  //   if (i != 0)
  //     cout << "," << endl << std::string(indent, ' ');
  //
  //   CLI::GetSingleton().functionMap[d.tname]["PrintDefn"](d, NULL, NULL);
  // }

  // Print closing brace for function definition.
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
  cout << "  if p.Copy_all_inputs == true {" << endl;
  cout << "    SetParamBool(\"copy_all_inputs\", p.Copy_all_inputs)" << endl;
  cout << "    SetPassed(\"copy_all_inputs\")" << endl;
  cout << "" << endl;

  // // Do any input processing.
  // for (size_t i = 0; i < inputOptions.size(); ++i)
  // {
  //   const util::ParamData& d = parameters.at(inputOptions[i]);
  //
  //   size_t indent = 2;
  //   CLI::GetSingleton().functionMap[d.tname]["PrintInputProcessing"](d,
  //       (void*) &indent, NULL);
  // }

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

  // Do any output processing and return.
  cout << "  // Initialize result variable and get output." << endl;
  // cout << "  var result MLPACK_" << << endl;
  // cout << endl;
  //
  // for (size_t i = 0; i < outputOptions.size(); ++i)
  // {
  //   const util::ParamData& d = parameters.at(outputOptions[i]);
  //
  //   std::tuple<size_t, bool> t = std::make_tuple(2, false);
  //   CLI::GetSingleton().functionMap[d.tname]["PrintOutputProcessing"](d,
  //       (void*) &t, NULL);
  // }

  // Clear the parameters.
  cout << endl;
  cout << "  ClearSettings()" << endl;
  cout << endl;

  cout << "  return result" << endl;
  cout << "" << endl;
}

} // namespace go
} // namespace bindings
} // namespace mlpack
