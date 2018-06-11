/*
 * ResourceFileUtility
 * By: Brad Lee
 */
#ifndef RFU_ASSET_H
#define RFU_ASSET_H

#include <iostream>
#include <string>
#include <chrono>
#include <boost/locale.hpp>
#include <boost/filesystem.hpp>

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
	Asset()
			:
				fileExist(false),
				fileWritten(false),
				fileProcessing(false),
				filePosCurrent(0),
				filePosNew(0),
				fileLenCurrent(0),
				fileLenNew(0),
				processBytes(0),
				fileBytes(0),
				fileReadBytesLast(0),
				processTime(std::chrono::microseconds(0)),
				fileReadTimeLast(std::chrono::microseconds(0)),
				fileReadTimePerByteLast(std::chrono::microseconds(0)),
				crc64(0),
				handle(""),
				filePath(""),
				inType(""),
				outType("") {
	}

	Asset(
		std::string handle_,
		filesystem::path filePath_,
		std::string inType_,
		std::string outType_)
			:
				fileExist(false),
				fileWritten(false),
				fileProcessing(false),
				filePosCurrent(0),
				filePosNew(0),
				fileLenCurrent(0),
				fileLenNew(0),
				processBytes(0),
				fileBytes(0),
				fileReadBytesLast(0),
				processTime(std::chrono::microseconds(0)),
				fileReadTimeLast(std::chrono::microseconds(0)),
				fileReadTimePerByteLast(std::chrono::microseconds(0)),
				crc64(0),
				handle(handle_),
				filePath(filePath_),
				inType(inType_),
				outType(outType_) {
	}
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

}

#endif
