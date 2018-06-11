/*
 * ResourceFileUtility
 * By: Brad Lee
 */
#ifndef RFU_RESOURCE_FILE_H
#define RFU_RESOURCE_FILE_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <unordered_map>
#include <boost/locale.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>		// linux-x86_64-gcc needs this for boost::filesystem::fstream
#include <boost/nowide/fstream.hpp>
#include <boost/nowide/iostream.hpp>
#include "crc64.h"
#include "Asset.h"
#include "AssetUtilities.h"
#include "StreamUtilities.h"

using namespace boost;

namespace ResourceFileUtility {

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
	std::unordered_map<char*, Asset*> hashTable;
	unsigned int metaSize, directoryEntryReserve, directoryEntrySize;
public:
	ResourceFile()
			:
				versionStatic(1526521021),
				compatibilityVersionStatic(1526521021),
				version(0),
				compatibilityVersion(0),
				directoryStartByte(0),
				DataStartByte(0),
				directoryEntryReserve(0),
				metaSize(128),
				directoryEntrySize(128) {
	}
	;
	virtual ~ResourceFile() {
	}
	void addFile(
		std::string handle,
		std::string filePathString,
		std::string inType,
		std::string outType);
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
	int buildDirectory();
};

}

#endif
