/*
 * ResourceFileUtility
 * By: Brad Lee
 */
#ifndef RESOURCE_FILE_H
#define RESOURCE_FILE_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include "../contrib/json.hpp"
#include "crc64.h"

namespace ResourceFileUtility {

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
	bool fileExist, fileWritten, fileProcessing;
	unsigned long long filePosCurrent, filePosNew, fileLenCurrent, fileLenNew,
			processBytes, fileBytes, fileReadBytesLast;
	std::chrono::microseconds processTime, fileReadTimeLast,
			fileReadTimePerByteLast;
	std::string handle, path, inType, outType;
public:
	Asset();
	Asset(std::string handle_, std::string filePath_, std::string inType_,
			std::string outType_);
	void init();
	std::string getPath();
	void setExist(bool flag);
	void setProcess(bool flag);
	bool getProcess();
	unsigned long long getProcessBytes();
	unsigned long long getFileBytes();
	void setProcessBytes(unsigned long long val);
	void setFileBytes(unsigned long long val);
	void setProcessTime(std::chrono::microseconds val);
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
	unsigned long long sizePending();
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
	static int estimate(Asset* assetObj);
	static int writeDirectory(std::fstream& resourceFile,
			ResourceFile& directoryObj, unsigned long long& sizeCurrent,
			unsigned long long& sizeTotal);
	static int insertAsset(std::fstream& resourceFile, Asset& assetObj,
			unsigned long long& sizeCurrent, unsigned long long& sizeTotal);
	static int removeAsset(std::fstream& resourceFile, Asset& assetObj,
			unsigned long long& sizeCurrent, unsigned long long& sizeTotal);
};

}

#endif
