#include "ResourceFile.h"

namespace ResourceFileUtility {

Asset::Asset() {
	init();
}

Asset::Asset(std::string handle_, filesystem::path filePath_,
		std::string inType_, std::string outType_) {
	init();
	std::cout << filePath_ << std::endl;
	handle = handle_;
	filePath = filePath_;
	inType = inType_;
	outType = outType_;
}

void Asset::init() {
	fileExist = fileWritten = fileProcessing = false;
	filePosCurrent = filePosNew = fileLenCurrent = fileLenNew = processBytes =
			fileBytes = fileReadBytesLast = 0;
	processTime = fileReadTimeLast = fileReadTimePerByteLast =
			std::chrono::microseconds(0);
	handle = inType = outType = "";
	crc64 = 0;
}

std::string Asset::getHandle() {
	return handle;
}
filesystem::path Asset::getFilePath() {
	return filePath;
}

std::string Asset::getInType() {
	return inType;
}
std::string Asset::getOutType() {
	return outType;
}

void Asset::setExist(bool flag) {
	fileExist = flag;
}

void Asset::setProcess(bool flag) {
	fileProcessing = flag;
}

bool Asset::getProcess() {
	return fileProcessing;
}

unsigned long long Asset::getProcessBytes() {
	return processBytes;
}
unsigned long long Asset::getFileBytes() {
	return fileBytes;
}
void Asset::setProcessBytes(unsigned long long val) {
	processBytes = val;
}
void Asset::setFileBytes(unsigned long long val) {
	fileBytes = val;
}
void Asset::setProcessTime(std::chrono::microseconds val) {
	processTime = val;
}
uint64_t Asset::getCRC64() {
	return crc64;
}
void Asset::setCRC64(uint64_t val) {
	crc64 = val;
}

/* ResourceFile implementation */
ResourceFile::ResourceFile() {
	version = 1526521021;
	compatibilityVersion = 1526521021;
}

void ResourceFile::addFile(std::string handle, std::string filePathString,
		std::string inType, std::string outType) {
	std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> conversion;
	std::string mbs = conversion.to_bytes(filePathString);

	filesystem::path p = filesystem::path(filePathString);
	p.imbue(std::locale("en_US.utf8"));
	assetList.push_back(new Asset(handle, p, inType, outType));
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

unsigned long long ResourceFile::getProcessingBytesTotal() {
	unsigned int i, n;
	unsigned long long size;
	n = assetList.size();
	size = 0;
	for (i = 0; i < n; i++) {
		if (assetList[i]->getProcess()) {
			size += assetList[i]->getFileBytes();
		}
	}
	return size;
}

unsigned long long ResourceFile::getProcessingBytes() {
	unsigned int i, n;
	unsigned long long size;
	n = assetList.size();
	size = 0;
	for (i = 0; i < n; i++) {
		if (assetList[i]->getProcess()) {
			size += assetList[i]->getProcessBytes();
		}
	}
	return size;
}

unsigned long long ResourceFile::getSizeTotal() {
	unsigned int i, n;
	unsigned long long size;
	n = assetList.size();
	size = 0;
	for (i = 0; i < n; i++) {
		size += assetList[i]->getFileBytes();
	}
	return size;
}

unsigned long long ResourceFile::getVersion() {
	return version;
}
unsigned long long ResourceFile::getCompatibilityVersion() {
	return compatibilityVersion;
}

std::string ResourceFile::infoToString() {
	std::stringstream stringStream;
	stringStream << std::left << std::setw(20) << "Handle" << std::setw(10)
			<< "In Type" << std::setw(10) << "Out Type" << "Path" << std::endl;
	unsigned int i, n;
	n = assetList.size();
	for (i = 0; i < n; i++) {
		stringStream << std::left << std::setw(20) << assetList[i]->getHandle()
				<< std::setw(10) << assetList[i]->getInType() << std::setw(10)
				<< assetList[i]->getOutType()
				<< assetList[i]->getFilePath().string() << std::endl;
	}
	return stringStream.str();
}

std::string ResourceFile::estimateToString() {
	std::stringstream stringStream;
	stringStream << std::left << std::setw(20) << "Handle" << std::setw(10)
			<< "Bytes" << std::setw(32) << "CRC 64" << std::endl;
	unsigned int i, n;
	n = assetList.size();
	for (i = 0; i < n; i++) {
		stringStream << std::left << std::setw(20) << assetList[i]->getHandle()
				<< std::setw(10) << assetList[i]->getFileBytes()
				<< std::setw(32) << assetList[i]->getCRC64() << std::endl;
	}
	return stringStream.str();
}

void ResourceFile::setDirectory(filesystem::path path) {
	directoryPath = path;
}

int Parser::readDirectoryJSON(filesystem::fstream& fileJSON,
		ResourceFile& resourceFileObj) {
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
			} catch (...) {
				std::cout
						<< "JSON file object does not have the \"handle\" attribute"
						<< std::endl;
			}
			try {
				filePath = files[i].at("path").get<std::string>();
			} catch (...) {
				std::cout
						<< "JSON file object does not have the \"path\" attribute"
						<< std::endl;
			}
			try {
				inType = files[i].at("inType").get<std::string>();
			} catch (...) {
				std::cout
						<< "JSON file object does not have the \"inType\" attribute"
						<< std::endl;
			}
			try {
				outType = files[i].at("outType").get<std::string>();
			} catch (...) {
				std::cout
						<< "JSON file object does not have the \"outType\" attribute"
						<< std::endl;
			}
			resourceFileObj.addFile(handle, filePath, inType, outType);
		}
		status = 0; //okay
	}
	return status;
}

