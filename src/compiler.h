#ifndef CHANGE_HPP
#define CHANGE_HPP

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
};
}

#endif
