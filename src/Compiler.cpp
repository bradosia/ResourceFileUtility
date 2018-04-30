#include "Compiler.h"

namespace ResourceFileUtility {
Compiler::Compiler() {
	callbackFileComplete = 0;
	callbackPackComplete = 0;
	callbackHandlerPtr = 0;
}
Compiler::~Compiler() {

}
void Compiler::info(std::string fileName) {
	std::cout << "Opening \"" << fileName << "\" as the resource info file."
			<< std::endl;
	std::fstream fileIn;
	nlohmann::json j;
	std::string handle = "";
	unsigned int i, n;
	bool parseFlag = false;
	nlohmann::json files;

	fileIn.open(fileName);
	if (fileIn.is_open()) {
		try {
			fileIn >> j;
			parseFlag = true;
		} catch (...) {
			std::cout << "Failed to parse JSON!" << std::endl;
		}
	} else {
		std::cout << "Failed opening \"" << fileName
				<< "\" as the resource info file." << std::endl;
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
			try {
				handle = files[i].at("handle").get<std::string>();
				std::cout << "Found handle: " << handle << std::endl;
			} catch (...) {
				std::cout
						<< "JSON file object does not have the \"handle\" attribute"
						<< std::endl;
			}
			try {
				handle = files[i].at("path").get<std::string>();
				std::cout << "Found handle: " << handle << std::endl;
			} catch (...) {
				std::cout
						<< "JSON file object does not have the \"path\" attribute"
						<< std::endl;
			}
			try {
				handle = files[i].at("inType").get<std::string>();
				std::cout << "Found handle: " << handle << std::endl;
			} catch (...) {
				std::cout
						<< "JSON file object does not have the \"inType\" attribute"
						<< std::endl;
			}
			try {
				handle = files[i].at("outType").get<std::string>();
				std::cout << "Found handle: " << handle << std::endl;
			} catch (...) {
				std::cout
						<< "JSON file object does not have the \"outType\" attribute"
						<< std::endl;
			}
		}
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

}
