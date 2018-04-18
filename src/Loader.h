#ifndef LOADER_H
#define LOADER_H

#include <iostream>
#include <string>
#include <fstream>

namespace ResourceFileUtility {

class Loader {
public:
	int test;
	Loader();
	~Loader();
	void info(std::string fileName);
};

}

#endif
