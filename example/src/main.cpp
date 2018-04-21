#include <ResourceFileUtility.h>
#include <string>
#include <iostream>

using namespace std;

class Callback: ResourceFileUtility::CallbackHandler {
public:
	void fileComplete(string filePath) {
		cout << "Sucessfully Packed: " << filePath << endl;
	}
	void packComplete() {
		cout << "Sucessfully Packed all files!" << endl;
	}
};

int main() {
	ResourceFileUtility::Compiler* RFUCompiler =
			new ResourceFileUtility::Compiler();
	RFUCompiler->info("resources.json");
	RFUCompiler->pack("assets.data");
	//RFUCompiler->pack("assets.data", new Callback());

	// Keep the console window open in debug mode.
	string temp;
	cout << "Press any key to exit." << endl;
	getline(cin, temp);
}
