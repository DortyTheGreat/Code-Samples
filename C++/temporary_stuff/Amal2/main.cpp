/*
The Heady library is distributed under the MIT License (MIT)
https://opensource.org/licenses/MIT
See LICENSE.TXT or Heady.h for license details.
Copyright (c) 2018 James Boer
*/

#include <iostream>
#include <thread>
#include <cstring>
#include "clara.hpp"

#include "Heady.hpp"
using namespace clara;

int main(int argc, char ** argv)
{
	// Handle command-line options
	std::string source;
	std::string excluded;
	std::string inlined = "inline_t";
	std::string define;
	std::string output;
	bool recursive = false;
	bool showHelp = false;
	auto parser =
		Opt(source, "folder")["-s"]["--source"]("folder containing source files") |
		Opt(excluded, "files")["-e"]["--excluded"]("exclude specific files") |
		Opt(inlined, "name")["-i"]["--inline"]("inline macro substitution") |
		Opt(define, "define")["-d"]["--define"]("define for almagamated header") |
		Opt(output, "file")["-o"]["--output"]("generated header file") |
		Opt(recursive)["-r"]["--recursive"]("recursively scan source folder") |
		Help(showHelp)
		;

	auto result = parser.parse(Args(argc, argv));
	if (!result)
	{
		std::cerr << "Error in command line: " << result.errorMessage() << std::endl;
		return 1;
	}
	else if (showHelp)
	{
		std::cout << "Heady version " << Heady::GetVersionString() << " Copyright (c) James Boer\n\n";
		parser.writeToStream(std::cout);
		std::cout <<
			"\nExample usage:" <<
			"\nHeady --source \"Source\" --exluded \"Main.cpp clara.hpp\" --inline \"inline_t\" --output \"Include/Heady.hpp\"\n";
		return 0;
	}
	else if (source.empty() || output.empty())
	{
		std::cerr << "Error: Valid source and output are required.\n\n";
		parser.writeToStream(std::cerr);
		std::cerr <<
			"\nExample usage:" <<
			"\nHeady --source \"Source\" --exluded \"Main.cpp clara.hpp\" --inline \"inline_t\" --output \"Include/Heady.hpp\"\n";
		return 1;
	}

	// Generate a combined header file from all C++ source files
	try
	{
		Heady::Params params;
		params.sourceFolder = source;
		params.output = output;
		params.excluded = excluded;
		params.inlined = inlined;
		params.define = define;
		params.recursiveScan = recursive;
		Heady::GenerateHeader(params);
	}
	catch (const std::exception & e)
	{
		std::cerr << "Error processing source files.  " << e.what() << std::endl;
		return 1;
	}

	return 0;
}

