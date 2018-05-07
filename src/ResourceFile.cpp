#include "ResourceFile.h"

namespace ResourceFileUtility {

ResourceFile::ResourceFile() {

}

void ResourceFile::addFile(std::string handle, std::string filePath,
		std::string inType, std::string outType) {
	assetList.push_back(new Asset(handle, filePath, inType, outType));
}
unsigned int ResourceFile::assetListSize() {
	return (unsigned int) assetList.size();
}
Asset* ResourceFile::asset(unsigned int assetID) {
	Asset* assetObj = nullptr;
	try {
		assetObj = assetList[assetID];
	} catch (...) {

	}
	return assetObj;
}

Asset::Asset(std::string handle_, std::string filePath_, std::string inType_,
		std::string outType_) {
	handle = handle_;
	path = filePath_;
	inType = inType_;
	outType = outType_;
}

std::string Asset::getPath() {
	return path;
}

void Asset::setExist(bool flag) {
	fileExist = flag;
}

int Parser::readDirectoryJSON(std::fstream& fileJSON,
		ResourceFile& resourceFileObj, unsigned long long& sizeCurrent,
		unsigned long long& sizeTotal) {
	nlohmann::json j;
	std::string handle;
	std::string filePath;
	std::string inType;
	std::string outType;
	unsigned int i, n;
	bool parseFlag = false;
	nlohmann::json files;
	int status = -1;
	sizeCurrent = sizeTotal = 0;

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
		sizeTotal = (unsigned long long) n;
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
				std::cout << "Found path: " << filePath << std::endl;
			} catch (...) {
				std::cout
						<< "JSON file object does not have the \"path\" attribute"
						<< std::endl;
			}
			try {
				inType = files[i].at("inType").get<std::string>();
				std::cout << "Found inType: " << inType << std::endl;
			} catch (...) {
				std::cout
						<< "JSON file object does not have the \"inType\" attribute"
						<< std::endl;
			}
			try {
				outType = files[i].at("outType").get<std::string>();
				std::cout << "Found outType: " << outType << std::endl;
			} catch (...) {
				std::cout
						<< "JSON file object does not have the \"outType\" attribute"
						<< std::endl;
			}
			resourceFileObj.addFile(handle, filePath, inType, outType);
			sizeCurrent++;
		}
	}
	return status;
}

int Parser::estimate(Asset& assetObj, unsigned long long& sizeCurrent,
		unsigned long long& sizeTotal) {
	unsigned long long fileSize;
	sizeCurrent = sizeTotal = 0;
	std::ifstream fileAsset;
	int retStatus = -1;
	try {
		std::cout << assetObj.getPath() << std::endl;
		fileAsset.open(assetObj.getPath(), std::ios::binary);
		assetObj.setExist(true);
	} catch (...) {
		retStatus = 1;
		assetObj.setExist(false);
	}
	if (fileAsset.is_open()) {
		fileAsset.seekg(0, std::ios::end); // set the pointer to the end
		fileSize = fileAsset.tellg(); // get the length of the file
		fileAsset.seekg(0, std::ios::beg); // set the pointer to the beginning
		std::cout << "size: " << fileSize << std::endl;
		uint64_t crcHash = hashExt::crc64(0, (std::istream&) fileAsset, fileSize);
		std::cout << "hash: " << crcHash << std::endl;
	} else {
		retStatus = 2;
	}
	return retStatus;
}

}
