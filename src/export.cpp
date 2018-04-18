/*
 * 2018-04-18: This used to be a .hpp file, but eclipse refuses to compile it by default.
 * Changed to a cpp file
 */

#ifndef EXPORT_HPP
#define EXPORT_HPP

#include "Loader.h"
#include "Compiler.h"
#include "Stream.h"
#define DllExport __declspec( dllexport )

extern "C" {

DllExport intptr_t loader_new();
DllExport intptr_t compiler_new();
DllExport void compiler_info(intptr_t ptr, char* fileName);
DllExport void compiler_pack(intptr_t ptr, char* fileName);
DllExport intptr_t stream_new();

}

intptr_t loader_new() {
	return (intptr_t) new ResourceFileUtility::Loader;
}

intptr_t compiler_new() {
	return (intptr_t) new ResourceFileUtility::Compiler;
}

void compiler_info(intptr_t ptr, char* fileName) {
	ResourceFileUtility::Compiler* objPtr = (ResourceFileUtility::Compiler*) ptr;
	return objPtr->info(std::string(fileName));
}

void compiler_pack(intptr_t ptr, char* fileName) {
	ResourceFileUtility::Compiler* objPtr = (ResourceFileUtility::Compiler*) ptr;
	return objPtr->pack(std::string(fileName));
}

intptr_t stream_new() {
	return (intptr_t) new ResourceFileUtility::Stream;
}

#endif
