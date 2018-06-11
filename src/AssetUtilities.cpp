#include "AssetUtilities.h"

namespace ResourceFileUtility {

int AssetUtilities::assetListToDirectory(std::vector<Asset*>& assetList,
		Directory& directory) {
	int returnValue = 0;
	unsigned int i, n;
	n = assetList.size();
	for (i = 0; i < n; i++) {
		directory.addFromAsset(*assetList[i]);
	}
	return returnValue;
}

}
