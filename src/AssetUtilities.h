/*
 * ResourceFileUtility
 * By: Brad Lee
 */
#ifndef RFU_ASSET_UTILITIES_H
#define RFU_ASSET_UTILITIES_H

#include "Asset.h"
#include "Directory.h"

using namespace boost;

namespace ResourceFileUtility {

class AssetUtilities {
public:
	static int assetListToDirectory(
		std::vector<Asset*>& assetList,
		Directory& directory);
};

}

#endif
