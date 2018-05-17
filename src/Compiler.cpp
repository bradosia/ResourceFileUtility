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
		} else if (readDirectoryJSONStatus == -1) {
			std::cout << "Unknown error in \"" << fileName
					<< "\" as the resource info file." << std::endl;
		}
	} else {
		Parser::getSize(resourceFileObj);
		std::cout << "Success opening \"" << fileName
				<< "\" as the resource info file." << std::endl;
	}
}
void Compiler::estimate() {
	Compiler::estimate([](ResourceFile* resourceFilePtr) {});
}
void Compiler::estimate(CBvoidResourceFile handler_) {
	int estimateStatus;
	unsigned int i, n;
	unsigned long long assetSizeCurrent, assetSizeTotal;
	// re check sizes
	Parser::getSize(resourceFileObj);
	// begin estimate threads and set processing flag
	n = resourceFileObj.assetListSize();
	for (i = 0; i < n; i++) {
		resourceFileObj.asset(i)->setProcess(true);
		estimateThreadList.push_back(
				new std::thread(Parser::estimate, resourceFileObj.asset(i)));
	}
	// custom handler
	estimateThreadList.push_back(new std::thread(handler_, &resourceFileObj));
	// join threads
	n = estimateThreadList.size();
	for (i = 0; i < n; i++) {
		estimateThreadList[i]->join();
	}
	// end the processing flag
	n = resourceFileObj.assetListSize();
	for (i = 0; i < n; i++) {
		resourceFileObj.asset(i)->setProcess(false);
	}
}
void Compiler::pack(std::string fileName) {
	Compiler::pack(fileName, [](ResourceFile* resourceFilePtr) {});
}
void Compiler::pack(std::string fileName, CBvoidResourceFile handler_) {
	std::cout << "Opening \"" << fileName << "\" as the resource output file."
			<< std::endl;
	std::fstream fileOut;
	fileOut.open(fileName, std::fstream::out);
	if (fileOut.is_open()) {
		std::cout << "Opened \"" << fileName
				<< "\" as the resource output file." << std::endl;
		fileOut.seekg(0, std::ios::beg); // set the pointer to the beginning
		fileOut.write(
				(const char*) Parser::ullToBytes(resourceFileObj.getVersion()),
				8);
		fileOut.seekg(8, std::ios::beg);
		fileOut.write(
				(const char*) Parser::ullToBytes(
						resourceFileObj.getCompatibilityVersion()), 8);
	} else {
		std::cout << "Failed opening \"" << fileName
				<< "\" as the resource output file." << std::endl;
	}
	if (callbackFileComplete != 0) {
		char test[] = "packed a file test !!";
		callbackFileComplete(test);
	}
	fileOut.close();
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
