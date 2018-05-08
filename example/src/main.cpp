#include <string>
#include <iostream>
#include <ResourceFileUtility.h>

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

int main() {
	unsigned fileNumber, sizeTotal, sizeCurrent, loadBarNumber;
	ResourceFileUtility::Compiler RFUCompiler =
			new ResourceFileUtility::Compiler();
	RFUCompiler.info("resources.json");
	ResourceFileUtility::FileList fileList = RFUCompiler.getFileList();
	fileNumber = fileList.size();
	RFUCompiler.estimate();
	sizeTotal = RFUCompiler.sizePending();
	while (true) {
		sizeCurrent = 0;
		for (int i = 0; i < fileNumber; i++) {
			sizeCurrent += fileList[i]->processSize();
		}
		loadBarNumber =
				(unsigned int) (sizeCurrent / (double) sizeTotal * 20.0);
		cout << std::string(loadBarNumber, '#')
				<< std::string(20 - loadBarNumber, ' ') << " Progress\r";
		if (sizeCurrent >= sizeTotal)
			break;
	}
	RFUCompiler.pack("assets.data");
	sizeTotal = RFUCompiler.sizePending();
	while (true) {
		sizeCurrent = 0;
		for (int i = 0; i < fileNumber; i++) {
			sizeCurrent += fileList[i]->processSize();
		}
		loadBarNumber =
				(unsigned int) (sizeCurrent / (double) sizeTotal * 20.0);
		cout << std::string(loadBarNumber, '#')
				<< std::string(20 - loadBarNumber, ' ') << " Progress\r";
		if (sizeCurrent >= sizeTotal)
			break;
	}

// Keep the console window open in debug mode.
	string temp;
	cout << "Press any key to exit." << endl;
	getline(cin, temp);
}
