#ifndef MATH_HPP
#define MATH_HPP

#include "change.h"

extern "C"
{
    __declspec(dllexport) int __stdcall math_add(int a, int b);
    __declspec(dllexport) int __stdcall math_add2(int a, int b);
    __declspec(dllexport) void __stdcall coutTest();
    __declspec(dllexport) intptr_t __stdcall objNew();
    __declspec(dllexport) void __stdcall objSet(intptr_t ptr, int testint);
    __declspec(dllexport) int __stdcall objGet(intptr_t ptr);
}

#endif
