#include "Parser.h"

namespace ResourceFileUtility {

int Parser::readDirectoryJSON(filesystem::fstream& fileJSON,
		ResourceFile& resourceFileObj) {
	std::string handle;
	std::string filePath;
	std::string inType;
	std::string outType;
	int status = -1;
	rapidjson::IStreamWrapper isw(fileJSON);
	rapidjson::EncodedInputStream<rapidjson::UTF8<>, rapidjson::IStreamWrapper> eis(
			isw);
	rapidjson::Document jsonDocument; // Document is GenericDocument<UTF8<> >
	jsonDocument.ParseStream<0, rapidjson::UTF8<> >(eis); // Parses UTF-8 file into UTF-8 in memory
	if (jsonDocument.HasParseError()) {
		std::cout << "Failed to parse JSON!";
		if (jsonDocument.GetParseError() == 3) {
			std::cout << " Possible reason: file encoding incorrect\n";
		} else {
			std::cout << " Error code: " << jsonDocument.GetParseError()
					<< " at position " << jsonDocument.GetErrorOffset() << "\n";
		}
	} else if (!jsonDocument.IsObject()) {
		std::cout << "JSON is not an object\n";
	} else if (!jsonDocument.HasMember("files")) {
		std::cout << "JSON does not have the \"files\" attribute\n";
	} else if (!jsonDocument["files"].IsArray()) {
		std::cout << "\"files\" attribute attributes is not an array\n";
	} else {
		rapidjson::Value& fileArray = jsonDocument["files"];
		for (auto& fileObject : fileArray.GetArray()) {
			if (fileObject.IsObject()) {
				std::string handle = "";
				std::string filePath = "";
				std::string inType = "";
				std::string outType = "";
				/* get handle */
				if (fileObject.HasMember("handle")
						&& fileObject["handle"].IsString()) {
					handle = fileObject["handle"].GetString();
				} else {
					std::cout
							<< "JSON file object does not have the \"handle\" attribute\n";
				}
				/* get filePath */
				if (fileObject.HasMember("path")
						&& fileObject["path"].IsString()) {
					filePath = fileObject["path"].GetString();
				} else {
					std::cout
							<< "JSON file object does not have the \"path\" attribute\n";
				}
				/* get inType */
				if (fileObject.HasMember("inType")
						&& fileObject["inType"].IsString()) {
					inType = fileObject["inType"].GetString();
				} else {
					std::cout
							<< "JSON file object does not have the \"inType\" attribute\n";
				}
				/* get inType */
				if (fileObject.HasMember("outType")
						&& fileObject["outType"].IsString()) {
					outType = fileObject["outType"].GetString();
				} else {
					std::cout
							<< "JSON file object does not have the \"outType\" attribute\n";
				}
				resourceFileObj.addFile(handle, filePath, inType, outType);
			}
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
	nowide::ifstream fileAsset;
	int retStatus = -1;
	try {
		fileAsset.open(assetPtr->getFilePath().string(), std::ios::binary);
	} catch (...) {
		retStatus = 1;
	}
	if (fileAsset.is_open()) {
		assetPtr->setExist(true);
		// std::cout << "open " << assetPtr->getFilePath() << std::endl;
		fileAsset.seekg(0, std::ios::end); // set the pointer to the end
		assetPtr->setFileBytes(fileAsset.tellg()); // get the length of the file
		try {
			fileAsset.close();
		} catch (...) {
			// nothing
		}
	} else {
		assetPtr->setExist(false);
		retStatus = 2;
	}
	return retStatus;
}

int Parser::estimate(Asset* assetPtr) {
	unsigned long long fileSize, processBytes;
	nowide::ifstream fileAsset;
	int retStatus = -1;
	try {
		fileAsset.open(assetPtr->getFilePath().string(), std::ios::binary);
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

char* Parser::ullToBytesSigned(unsigned long long val) {
	unsigned long long *temp = new unsigned long long(val);
	return (char*) (unsigned char*) temp;
}

char* Parser::ullToBytesSigned(unsigned long long val,
		unsigned long long size) {
	char* temp = new char[size];
	memset((void*) temp, 0, size);
	memcpy((void*) temp, static_cast<void*>(&val), size);
	return temp;
}

unsigned long long Parser::bytesToUll(unsigned char* val) {
	unsigned long long *temp = (unsigned long long*) val;
	return *temp;
}

unsigned long long Parser::bytesToUll(char* val) {
	unsigned long long *temp = (unsigned long long*) (unsigned char*) val;
	return *temp;
}

void Parser::ofstreamWrite(nowide::ofstream& outStream, unsigned long long val,
		unsigned long long size) {
	char* temp = new char[size];
	memset((void*) temp, 0, size);
	memcpy((void*) temp, static_cast<void*>(&val), size);
	outStream.write(temp, size);
	delete temp;
}

int Parser::assetListToDirectory(std::vector<Asset*>& assetList,
		Directory& directory) {
	int returnValue = 0;
	unsigned int i, n;
	n = assetList.size();
	for (i = 0; i < n; i++) {
		directory.addFromAsset(*assetList[i]);
	}
	return returnValue;
}

}
