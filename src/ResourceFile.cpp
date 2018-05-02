#include "ResourceFile.h"

namespace ResourceFileUtility {

ResourceFile::ResourceFile() {

}

Asset::Asset(std::string handle_, std::string filePath_, std::string inType_,
		std::string outType_){
	handle = handle_;
	path = filePath_;
	inType = inType_;
	outType = outType_;
}

int Parser::readDirectoryJSON(std::fstream fileJSON, ResourceFile& directoryObj,
		unsigned long long& sizeCurrent) {
	nlohmann::json j;
	std::string handle;
	std::string filePath;
	std::string inType;
	std::string outType;
	unsigned int i, n;
	bool parseFlag = false;
	nlohmann::json files;
	int status = -1;

	if (fileJSON.is_open()) {
		try {
			fileJSON >> j;
			parseFlag = true;
		} catch (...) {
			std::cout << "Failed to parse JSON!" << std::endl;
		}
	} else {
		status = 1;
	}
	/* the user defined json file is very unsafe
	 * we wrap all the attribute accessing in try{}catch(...){}
	 */
	if (parseFlag) {
		parseFlag = false;
		try {
			files = j.at("files");
			parseFlag = true;
		} catch (...) {
			std::cout << "JSON does not have the \"files\" attribute"
					<< std::endl;
		}
	}
	/* Too many nested try {} statements will confuse me so this part
	 * gets its own if block
	 */
	if (parseFlag) {
		n = files.size();
		for (i = 0; i < n; i++) {
			std::string handle = "";
			std::string filePath = "";
			std::string inType = "";
			std::string outType = "";
			try {
				handle = files[i].at("handle").get<std::string>();
				std::cout << "Found handle: " << handle << std::endl;
			} catch (...) {
				std::cout
						<< "JSON file object does not have the \"handle\" attribute"
						<< std::endl;
			}
			try {
				filePath = files[i].at("path").get<std::string>();
				std::cout << "Found path: " << handle << std::endl;
			} catch (...) {
				std::cout
						<< "JSON file object does not have the \"path\" attribute"
						<< std::endl;
			}
			try {
				inType = files[i].at("inType").get<std::string>();
				std::cout << "Found handle: " << handle << std::endl;
			} catch (...) {
				std::cout
						<< "JSON file object does not have the \"inType\" attribute"
						<< std::endl;
			}
			try {
				outType = files[i].at("outType").get<std::string>();
				std::cout << "Found handle: " << handle << std::endl;
			} catch (...) {
				std::cout
						<< "JSON file object does not have the \"outType\" attribute"
						<< std::endl;
			}
			directoryObj.addFile(handle, filePath, inType, outType);
		}
	}
	return status;
}

}
