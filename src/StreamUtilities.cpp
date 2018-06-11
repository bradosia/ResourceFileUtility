#include "StreamUtilities.h"

namespace ResourceFileUtility {

unsigned char* StreamUtilities::ullToBytes(unsigned long long val) {
	unsigned long long *temp = new unsigned long long(val);
	return (unsigned char*) temp;
}

char* StreamUtilities::ullToBytesSigned(unsigned long long val) {
	unsigned long long *temp = new unsigned long long(val);
	return (char*) (unsigned char*) temp;
}

char* StreamUtilities::ullToBytesSigned(
	unsigned long long val,
	unsigned long long size) {
	char* temp = new char[size];
	memset((void*) temp, 0, size);
	memcpy((void*) temp, static_cast<void*>(&val), size);
	return temp;
}

unsigned long long StreamUtilities::bytesToUll(unsigned char* val) {
	unsigned long long *temp = (unsigned long long*) val;
	return *temp;
}

unsigned long long StreamUtilities::bytesToUll(char* val) {
	unsigned long long *temp = (unsigned long long*) (unsigned char*) val;
	return *temp;
}

void StreamUtilities::ofstreamWrite(
	nowide::ofstream& outStream,
	unsigned long long val,
	unsigned long long size) {
	char* temp = new char[size];
	memset((void*) temp, 0, size);
	memcpy((void*) temp, static_cast<void*>(&val), size);
	outStream.write(temp, size);
	delete temp;
}

}
