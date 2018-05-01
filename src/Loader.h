#ifndef LOADER_H
#define LOADER_H

#include <iostream>
#include <string>
#include "ResourceFile.h"

namespace ResourceFileUtility {

class Loader {
	ResourceFile resourceFileObj;
public:
	Loader();
	virtual ~Loader() {
	}
	void info(std::string fileName);
};

}

#endif
