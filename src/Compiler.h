/*
 * ResourceFileUtility
 * By: Brad Lee
 */
#ifndef COMPILER_H
#define COMPILER_H

#define __cplusplus 201103L
#define _GLIBCXX_USE_C99 1
//#define _GLIBCXX_USE_WCHAR_T 1
//#define _GLIBCXX_HAVE_WCSTOF 1
//#undef _GLIBCXX_HAVE_BROKEN_VSWPRINTF
//#define _GLIBCXX_HAVE_WCHAR_H 1

#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include "../contrib/json.hpp"
#include "CallbackHandler.h"
#include "ResourceFile.h"
#include "mingw_threads.h"

namespace ResourceFileUtility {

class ResourceFile;
class Asset;
typedef int (*CBintString)(char* text);
typedef void (*CBvoidResourceFile)(ResourceFile* resourceFilePtr);

class Compiler {
private:
	ResourceFile resourceFileObj;
	CBintString callbackFileComplete;
	CBintString callbackPackComplete;
	ResourceFileUtility::CallbackHandler* callbackHandlerPtr;
	std::vector<std::thread*> estimateThreadList;
	int metaDirectorySize;
	/* reads current resource file directory and attempts to append new files and delete old ones.
	 * An entire recompile will be triggered if new directory size > old directory size */
	bool tryToUpdate;
public:
	Compiler();
	virtual ~Compiler() {
	}
	void info(std::string fileName);
	void estimate();
	void estimate(CBvoidResourceFile handler_);
	void pack(std::string fileName);
	void pack(std::string fileName, CBvoidResourceFile handler_);
	Asset resourceFileGetFile(int fileID);
	void setCallbackFileComplete(CBintString handler_);
	void setCallbackPackComplete(CBintString handler_);
	void setCallback(CallbackHandler* handler_);
	ResourceFile* getResourceFile();
};

}

#endif
