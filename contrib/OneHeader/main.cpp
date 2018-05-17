/*
 * Creates a monolithic header
 */
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char** argv) {
	char *streamInName, *fileOutputName;
	unsigned int fileSize, filePos;
	ifstream streamIn;
	ofstream fileOutput;
	if (argc > 1) {
		streamInName = argv[0];
		fileOutputName = argv[1];
		streamIn.open(streamInName);
		if (streamIn.is_open()) {
			streamIn.seekg(0, ios::end); // set the pointer to the end
			fileSize = streamIn.tellg(); // get the length of the file
			streamIn.seekg(0, ios::beg); // set the pointer to the beginning
			for (filePos = 0; filePos < fileSize; filePos++) {
				// read one byte at a time
				streamIn.seekg(filePos, ios::beg);
				streamIn.read(bufferInChar, 1);
			}
		}
	} else {
		cout
				<< "Use the program like this:\nOneHeader.exe ../../src/OneHeader.h ../../include/OneHeaderOutput.h\n";
	}

	return 0;
}