int Parser::getSize(ResourceFile& directoryObj) {
	unsigned int i, n;
	n = directoryObj.assetListSize();
	for (i = 0; i < n; i++) {
		getSize(directoryObj.asset(i));
	}
	return 0;
}

int Parser::getSize(Asset* assetPtr) {
	filesystem::ifstream fileAsset;
	int retStatus = -1;
	try {
		fileAsset.open(assetPtr->getFilePath(), std::ios::binary);
		assetPtr->setExist(true);
	} catch (...) {
		retStatus = 1;
		assetPtr->setExist(false);
	}
	if (fileAsset.is_open()) {
		fileAsset.seekg(0, std::ios::end); // set the pointer to the end
		assetPtr->setFileBytes(fileAsset.tellg()); // get the length of the file
		try {
			fileAsset.close();
		} catch (...) {
			// nothing
		}
	} else {
		retStatus = 2;
	}
	return retStatus;
}

int Parser::estimate(Asset* assetPtr) {
	unsigned long long fileSize, processBytes;
	filesystem::ifstream fileAsset;
	int retStatus = -1;
	try {
		fileAsset.open(assetPtr->getFilePath(), std::ios::binary);
		assetPtr->setExist(true);
	} catch (...) {
		retStatus = 1;
		assetPtr->setExist(false);
	}
	if (fileAsset.is_open()) {
		fileAsset.seekg(0, std::ios::end); // set the pointer to the end
		fileSize = fileAsset.tellg(); // get the length of the file
		fileAsset.seekg(0, std::ios::beg); // set the pointer to the beginning
		processBytes = 0;
		unsigned long long j, buffer;
		uint64_t crcHash;
		buffer = 256;
		uint8_t bufferBytes[buffer];
		j = crcHash = 0;
		while (j < fileSize) {
			if (j + buffer > fileSize) {
				buffer = fileSize - j;
			}
			fileAsset.seekg(j, std::ios::beg);
			fileAsset.read((char*) bufferBytes, buffer);
			crcHash = hashExt::crc64(crcHash, bufferBytes, (uint64_t) buffer);
			// update status
			processBytes += buffer;
			j += buffer;
			assetPtr->setProcessBytes(processBytes);
		}
		assetPtr->setProcessBytes(fileSize);
		assetPtr->setCRC64(crcHash);
	} else {
		retStatus = 2;
	}
	return retStatus;
}

unsigned char* Parser::ullToBytes(unsigned long long val) {
	unsigned long long *temp = new unsigned long long(val);
	return (unsigned char*) temp;
}

}
