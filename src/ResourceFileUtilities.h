/*
 * ResourceFileUtility
 * By: Brad Lee
 */
#ifndef RFU_RESOURCE_FILE_UTILITIES_H
#define RFU_RESOURCE_FILE_UTILITIES_H

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
#ifndef ONE_HEADER
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/encodedstream.h>
#endif
#include "crc64.h"
#include "Asset.h"
#include "AssetUtilities.h"
#include "ResourceFile.h"

using namespace boost;

namespace ResourceFileUtility {

class ResourceFileUtilities {
public:
	static int readDirectoryJSON(
		filesystem::fstream& resourceFile,
		ResourceFile& directoryObj);
	static int readDirectory(
		filesystem::fstream& resourceFile,
		ResourceFile& directoryObj);
	static int getSize(ResourceFile& directoryObj);
	static int getSize(Asset* assetPtr);
	static int estimate(Asset* assetPtr);
	static int writeDirectory(
		filesystem::fstream& resourceFile,
		ResourceFile& directoryObj);
	static int insertAsset(filesystem::fstream& resourceFile, Asset& assetObj);
	static int removeAsset(filesystem::fstream& resourceFile, Asset& assetObj);
};

}

#endif
