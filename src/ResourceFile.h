#ifndef RESOURCE_FILE_H
#define RESOURCE_FILE_H

#include <iostream>
#include <string>
#include <vector>

namespace ResourceFileUtility {

/*
 * @class Directory
 * Each Directory entry takes up the bytes
 * 8 bytes = file CRC64
 * 8 bytes = file start position (byte)
 * 8 bytes = file length (byte)
 * 8 bytes = file type (8 digit ascii)
 * 32 bytes = file handle (32 digit ascii)
 * 64 bytes = custom
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
};

class ResourceFile {
private:
	Directory directory;
	std::vector<Asset> assetList;
public:
	ResourceFile();
	virtual ~ResourceFile() {
	}
};

class Parser {
public:
	Parser();
	virtual ~Parser() {
	}
	bool readDirectory(std::fstream resourceFile, Directory& directoryObj,
			unsigned long long& sizeCurrent);
	bool writeDirectory(std::fstream resourceFile, Directory& directoryObj,
			unsigned long long& sizeCurrent);
	bool insertAsset(std::fstream resourceFile, Asset& assetObj,
			unsigned long long& sizeCurrent);
	bool removeAsset(std::fstream resourceFile, Asset& assetObj,
			unsigned long long& sizeCurrent);
};

}

#endif
