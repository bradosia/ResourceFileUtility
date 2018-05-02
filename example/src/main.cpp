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
	unsigned long long sizeCurrent, sizeTotal;
	ResourceFileUtility::Compiler* RFUCompiler =
			new ResourceFileUtility::Compiler();
	RFUCompiler->setCallback(new Callback());
	RFUCompiler->info("resources.json");
	RFUCompiler->packEstimate(sizeCurrent, sizeTotal);
	RFUCompiler->pack("assets.data");

	// Keep the console window open in debug mode.
	string temp;
	cout << "Press any key to exit." << endl;
	getline(cin, temp);
}
