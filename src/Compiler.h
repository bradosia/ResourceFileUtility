#ifndef COMPILER_H
#define COMPILER_H

#define __cplusplus 201103L
#define _GLIBCXX_USE_C99 1
//#define _GLIBCXX_USE_WCHAR_T 1
//#define _GLIBCXX_HAVE_WCSTOF 1
//#undef _GLIBCXX_HAVE_BROKEN_VSWPRINTF
//#define _GLIBCXX_HAVE_WCHAR_H 1
//#define __ANDROID_API__ 21

#include <iostream>
#include <string>
#include <fstream>
#include "../contrib/json.hpp"
#include "CallbackHandler.h"
#include "ResourceFile.h"

namespace ResourceFileUtility {

typedef int (*CBintString)(char* text);

class Compiler {
private:
	ResourceFile resourceFileObj;
	CBintString callbackFileComplete;
	CBintString callbackPackComplete;
	ResourceFileUtility::CallbackHandler* callbackHandlerPtr;
	int metaDirectorySize;
	/* reads current resource file directory and attempts to append new files and delete old ones.
	 * An entire recompile will be triggered if new directory size > old directory size */
	bool tryToUpdate;
public:
	Compiler();
	virtual ~Compiler() {
	}
	void info(std::string fileName);
	void packEstimate(unsigned long long& sizeCurrent,
			unsigned long long& sizeTotal);
	void pack(std::string fileName);
	Asset resourceFileGetFile(int fileID);
	void setCallbackFileComplete(CBintString handler_);
	void setCallbackPackComplete(CBintString handler_);
	void setCallback(CallbackHandler* handler_);
};

}

#endif
