#include "math.hpp"
#include "change.h"
#include <iostream>

using namespace std;

int __stdcall math_add(int a, int b) {
	return a + b;
}

int __stdcall math_add2(int a, int b) {
	return a + b + 2;
}

void __stdcall coutTest() {
	test();
}

intptr_t __stdcall objNew() {
	intptr_t test = (intptr_t) new myObj;
	cout << test << endl;
	return test;
}

void __stdcall objSet(intptr_t ptr, int testint) {
	myObj* objPtr = (myObj*)ptr;
	objPtr->temp = testint+2;
}

int __stdcall objGet(intptr_t ptr) {
	myObj* objPtr = (myObj*)ptr;
	return objPtr->temp;
}

