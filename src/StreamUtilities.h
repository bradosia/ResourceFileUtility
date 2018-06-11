/*
 * ResourceFileUtility
 * By: Brad Lee
 */
#ifndef RFU_STREAM_UTILITIES_H
#define RFU_STREAM_UTILITIES_H

#include <boost/locale.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>		// linux-x86_64-gcc needs this for boost::filesystem::fstream
#include <boost/nowide/fstream.hpp>
#include <boost/nowide/iostream.hpp>

using namespace boost;

namespace ResourceFileUtility {

class StreamUtilities {
public:
	static unsigned char* ullToBytes(unsigned long long val);
	static char* ullToBytesSigned(unsigned long long val);
	static char* ullToBytesSigned(
		unsigned long long val,
		unsigned long long size);
	static unsigned long long bytesToUll(unsigned char* val);
	static unsigned long long bytesToUll(char* val);
	static void ofstreamWrite(
		nowide::ofstream& outStream,
		unsigned long long val,
		unsigned long long size);
};

}

#endif
