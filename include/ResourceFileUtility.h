/*
 * This is suppose to be a single header include when linking against this library
 * It is basically a copy of source headers in one file
 */

#ifndef RESOURCE_FILE_UTILITY_H
#define RESOURCE_FILE_UTILITY_H

#include <iostream>
#include <string>
#include <fstream>
#include "../contrib/json.hpp"

namespace ResourceFileUtility {

class Compiler {
public:
	int test;
	Compiler();
	~Compiler();
	void info(std::string fileName);
	void pack(std::string fileName);
};

class Loader {
public:
	int test;
	Loader();
	~Loader();
	void info(std::string fileName);
};

class Stream {
public:
	Stream();
	~Stream();
};

class CallbackHandler {
public:
	CallbackHandler();
	virtual ~CallbackHandler();
	virtual void fileComplete(std::string filePath);
	virtual void packComplete();
};

}

#endif
