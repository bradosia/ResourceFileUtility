#ifndef RESOURCE_FILE_H
#define RESOURCE_FILE_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "../contrib/json.hpp"

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
};

class ResourceFile {
private:
	Directory directory;
	std::vector<Asset> assetList;
public:
	ResourceFile();
	virtual ~ResourceFile() {
	}
	void addFile(std::string handle, std::string filePath, std::string inType,
			std::string outType) {
		assetList.push_back(Asset(handle, filePath, inType, outType));
	}
};

class Parser {
public:
	Parser() {

	}
	virtual ~Parser() {
	}
	static int readDirectoryJSON(std::fstream resourceFile,
			ResourceFile& directoryObj, unsigned long long& sizeCurrent);
	static int readDirectory(std::fstream resourceFile,
			ResourceFile& directoryObj, unsigned long long& sizeCurrent);
	static int writeDirectory(std::fstream resourceFile,
			ResourceFile& directoryObj, unsigned long long& sizeCurrent);
	static int insertAsset(std::fstream resourceFile, Asset& assetObj,
			unsigned long long& sizeCurrent);
	static int removeAsset(std::fstream resourceFile, Asset& assetObj,
			unsigned long long& sizeCurrent);
};

}

#endif
