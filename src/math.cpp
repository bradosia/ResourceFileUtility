#include <iostream>

#include "compiler.h"
#include "export.hpp"

using namespace std;

int __stdcall math_add(int a, int b) {
	return a + b;
}

int __stdcall math_add2(int a, int b) {
	return a + b + 2;
}

void __stdcall coutTest() {
	cout << "hey" << endl;
}

intptr_t __stdcall compile_new() {
	return (intptr_t) new ResourceFileUtility::Compiler;
}

void __stdcall objSet(intptr_t ptr, int testint) {
	ResourceFileUtility::Compiler* objPtr = (ResourceFileUtility::Compiler*)ptr;
	objPtr->test = testint+2;
}

int __stdcall objGet(intptr_t ptr) {
	ResourceFileUtility::Compiler* objPtr = (ResourceFileUtility::Compiler*)ptr;
	return objPtr->test;
}

void __stdcall compile_info(intptr_t ptr, char* fileName) {
	ResourceFileUtility::Compiler* objPtr = (ResourceFileUtility::Compiler*)ptr;
	return objPtr->info(std::string(fileName));
}
