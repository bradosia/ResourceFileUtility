#include "ResourceFile.h"

namespace ResourceFileUtility {

unsigned char* Directory::toBytes(unsigned int& size) {
	unsigned int i, n, offset;
	unsigned char* returnValue;
	n = entryReserve;
	if (entryList.size() > n)
		n = entryList.size();
	size = 128 * n;
	returnValue = new unsigned char[size];
	memset(&*returnValue, 0, size);
	for (i = 0; i < n; i++) {
		offset = i * 128;
		// 8 bytes = file CRC64
		memcpy(
			&returnValue[offset + 0],
			StreamUtilities::ullToBytesSigned(entryList[i]->CRC64),
			8);
		// 8 bytes = file start position (byte)
		memcpy(
			&returnValue[offset + 8],
			StreamUtilities::ullToBytesSigned(
				entryList[i]->assetPosition + offsetPosition),
			8);
		// 8 bytes = file length (byte)
		memcpy(
			&returnValue[offset + 16],
			StreamUtilities::ullToBytesSigned(entryList[i]->assetLength),
			8);
		// 8 bytes = insert time
		memcpy(
			&returnValue[offset + 24],
			StreamUtilities::ullToBytesSigned(entryList[i]->assetInsertTime),
			8);
		// 8 bytes = file type (8 digit ascii)
		memcpy(&returnValue[offset + 32], entryList[i]->type, 8);
		// 32 bytes = file handle (32 digit ascii)
		memcpy(&returnValue[offset + 40], entryList[i]->handle, 8);
	}
	return &*returnValue;
}

int Directory::addFromAsset(Asset& assetObject) {
	int returnValue = 0;
	Entry* entryTemp = new Entry();
	entryTemp->CRC64 = assetObject.getCRC64();
	entryTemp->assetLength = (uint64_t) assetObject.getFileBytes();
	entryTemp->assetPosition = findSpace(entryTemp->assetLength);
	// the insert time will be re-written when the actual packing occurs
	entryTemp->assetInsertTime = (uint64_t) std::chrono::time_point_cast<
			std::chrono::seconds>(std::chrono::system_clock::now())
		.time_since_epoch().count();
	memcpy(&entryTemp->type, assetObject.getOutType().substr(0, 7).c_str(), 8);
	memcpy(
		&entryTemp->handle,
		assetObject.getHandle().substr(0, 31).c_str(),
		32);
	entryTemp->assetPtr = &assetObject;
	entryList.push_back(entryTemp);
	// increment if last space was used
	if (entryTemp->assetPosition == spaceLast) {
		spaceLast += entryTemp->assetLength;
	}
	return returnValue;
}

uint64_t Directory::findSpace(uint64_t length) {
	unsigned int i, n;
	n = spaceList.size();
	uint64_t returnValue = spaceLast;
	if (n > 0) {
		for (i = 0; i < n; i++) {
			// pair->first = space starting position, pair->second = space length
			if (length <= spaceList[i]->second) {
				returnValue = spaceList[i]->first;
				break;
			}
		}
	}
	return returnValue;
}

void Directory::setOffsetPosition(uint64_t pos) {
	offsetPosition = pos;
}

void Directory::setEntryReserve(unsigned int val) {
	entryReserve = val;
}

}
