#ifndef COMPILER_H
#define COMPILER_H

#include <iostream>
#include <string>
#include <fstream>
#include "../contrib/json.hpp"

namespace ResourceFileUtility {

class Compiler {
public:
	int test;
	Compiler();
	~Compiler();
	void info(std::string fileName);
	void pack(std::string fileName);
};

}

#endif
