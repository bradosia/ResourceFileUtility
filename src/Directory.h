/*
 * ResourceFileUtility
 * By: Brad Lee
 */
#ifndef RFU_DIRECTORY_H
#define RFU_DIRECTORY_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <unordered_map>
#include "Asset.h"
#include "StreamUtilities.h"

using namespace boost;

namespace ResourceFileUtility {

/*
 * @class Directory
 * A pre-processed resource file directory.\n
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
	public:
		uint64_t CRC64, assetPosition // relative offset from file data start position
				, assetLength, assetInsertTime;
		char type[8], handle[32];
		Asset* assetPtr;
	};
	std::vector<Entry*> entryList;
	std::vector<std::pair<uint64_t, uint64_t>*> spaceList;
	uint64_t spaceLast, offsetPosition;
	unsigned int entryReserve;
public:
	Directory()
			: spaceLast(0), offsetPosition(0), entryReserve(0) {
	}
	unsigned char* toBytes(unsigned int& size);
	int addFromAsset(Asset& assetObject);
	uint64_t findSpace(uint64_t length);
	void setOffsetPosition(uint64_t pos);
	void setEntryReserve(unsigned int val);
};

}

#endif
