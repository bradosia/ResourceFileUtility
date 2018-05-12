#include "Compiler.h"

namespace ResourceFileUtility {
Compiler::Compiler() {
	callbackFileComplete = 0;
	callbackPackComplete = 0;
	callbackHandlerPtr = 0;
	metaDirectorySize = 128; // 128 entries
	tryToUpdate = true;
}

void Compiler::info(std::string fileName) {
	std::cout << "Opening \"" << fileName << "\" as the resource info file."
			<< std::endl;
	std::fstream fileIn;
	int readDirectoryJSONStatus;
	fileIn.open(fileName);
	readDirectoryJSONStatus = Parser::readDirectoryJSON(fileIn,
			resourceFileObj);
	if (readDirectoryJSONStatus) {
		if (readDirectoryJSONStatus == 1) {
			std::cout << "Failed opening \"" << fileName
					<< "\" as the resource info file." << std::endl;
		}
	} else {
		Parser::getSize(fileIn, resourceFileObj);
		std::cout << "Failed opening \"" << fileName
				<< "\" as the resource info file." << std::endl;
	}
}
void Compiler::estimate() {
	int estimateStatus;
	unsigned int i, n;
	unsigned long long assetSizeCurrent, assetSizeTotal;
	n = resourceFileObj.assetListSize();
	for (i = 0; i < n; i++) {
		estimateThreadList.push_back(
				new std::thread(Parser::estimate, resourceFileObj.asset(i)));
	}
	n = estimateThreadList.size();
	for (i = 0; i < n; i++) {
		estimateThreadList[i]->join();
	}
}
void Compiler::pack(std::string fileName) {
	std::cout << "Opening \"" << fileName << "\" as the resource output file."
			<< std::endl;
	std::fstream fileOut;
	fileOut.open(fileName, std::fstream::out);
	if (fileOut.is_open()) {
		std::cout << "Opened \"" << fileName
				<< "\" as the resource output file." << std::endl;
	} else {
		std::cout << "Failed opening \"" << fileName
				<< "\" as the resource output file." << std::endl;
	}
	if (callbackFileComplete != 0) {
		char test[] = "packed a file test !!";
		callbackFileComplete(test);
	}
}

void Compiler::setCallbackFileComplete(CBintString handler_) {
	callbackFileComplete = handler_;
}

void Compiler::setCallbackPackComplete(CBintString handler_) {
	callbackPackComplete = handler_;
}

void Compiler::setCallback(CallbackHandler* handler_) {
	callbackHandlerPtr = handler_;
}

ResourceFile* Compiler::getResourceFile() {
	return &resourceFileObj;
}

//namespace end
}
