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

class CallbackHandler {
public:
	CallbackHandler() {
	}
	virtual ~CallbackHandler() {
	}
	virtual int fileComplete(char* filePath);
	virtual int packComplete(char* filePath);
	virtual int estimateFileComplete(int fileID);
};

/*
 * @class Directory
 * Each Directory entry takes up the bytes
 * 8 bytes = file CRC64
 * 8 bytes = file start position (byte)
 * 8 bytes = file length (byte)
 * 8 bytes = insert time
 * 8 bytes = file type (8 digit ascii)
 * 32 bytes = file handle (32 digit ascii)
 * 58 bytes = custom
 * 128 bytes total
 */
class Directory {
private:
	class Entry {
	private:

	};
	unsigned long long filePosCurrent;
	unsigned long long filePosNew;
	unsigned long long fileLenCurrent;
	unsigned long long fileLenNew;
};

class Asset {
private:
	bool fileExist;
	bool fileWritten;
	unsigned long long filePosCurrent;
	unsigned long long filePosNew;
	unsigned long long fileLenCurrent;
	unsigned long long fileLenNew;
	std::string handle;
	std::string path;
	std::string inType;
	std::string outType;
public:
	Asset(std::string handle_, std::string filePath_, std::string inType_,
			std::string outType_);
	std::string getPath();
	void setExist(bool flag);
};

class ResourceFile {
private:
	Directory directory;
	std::vector<Asset*> assetList;
public:
	ResourceFile();
	virtual ~ResourceFile() {
	}
	void addFile(std::string handle, std::string filePath, std::string inType,
			std::string outType);
	unsigned int assetListSize();
	Asset* asset(unsigned int assetID);
};

class Parser {
public:
	Parser() {

	}
	virtual ~Parser() {
	}
	static int readDirectoryJSON(std::fstream& resourceFile,
			ResourceFile& directoryObj, unsigned long long& sizeCurrent,
			unsigned long long& sizeTotal);
	static int readDirectory(std::fstream& resourceFile,
			ResourceFile& directoryObj, unsigned long long& sizeCurrent,
			unsigned long long& sizeTotal);
	static int estimate(Asset& assetObj, unsigned long long& sizeCurrent,
			unsigned long long& sizeTotal);
	static int writeDirectory(std::fstream& resourceFile,
			ResourceFile& directoryObj, unsigned long long& sizeCurrent,
			unsigned long long& sizeTotal);
	static int insertAsset(std::fstream& resourceFile, Asset& assetObj,
			unsigned long long& sizeCurrent, unsigned long long& sizeTotal);
	static int removeAsset(std::fstream& resourceFile, Asset& assetObj,
			unsigned long long& sizeCurrent, unsigned long long& sizeTotal);
};

class Stream {
public:
	Stream();
	~Stream();
};

class Loader {
	ResourceFile resourceFileObj;
public:
	Loader();
	virtual ~Loader() {
	}
	void info(std::string fileName);
};

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
