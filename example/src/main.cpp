#include <string>
#include <iostream>
#include <ResourceFileUtility.h>
#include "../../include/ResourceFileUtility.h"

using namespace std;

class Callback: public ResourceFileUtility::CallbackHandler {
public:
	int fileComplete(char* filePath) {
		cout << "Sucessfully Packed: " << filePath << endl;
		return 0;
	}
	int packComplete(char* filePath) {
		cout << "Sucessfully Packed all files!" << endl;
		return 0;
	}
	int estimateFileComplete(int fileID) {
		cout << "Sucessfully Packed all files!" << endl;
		return 0;
	}
};

void CBprocess(ResourceFileUtility::ResourceFile* resourceFilePtr) {
	unsigned int sizeTotal, sizeCurrent, loadBarNumber, n, i;
	sizeTotal = resourceFilePtr->getProcessingBytesTotal();
	while (true) {
		sizeCurrent = resourceFilePtr->getProcessingBytes();
		loadBarNumber =
				(unsigned int) (sizeCurrent / (double) sizeTotal * 40.0);
		cout << std::string(loadBarNumber, '#')
				<< std::string(40 - loadBarNumber, ' ') << "  " << sizeCurrent
				<< "/" << sizeTotal << "   Progress\r";
		if (sizeCurrent >= sizeTotal)
			break;
	}
	cout << "\n";
	cout << resourceFilePtr->estimateToString();
}

int main() {
	unsigned fileNumber, sizeTotal, sizeCurrent, loadBarNumber;
	ResourceFileUtility::Compiler* RFUCompiler =
			new ResourceFileUtility::Compiler();
	RFUCompiler->info("resources.json");
	ResourceFileUtility::ResourceFile* resourceFile =
			RFUCompiler->getResourceFile();
	cout << resourceFile->infoToString();
	fileNumber = resourceFile->assetListSize();
	RFUCompiler->estimate(CBprocess);
	RFUCompiler->pack("assets.data", CBprocess);
	sizeTotal = resourceFile->getProcessingBytesTotal();

// Keep the console window open in debug mode.
	string temp;
	cout << "Press any key to exit." << endl;
	getline(cin, temp);
}
