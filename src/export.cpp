/*
 * 2018-04-18: This used to be a .hpp file, but eclipse refuses to compile it by default.
 * Changed to a cpp file
 */

#ifndef EXPORT_HPP
#define EXPORT_HPP

#ifdef __cplusplus
#define EXTERNC         extern "C"
#else
#define EXTERNC
#endif

#if defined __linux__ || defined __CYGWIN__
#define IDAMAN
#define IDA_EXPORT
#elif defined _WIN32
#define IDAMAN EXTERNC __declspec(dllexport)
#define IDA_EXPORT __stdcall
#elif defined __APPLE__ || defined(__MAC__)
#define IDAMAN EXTERNC __declspec(dllexport)
#define IDA_EXPORT __stdcall
#endif

#include "Loader.h"
#include "Compiler.h"
#include "Stream.h"

IDAMAN intptr_t IDA_EXPORT loader_new();
IDAMAN intptr_t IDA_EXPORT compiler_new();
IDAMAN void IDA_EXPORT compiler_info(intptr_t ptr, char* fileName);
IDAMAN void IDA_EXPORT compiler_pack(intptr_t ptr, char* fileName);
IDAMAN intptr_t IDA_EXPORT stream_new();

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
