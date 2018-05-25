/*
 * ResourceFileUtility
 * By: Brad Lee
 */
#ifndef RESOURCE_FILE_H
#define RESOURCE_FILE_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <boost/locale.hpp>
#include <boost/filesystem.hpp>
#include <boost/nowide/fstream.hpp>
#include <boost/nowide/iostream.hpp>
#include "../contrib/json.hpp"
#include "crc64.h"

using namespace boost;

namespace ResourceFileUtility {

class Asset {
private:
	bool fileExist, fileWritten, fileProcessing;
	unsigned long long filePosCurrent, filePosNew, fileLenCurrent, fileLenNew,
			processBytes, fileBytes, fileReadBytesLast;
	std::chrono::microseconds processTime, fileReadTimeLast,
			fileReadTimePerByteLast;
	std::string handle, inType, outType;
	filesystem::path filePath;
	uint64_t crc64;
public:
	Asset();
	Asset(std::string handle_, filesystem::path filePath_, std::string inType_,
			std::string outType_);
	void init();
	std::string getHandle();
	filesystem::path getFilePath();
	std::string getInType();
	std::string getOutType();
	void setExist(bool flag);
	void setProcess(bool flag);
	bool getProcess();
	unsigned long long getProcessBytes();
	unsigned long long getFileBytes();
	void setProcessBytes(unsigned long long val);
	void setFileBytes(unsigned long long val);
	void setProcessTime(std::chrono::microseconds val);
	uint64_t getCRC64();
	void setCRC64(uint64_t val);
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
		unsigned long long CRC64, assetPosition, assetLength, assetInsertTime;
		char type[8], handle[32];
	};
	std::unordered_map<char*, Entry*> hashTable;
public:
	unsigned char* toBytes();
	unsigned int addFromAsset(Asset& assetObject);

};

/**
 * @class ResourceFile
 * Resource File Meta
 * 8 bytes = file version
 * 8 bytes = file compatibility version
 * 8 bytes = last write time (seconds since unix epoch)
 * 8 bytes = directory start position (byte)
 * 8 bytes = directory length (byte)
 * 8 bytes = directory CRC64
 * 8 bytes = data start position (byte)
 * 8 bytes = data length (byte)
 * 8 bytes = data CRC64
 * 72 bytes = reserved
 * 128 bytes total
 **/
class ResourceFile {
private:
	Directory directory;
	std::vector<Asset*> assetList;
	unsigned long long versionStatic, compatibilityVersionStatic, version,
			compatibilityVersion // equal compatibility versions can be read/written
			, directoryStartByte, DataStartByte;
	std::chrono::time_point<std::chrono::system_clock> writeTimeLast;
	filesystem::path directoryPath;
public:
	ResourceFile();
	virtual ~ResourceFile() {
	}
	void addFile(std::string handle, std::string filePathString,
			std::string inType, std::string outType);
	unsigned int assetListSize();
	Asset* asset(unsigned int assetID);
	unsigned long long getProcessingBytesTotal();
	unsigned long long getProcessingBytes();
	unsigned long long getSizeTotal();
	unsigned long long getVersion();
	unsigned long long getCompatibilityVersion();
	std::string infoToString();
	std::string estimateToString();
	void setDirectory(filesystem::path path);
	unsigned int open(std::string resourceFileName);
	unsigned int open(std::wstring resourceFileName);
	unsigned int open(filesystem::path resourceFilePath);
	unsigned int write(std::string resourceFileName);
	unsigned int write(std::wstring resourceFileName);
	unsigned int write(filesystem::path resourceFilePath);
};

class Parser {
public:
	Parser() {

	}
	virtual ~Parser() {
	}
	static int readDirectoryJSON(filesystem::fstream& resourceFile,
			ResourceFile& directoryObj);
	static int readDirectory(filesystem::fstream& resourceFile,
			ResourceFile& directoryObj);
	static int getSize(ResourceFile& directoryObj);
	static int getSize(Asset* assetPtr);
	static int estimate(Asset* assetPtr);
	static int writeDirectory(filesystem::fstream& resourceFile,
			ResourceFile& directoryObj);
	static int insertAsset(filesystem::fstream& resourceFile, Asset& assetObj);
	static int removeAsset(filesystem::fstream& resourceFile, Asset& assetObj);
	static unsigned char* ullToBytes(unsigned long long val);
	static char* ullToBytesSigned(unsigned long long val);
	static unsigned long long bytesToUll(unsigned char* val);
	static unsigned long long bytesToUll(char* val);
};

}

#endif
