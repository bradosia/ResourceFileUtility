/*
 * This is suppose to be a single header include when linking against this library
 * It is basically a copy of source headers in one file
 */

#ifndef RESOURCE_FILE_UTILITY_H
#define RESOURCE_FILE_UTILITY_H

#define __cplusplus 201103L
#define _GLIBCXX_USE_C99 1

#include <iostream>
#include <string>
#include <fstream>
#include "../contrib/json.hpp"

namespace ResourceFileUtility {

typedef int (*CBintString)(char* text);

class CallbackHandler {
public:
	CallbackHandler();
	virtual ~CallbackHandler();
	virtual int fileComplete(char* filePath);
	virtual int packComplete(char* filePath);
};

class Compiler {
public:
	CBintString callbackFileComplete;
	CBintString callbackPackComplete;
	Compiler();
	~Compiler();
	void info(std::string fileName);
	void pack(std::string fileName);
	void setCallbackFileComplete(CBintString handler_);
	void setCallbackPackComplete(CBintString handler_);
	void setCallback(CallbackHandler* handler_);
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

}

#endif
