#ifndef CALLBACK_HANDLER_H
#define CALLBACK_HANDLER_H

#include <iostream>
#include <string>
#include <fstream>

namespace ResourceFileUtility {

class CallbackHandler {
public:
	CallbackHandler();
	virtual ~CallbackHandler();
	virtual void fileComplete(std::string filePath);
	virtual void packComplete();
};

}

#endif
