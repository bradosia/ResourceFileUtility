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

#define IDAMAN
#define IDA_EXPORT 

#if defined(__NT__)                   // MS Windows
#define IDAAPI __stdcall
#define IDA_EXPORT IDAAPI
#if defined(__IDP__)                  // modules
#define IDAMAN EXTERNC
#else                                 // kernel
#if defined(__X64__) || defined(__NOEXPORT__)
#define IDAMAN EXTERNC
#else
#define IDAMAN EXTERNC __declspec(dllexport)
#endif
#endif
#define IDA_LOCAL
#elif defined(__UNIX__)                 // for unix
#define IDAAPI
#if defined(__MAC__)
#define IDAMAN EXTERNC
#define IDA_LOCAL
#else  // Linux
#if __GNUC__ >= 4
#define IDAMAN EXTERNC
#define IDA_LOCAL
#else
#define IDAMAN EXTERNC
#define IDA_LOCAL
#endif
#endif
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
