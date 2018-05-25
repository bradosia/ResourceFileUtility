/*
 * ResourceFileUtility
 * By: Brad Lee
 */
#ifndef LOADER_H
#define LOADER_H

#include <iostream>
#include <string>
#include "ResourceFile.h"

namespace ResourceFileUtility {

class ResourceFile;
class Asset;
class Loader {
private:
	ResourceFile resourceFileObj;
public:
	Loader();
	virtual ~Loader() {
	}
	unsigned int data(std::string resourceFileName);
	Asset* info(std::string assetHandle);
	unsigned char** open(std::string assetHandle);
};

}

#endif
