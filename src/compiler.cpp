#include "compiler.h"

namespace ResourceFileUtility {
Compiler::Compiler() {

}
Compiler::~Compiler() {

}
void Compiler::info(std::string fileName) {
	std::cout << fileName << std::endl;
	std::fstream fileIn;
	nlohmann::json j;
	fileIn.open(fileName);
	if (fileIn.is_open()) {
		fileIn >> j;
	}
}
}
