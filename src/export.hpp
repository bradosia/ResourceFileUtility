#ifndef MATH_HPP
#define MATH_HPP

#include "compiler.h"

extern "C"
{
    __declspec(dllexport) int __stdcall math_add(int a, int b);
    __declspec(dllexport) int __stdcall math_add2(int a, int b);
    __declspec(dllexport) void __stdcall coutTest();
    __declspec(dllexport) intptr_t __stdcall compile_new();
    __declspec(dllexport) void __stdcall objSet(intptr_t ptr, int testint);
    __declspec(dllexport) int __stdcall objGet(intptr_t ptr);
    __declspec(dllexport) void __stdcall compile_info(intptr_t ptr, char* fileName);
}

#endif
