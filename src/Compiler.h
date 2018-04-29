#ifndef COMPILER_H
#define COMPILER_H

#include <iostream>
#include <string>
#include <fstream>
#include "../contrib/json.hpp"
#include "CallbackHandler.h"

namespace ResourceFileUtility {

typedef int (*CBintString)(char* text);

class Compiler {
public:
	CBintString callbackFileComplete;
	CBintString callbackPackComplete;
	ResourceFileUtility::CallbackHandler* callbackHandlerPtr;
	Compiler();
	~Compiler();
	void info(std::string fileName);
	void pack(std::string fileName);
	void setCallbackFileComplete(CBintString handler_);
	void setCallbackPackComplete(CBintString handler_);
	void setCallback(CallbackHandler* handler_);
};

}

#endif
