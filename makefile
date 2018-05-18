# Architecture detection
ifndef OS_DET
	ifeq ($(OS),Windows_NT)
	OS_DET = WIN
		ifeq ($(PROCESSOR_ARCHITEW6432),AMD64)
			ARCH = x86_64
		else
			ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
             	ARCH = x86_64
			endif
			ifeq ($(PROCESSOR_ARCHITECTURE),x86)
             	ARCH = x86
			endif
		endif
	else
    	UNAME_S := $(shell uname -s)
		ifeq ($(UNAME_S),Linux)
			OS_DET = LINUX
		endif
		ifeq ($(UNAME_S),Darwin)
			OS_DET = OSX
		endif
    	UNAME_P := $(shell uname -p)
		ifeq ($(UNAME_P),x86_64)
			ARCH = x86_64
		endif
		ifneq ($(filter %86,$(UNAME_P)),)
			ARCH = x86
		endif
    	ifneq ($(filter arm%,$(UNAME_P)),)
			ARCH = ARM
    	endif
	endif
endif

PROGRAM_BIN_DIR = example
PROGRAM_SHARED_LIB_DIR = example
PROGRAM_OBJ_DIR = example/obj
PROGRAM_SRC_DIR = example/src
PROGRAM_CSHARP_EXE_ENABLE = 
PROGRAM_CSHARP_EXE = $(PROGRAM_BIN_DIR)/example_csharp.exe
PROGRAM_CSHARP_BUNDLE = $(PROGRAM_BIN_DIR)/example_csharp
PROGRAM_CPP_EXE = $(PROGRAM_BIN_DIR)/example_cpp.exe
# mac app
PROGRAM_CPP_APP_NAME = example_cpp
PROGRAM_CPP_APP = $(PROGRAM_BIN_DIR)/example_cpp.app
PROGRAM_CPP_APP_ENABLE = 
PROGRAM_CPP_APP_DEL_CMD = 
# static and dynamic library
LIBRARY_INCLUDE_DIR = include
LIBRARY_DIR = bin
LIBRARY_SRC_DIR = src
LIBRARY_CPP_NAME = ResourceFileUtility
LIBRARY_CPP_HEADER = $(LIBRARY_INCLUDE_DIR)/$(LIBRARY_CPP_NAME).h
LIBRARY_CPP_ONE_HEADER = $(LIBRARY_SRC_DIR)/OneHeader.h
# OneHeader c++ program
PROGRAM_ONE_HEADER_SRC = contrib/OneHeader/src
PROGRAM_ONE_HEADER_OBJ = contrib/OneHeader/obj
PROGRAM_ONE_HEADER_BIN = contrib/OneHeader/bin
PROGRAM_ONE_HEADER_EXE_ENABLE = 
PROGRAM_ONE_HEADER_EXE = $(PROGRAM_ONE_HEADER_BIN)/OneHeader.exe
PROGRAM_ONE_HEADER_MAIN_NAME = main

ifeq ($(OS_DET),WIN)
	HOST_OS = WIN
	LIBRARY_CPP_SHARED_NAME = $(LIBRARY_CPP_NAME).dll
	LIBRARY_CPP_STATIC_NAME = lib$(LIBRARY_CPP_NAME).a
	ifeq ($(ARCH),x86)
		VERSION_NAME = win-x86-mingw
		GCC = x86_64-w64-mingw32-g++
		AR = x86_64-w64-mingw32-gcc-ar
	endif
	ifeq ($(ARCH),x86_64)
		VERSION_NAME = win-x86_64-mingw
		GCC = g++
		AR = ar
	endif
	# paths
	LIBRARY_PLATFORM_DIR = $(LIBRARY_DIR)/$(VERSION_NAME)
	LIBRARY_CPP_SHARED_BIN = $(LIBRARY_PLATFORM_DIR)/$(LIBRARY_CPP_SHARED_NAME)
	LIBRARY_CPP_STATIC_BIN = $(LIBRARY_PLATFORM_DIR)/$(LIBRARY_CPP_STATIC_NAME)
	LIBRARY_TEMP_DIR = $(VERSION_NAME)
	LIBRARY_OBJ_DIR = $(LIBRARY_TEMP_DIR)/src
	ifeq ($(ARCH),x86)
		# cpp library commands and flags
		LIBRARY_OBJ_COMPILE_FLAGS = -O3 -g3 -std=gnu++11 -Wall -c -fmessage-length=0
		SHARED_CPP_LINK_FLAGS = -lstdc++ -std=gnu++11 -static-libgcc -static-libstdc++ -static -shared
		STATIC_CPP_LINK = 
		# program c#
		PROGRAM_CSHARP_EXE_ENABLE = $(PROGRAM_CSHARP_EXE)
		CSC = csc
		CSC_FLAGS = /nologo /optimize /langversion:latest
		BUNDLE_CMD = 
		# program c++
		PROGRAM_CPP_COMPILE = -I"$(LIBRARY_INCLUDE_DIR)" -O3 -g3 -std=gnu++11 -Wall -c -fmessage-length=0
		PROGRAM_CPP_LINK = -static-libgcc -static-libstdc++ -L"$(LIBRARY_PLATFORM_DIR)"
		PROGRAM_CPP_LIBS = -lResourceFileUtility
		# OneHeader c++
		PROGRAM_ONE_HEADER_COMPILE_FLAGS = -O3 -g3 -std=gnu++11 -Wall -fmessage-length=0
		PROGRAM_ONE_HEADER_LINK_FLAGS = -static-libgcc -static-libstdc++
	endif
	ifeq ($(ARCH),x86_64)
		# cpp library commands and flags
		LIBRARY_OBJ_COMPILE_FLAGS = -O3 -g3 -std=gnu++11 -Wall -fmessage-length=0
		SHARED_CPP_LINK_FLAGS = -static-libgcc -static-libstdc++ -static -shared
		STATIC_CPP_LINK = 
		# program c#
		PROGRAM_CSHARP_EXE_ENABLE = $(PROGRAM_CSHARP_EXE)
		CSC = csc
		CSC_FLAGS = /nologo /optimize /langversion:latest
		BUNDLE_CMD = 
		# program c++
		PROGRAM_CPP_COMPILE = -I"$(LIBRARY_INCLUDE_DIR)" -O3 -g3 -std=gnu++11 -Wall -c -fmessage-length=0
		PROGRAM_CPP_LINK = -static-libgcc -static-libstdc++ -L"$(LIBRARY_PLATFORM_DIR)"
		PROGRAM_CPP_LIBS = -lResourceFileUtility
		# OneHeader c++
		PROGRAM_ONE_HEADER_COMPILE_FLAGS = -O3 -g3 -std=gnu++11 -Wall -fmessage-length=0
		PROGRAM_ONE_HEADER_LINK_FLAGS = -static-libgcc -static-libstdc++
	endif
endif
ifeq ($(OS_DET),android)
	HOST_OS = WIN
	# paths
	LIBRARY_CPP_SHARED_NAME = lib$(LIBRARY_CPP_NAME).dll
	LIBRARY_CPP_STATIC_NAME = lib$(LIBRARY_CPP_NAME).a
	ifeq ($(ARCH),armeabi)
		VERSION_NAME = android-armeabi
		GCC = arm-linux-androideabi-g++
		AR = arm-linux-androideabi-ar
	endif
	ifeq ($(ARCH),armeabi-v7a)
		VERSION_NAME = android-armeabi-v7a
		GCC = arm-linux-androideabi-g++
		AR = arm-linux-androideabi-ar
	endif
	ifeq ($(ARCH),arm64-v8a)
		VERSION_NAME = android-aarch64
		GCC = aarch64-linux-android-g++
		AR = aarch64-linux-android-ar
	endif
		LIBRARY_PLATFORM_DIR = $(LIBRARY_DIR)/$(VERSION_NAME)
		LIBRARY_CPP_SHARED_BIN = $(LIBRARY_PLATFORM_DIR)/$(LIBRARY_CPP_SHARED_NAME)
		LIBRARY_CPP_STATIC_BIN = $(LIBRARY_PLATFORM_DIR)/$(LIBRARY_CPP_STATIC_NAME)
		LIBRARY_SRC_DIR = src
		LIBRARY_TEMP_DIR = $(VERSION_NAME)
		LIBRARY_OBJ_DIR = $(LIBRARY_TEMP_DIR)/src
	ifeq ($(ARCH),armeabi-v7a)
		# cpp library commands and flags
		LIBRARY_OBJ_COMPILE_INCLUDES =  -I"$(NDK_PATH)/sources/cxx-stl/gnu-libstdc++/4.9/libs/armeabi-v7a/include" -I"$(NDK_PATH)/sources/cxx-stl/gnu-libstdc++/4.9/include" -I"$(NDK_PATH)/sysroot/usr/include" -I"$(NDK_PATH)/sysroot/usr/include/arm-linux-androideabi"
		LIBRARY_OBJ_COMPILE_FLAGS = $(LIBRARY_OBJ_COMPILE_INCLUDES) -O3 -g3 -std=gnu++11 -Wall -c -fmessage-length=0 
		SHARED_CPP_LINK_FLAGS = --sysroot="$(NDK_PATH)/platforms/android-21/arch-arm" -static-libgcc -static-libstdc++ -static -shared
		STATIC_CPP_LINK = 
		# program c#
		CSC = csc
		CSC_FLAGS = /nologo /optimize /langversion:latest
		BUNDLE_CMD = 
		# program c++
		PROGRAM_CPP_COMPILE_INCLUDES = -I"$(NDK_PATH)/sources/cxx-stl/gnu-libstdc++/4.9/libs/armeabi-v7a/include" -I"$(NDK_PATH)/sources/cxx-stl/gnu-libstdc++/4.9/include" -I"$(NDK_PATH)/sysroot/usr/include" -I"$(NDK_PATH)/sysroot/usr/include/arm-linux-androideabi"
		PROGRAM_CPP_COMPILE = $(PROGRAM_CPP_COMPILE_INCLUDES) -I"$(LIBRARY_INCLUDE_DIR)" -I"$(NDK_PATH)/sysroot/usr/include" -O3 -g3 -std=gnu++11 -Wall -c -fmessage-length=0
		PROGRAM_CPP_LINK = --sysroot="$(NDK_PATH)/platforms/android-21/arch-arm" -static-libgcc -static-libstdc++ -static -L"$(LIBRARY_PLATFORM_DIR)"
		PROGRAM_CPP_LIBS = -lResourceFileUtility
	endif
	ifeq ($(ARCH),arm64-v8a)
		# cpp library commands and flags
		LIBRARY_OBJ_COMPILE_INCLUDES =  --sysroot="$(NDK_PATH)/platforms/android-21/arch-arm64" -I"$(NDK_PATH)/sources/cxx-stl/gnu-libstdc++/4.9/libs/arm64-v8a/include" -I"$(NDK_PATH)/sources/cxx-stl/gnu-libstdc++/4.9/include" -I"$(NDK_PATH)/sysroot/usr/include" -I"$(NDK_PATH)/sysroot/usr/include/aarch64-linux-android"
		LIBRARY_OBJ_COMPILE_FLAGS = $(LIBRARY_OBJ_COMPILE_INCLUDES) -O3 -g3 -std=gnu++11 -Wall -c -fmessage-length=0 
		SHARED_CPP_LINK_FLAGS = --sysroot="$(NDK_PATH)/platforms/android-21/arch-arm64" -static-libgcc -static-libstdc++ -static -shared
		STATIC_CPP_LINK = 
		# program c#
		CSC = csc
		CSC_FLAGS = /nologo /optimize /langversion:latest
		BUNDLE_CMD = 
		# program c++
		PROGRAM_CPP_COMPILE_INCLUDES = -I"$(NDK_PATH)/sources/cxx-stl/gnu-libstdc++/4.9/libs/arm64-v8a/include" -I"$(NDK_PATH)/sources/cxx-stl/gnu-libstdc++/4.9/include" -I"$(NDK_PATH)/sysroot/usr/include" -I"$(NDK_PATH)/sysroot/usr/include/aarch64-linux-android"
		PROGRAM_CPP_COMPILE = $(PROGRAM_CPP_COMPILE_INCLUDES) -I"$(LIBRARY_INCLUDE_DIR)" -I"$(NDK_PATH)/sysroot/usr/include" -O3 -g3 -std=gnu++11 -Wall -c -fmessage-length=0
		PROGRAM_CPP_LINK = --sysroot="$(NDK_PATH)/platforms/android-21/arch-arm64" -static-libgcc -static-libstdc++ -static -L"$(LIBRARY_PLATFORM_DIR)"
		PROGRAM_CPP_LIBS = -lResourceFileUtility
	endif
endif
ifeq ($(OS_DET),LINUX)
	HOST_OS = UNIX
	ifeq ($(ARCH),x86)
		LIBRARY_CPP_SHARED_NAME = lib$(LIBRARY_CPP_NAME).so
		LIBRARY_CPP_STATIC_NAME = lib$(LIBRARY_CPP_NAME).a
		VERSION_NAME = linuxDebian-x86-gcc
		GCC = g++
		AR = ar
	endif
	ifeq ($(ARCH),x86_64)
		LIBRARY_CPP_SHARED_NAME = lib$(LIBRARY_CPP_NAME).so
		LIBRARY_CPP_STATIC_NAME = lib$(LIBRARY_CPP_NAME).a
		VERSION_NAME = linuxDebian-x86_64-gcc
		GCC = gcc
		AR = ar
	endif
	# paths
	LIBRARY_PLATFORM_DIR = $(LIBRARY_DIR)/$(VERSION_NAME)
	LIBRARY_CPP_SHARED_BIN = $(LIBRARY_PLATFORM_DIR)/$(LIBRARY_CPP_SHARED_NAME)
	LIBRARY_CPP_STATIC_BIN = $(LIBRARY_PLATFORM_DIR)/$(LIBRARY_CPP_STATIC_NAME)
	LIBRARY_TEMP_DIR = $(VERSION_NAME)
	LIBRARY_OBJ_DIR = $(LIBRARY_TEMP_DIR)/src
	ifeq ($(ARCH),x86)
		# cpp library commands and flags
		LIBRARY_OBJ_COMPILE_FLAGS = -m32 -O3 -g3 -std=gnu++11 -Wall -c -fmessage-length=0
		SHARED_CPP_LINK_FLAGS = -m32 -lstdc++ -std=gnu++11 -static-libgcc -static-libstdc++ -static -shared
		STATIC_CPP_LINK = 
		# program c#
		CSC = csc
		CSC_FLAGS = /nologo /optimize /langversion:latest
		BUNDLE_CMD = 
		# program c++
		PROGRAM_CPP_COMPILE = -m32 -I"$(LIBRARY_INCLUDE_DIR)" -O3 -g3 -std=gnu++11 -Wall -c -fmessage-length=0
		PROGRAM_CPP_LINK = -m32 -lstdc++ -static-libgcc -static-libstdc++ -L"$(LIBRARY_PLATFORM_DIR)"
		PROGRAM_CPP_LIBS = -lResourceFileUtility
	endif
	ifeq ($(ARCH),x86_64)
		# cpp library commands and flags
		LIBRARY_OBJ_COMPILE_FLAGS = -fPIC -O3 -g3 -std=gnu++11 -Wall -c
		SHARED_CPP_LINK_FLAGS = -fPIC -static-libgcc -static-libstdc++ -static -shared
		STATIC_CPP_LINK = 
		# program c#
		CSC = csc
		CSC_FLAGS = /nologo /optimize /langversion:latest
		BUNDLE_CMD = 
		# program c++
		PROGRAM_CPP_COMPILE = -fPIC -I"$(LIBRARY_INCLUDE_DIR)" -O3 -g3 -std=gnu++11 -Wall -c -fmessage-length=0
		PROGRAM_CPP_LINK = -fPIC -static-libgcc -static-libstdc++ -static -L"$(LIBRARY_PLATFORM_DIR)"
		PROGRAM_CPP_LIBS = -lResourceFileUtility
	endif
endif
ifeq ($(OS_DET),OSX)
	HOST_OS = UNIX
	# paths
	LIBRARY_CPP_SHARED_NAME = lib$(LIBRARY_CPP_NAME).dll
	LIBRARY_CPP_STATIC_NAME = lib$(LIBRARY_CPP_NAME).a
	VERSION_NAME = macOS-x86_64-clang
	LIBRARY_PLATFORM_DIR = $(LIBRARY_DIR)/$(VERSION_NAME)
	LIBRARY_CPP_SHARED_BIN = $(LIBRARY_PLATFORM_DIR)/$(LIBRARY_CPP_SHARED_NAME)
	LIBRARY_CPP_STATIC_BIN = $(LIBRARY_PLATFORM_DIR)/$(LIBRARY_CPP_STATIC_NAME)
	LIBRARY_TEMP_DIR = $(VERSION_NAME)
	LIBRARY_OBJ_DIR = $(LIBRARY_TEMP_DIR)/src
	# cpp library commands and flags
	GCC = g++
	LIBRARY_OBJ_COMPILE_FLAGS = -O3 -g3 -fPIC -std=gnu++11 -Wall -fvisibility=hidden -c -fmessage-length=0 -mmacosx-version-min=10.9
	SHARED_CPP_LINK_FLAGS = -dynamiclib -fPIC -std=gnu++11 -current_version 1.0 -compatibility_version 1.0 -fvisibility=hidden -mmacosx-version-min=10.9
	AR = ar
	STATIC_CPP_LINK = 
	# program c#
	CSC = csc
	CSC_FLAGS = /nologo /optimize /langversion:latest /lib:example/src
	BUNDLE_CMD = mkbundle -o $(PROGRAM_CSHARP_BUNDLE) --simple $(PROGRAM_CSHARP_EXE) --library $(LIBRARY_CPP_SHARED_BIN)
	# program c++
	PROGRAM_CPP_COMPILE = -I"$(LIBRARY_INCLUDE_DIR)" -O3 -g3 -std=gnu++11 -Wall -c -fmessage-length=0 -mmacosx-version-min=10.9
	PROGRAM_CPP_LINK = -L"$(LIBRARY_PLATFORM_DIR)" -mmacosx-version-min=10.9
	PROGRAM_CPP_LIBS = -lResourceFileUtility
	# mac app
	PROGRAM_CPP_APP_ENABLE = $(PROGRAM_CPP_APP)
endif
ifeq ($(OS_DET),IOS)
	HOST_OS = UNIX
	# paths
	LIBRARY_CPP_SHARED_NAME = lib$(LIBRARY_CPP_NAME).so
	LIBRARY_CPP_STATIC_NAME = lib$(LIBRARY_CPP_NAME).a
	ifeq ($(ARCH),armv7)
		VERSION_NAME = ios-armv7
		GCC = clang++
		AR = ar
		iPhoneSDK = /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS10.3.sdk
		iPhoneSDKLibs = lib/ios
		ios_arch = armv7
	endif
	ifeq ($(ARCH),armv7s)
		VERSION_NAME = ios-armv7s
		GCC = clang++
		AR = ar
		iPhoneSDK = /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS10.3.sdk
		iPhoneSDKLibs = lib/ios
		ios_arch = armv7s
	endif
	ifeq ($(ARCH),arm64)
		VERSION_NAME = ios-arm64
		GCC = clang++
		AR = ar
		iPhoneSDK = /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS10.3.sdk
		iPhoneSDKLibs = lib/ios
		ios_arch = arm64
	endif
		LIBRARY_PLATFORM_DIR = $(LIBRARY_DIR)/$(VERSION_NAME)
		LIBRARY_CPP_SHARED_BIN = $(LIBRARY_PLATFORM_DIR)/$(LIBRARY_CPP_SHARED_NAME)
		LIBRARY_CPP_STATIC_BIN = $(LIBRARY_PLATFORM_DIR)/$(LIBRARY_CPP_STATIC_NAME)
		LIBRARY_TEMP_DIR = $(VERSION_NAME)
		LIBRARY_OBJ_DIR = $(LIBRARY_TEMP_DIR)/src
	ifeq ($(ARCH),armv7)
		# cpp library commands and flags
		GCC = clang++
		LIBRARY_OBJ_COMPILE_INCLUDES =  
		LIBRARY_OBJ_COMPILE_FLAGS = $(LIBRARY_OBJ_COMPILE_INCLUDES) -O3 -g3 -std=gnu++11 -stdlib=libc++ -Wall -c -fmessage-length=0 -arch $(ios_arch) -mios-version-min=5.0 -isysroot $(iPhoneSDK)
		SHARED_CPP_LINK_FLAGS = -std=gnu++11 -stdlib=libc++ -static -shared -undefined dynamic_lookup -arch $(ios_arch) -mios-version-min=5.0 -isysroot $(iPhoneSDK)
		STATIC_CPP_LINK =
		# program c#
		CSC = csc
		CSC_FLAGS = /nologo /optimize /langversion:latest
		BUNDLE_CMD = 
		# program c++
		PROGRAM_CPP_COMPILE_INCLUDES = 
		PROGRAM_CPP_COMPILE = $(PROGRAM_CPP_COMPILE_INCLUDES) -I"$(LIBRARY_INCLUDE_DIR)" -O3 -g3 -std=gnu++11 -stdlib=libc++ -Wall -c -fmessage-length=0 -arch $(ios_arch) -mios-version-min=5.0 -isysroot $(iPhoneSDK)
		PROGRAM_CPP_LINK = -std=gnu++11 -stdlib=libc++ -L"$(LIBRARY_PLATFORM_DIR)" -L"$(iPhoneSDKLibs)" -undefined dynamic_lookup -arch $(ios_arch) -mios-version-min=5.0 -isysroot $(iPhoneSDK)
		PROGRAM_CPP_LIBS = -lResourceFileUtility
	endif
	ifeq ($(ARCH),armv7s)
		# cpp library commands and flags
		GCC = clang++
		LIBRARY_OBJ_COMPILE_INCLUDES =  
		LIBRARY_OBJ_COMPILE_FLAGS = $(LIBRARY_OBJ_COMPILE_INCLUDES) -O3 -g3 -std=gnu++11 -stdlib=libc++ -Wall -c -fmessage-length=0 -arch $(ios_arch) -mios-version-min=5.0 -isysroot $(iPhoneSDK)
		SHARED_CPP_LINK_FLAGS = -std=gnu++11 -stdlib=libc++ -static -shared -undefined dynamic_lookup -arch $(ios_arch) -mios-version-min=5.0 -isysroot $(iPhoneSDK)
		STATIC_CPP_LINK =
		# program c#
		CSC = csc
		CSC_FLAGS = /nologo /optimize /langversion:latest
		BUNDLE_CMD = 
		# program c++
		PROGRAM_CPP_COMPILE_INCLUDES = 
		PROGRAM_CPP_COMPILE = $(PROGRAM_CPP_COMPILE_INCLUDES) -I"$(LIBRARY_INCLUDE_DIR)" -O3 -g3 -std=gnu++11 -stdlib=libc++ -Wall -c -fmessage-length=0 -arch $(ios_arch) -mios-version-min=5.0 -isysroot $(iPhoneSDK)
		PROGRAM_CPP_LINK = -std=gnu++11 -stdlib=libc++ -L"$(LIBRARY_PLATFORM_DIR)" -L"$(iPhoneSDKLibs)" -undefined dynamic_lookup -arch $(ios_arch) -mios-version-min=5.0 -isysroot $(iPhoneSDK)
		PROGRAM_CPP_LIBS = -lResourceFileUtility
	endif
	ifeq ($(ARCH),arm64)
		# cpp library commands and flags
		GCC = clang++
		LIBRARY_OBJ_COMPILE_INCLUDES =  
		LIBRARY_OBJ_COMPILE_FLAGS = $(LIBRARY_OBJ_COMPILE_INCLUDES) -O3 -g3 -std=gnu++11 -stdlib=libc++ -Wall -c -fmessage-length=0 -arch $(ios_arch) -mios-version-min=5.0 -isysroot $(iPhoneSDK)
		SHARED_CPP_LINK_FLAGS = -std=gnu++11 -stdlib=libc++ -static -shared -undefined dynamic_lookup -arch $(ios_arch) -mios-version-min=5.0 -isysroot $(iPhoneSDK)
		STATIC_CPP_LINK =
		# program c#
		CSC = csc
		CSC_FLAGS = /nologo /optimize /langversion:latest
		BUNDLE_CMD = 
		# program c++
		PROGRAM_CPP_COMPILE_INCLUDES = 
		PROGRAM_CPP_COMPILE = $(PROGRAM_CPP_COMPILE_INCLUDES) -I"$(LIBRARY_INCLUDE_DIR)" -O3 -g3 -std=gnu++11 -stdlib=libc++ -Wall -c -fmessage-length=0 -arch $(ios_arch) -mios-version-min=5.0 -isysroot $(iPhoneSDK)
		PROGRAM_CPP_LINK = -std=gnu++11 -stdlib=libc++ -L"$(LIBRARY_PLATFORM_DIR)" -L"$(iPhoneSDKLibs)" -undefined dynamic_lookup -arch $(ios_arch) -mios-version-min=5.0 -isysroot $(iPhoneSDK)
		PROGRAM_CPP_LIBS = -lResourceFileUtility
	endif
endif

ifeq ($(HOST_OS),WIN)
	# backslash
	LIBRARY_OBJ_DIR_BACKSLASH = $(subst /,\\,$(LIBRARY_OBJ_DIR))
	LIBRARY_TEMP_DIR_BACKSLASH = $(subst /,\\,$(LIBRARY_TEMP_DIR))
	LIBRARY_PLATFORM_DIR_BACKSLASH= $(subst /,\\,$(LIBRARY_PLATFORM_DIR))
	LIBRARY_CPP_SHARED_BIN_BACKSLASH= $(subst /,\\,$(LIBRARY_CPP_SHARED_BIN))
	LIBRARY_CPP_STATIC_BIN_BACKSLASH= $(subst /,\\,$(LIBRARY_CPP_STATIC_BIN))
	PROGRAM_CSHARP_EXE_BACKSLASH= $(subst /,\\,$(PROGRAM_CSHARP_EXE))
	PROGRAM_CSHARP_BUNDLE_BACKSLASH= $(subst /,\\,$(PROGRAM_CSHARP_BUNDLE))
	PROGRAM_CPP_EXE_BACKSLASH=$(subst /,\\,$(PROGRAM_CPP_EXE))
	PROGRAM_OBJ_DIR_BACKSLASH=$(subst /,\\,$(PROGRAM_OBJ_DIR))
	LIBRARY_CPP_HEADER_BACKSLASH=$(subst /,\\,$(LIBRARY_CPP_HEADER))
	PROGRAM_ONE_HEADER_EXE_BACKSLASH=$(subst /,\\,$(PROGRAM_ONE_HEADER_EXE))
	# commands
	LIBRARY_OBJ_DIR_CMD = if not exist "$(LIBRARY_OBJ_DIR_BACKSLASH)" mkdir $(LIBRARY_OBJ_DIR_BACKSLASH)
	LIBRARY_PLATFORM_DIR_CMD = if not exist "$(LIBRARY_PLATFORM_DIR_BACKSLASH)" mkdir $(LIBRARY_PLATFORM_DIR_BACKSLASH)
	PROGRAM_OBJ_DIR_CMD = if not exist "$(PROGRAM_OBJ_DIR_BACKSLASH)" mkdir $(PROGRAM_OBJ_DIR_BACKSLASH)
	COPY_SHARED_LIBRARY_CMD = copy $(LIBRARY_CPP_SHARED_BIN_BACKSLASH) $(PROGRAM_BIN_DIR) /Y
	LIBRARY_TEMP_DIR_DEL = if exist "$(LIBRARY_TEMP_DIR_BACKSLASH)" rd /s /q "$(LIBRARY_TEMP_DIR_BACKSLASH)"
	PROGRAM_OBJ_DIR_DEL = if exist "$(PROGRAM_OBJ_DIR_BACKSLASH)" rd /s /q "$(PROGRAM_OBJ_DIR_BACKSLASH)"
	SHARED_LIBRARY_DEL_CMD = if exist "$(LIBRARY_CPP_SHARED_BIN_BACKSLASH)" del /F /Q "$(LIBRARY_CPP_SHARED_BIN_BACKSLASH)"
	STATIC_LIBRARY_DEL_CMD = if exist "$(LIBRARY_CPP_STATIC_BIN_BACKSLASH)" del /F /Q "$(LIBRARY_CPP_STATIC_BIN_BACKSLASH)"
	PROGRAM_CSHARP_DEL_CMD = if exist "$(PROGRAM_CSHARP_EXE_BACKSLASH)" del /F /Q "$(PROGRAM_CSHARP_EXE_BACKSLASH)"
	PROGRAM_CSHARP_DEL_POST_CMD = 
	BUNDLE_CSHARP_DEL_CMD = if exist "$(PROGRAM_CSHARP_BUNDLE_BACKSLASH)" del /F /Q "$(PROGRAM_CSHARP_BUNDLE_BACKSLASH)"
	PROGRAM_CPP_DEL_CMD = if exist "$(PROGRAM_CPP_EXE_BACKSLASH)" del /F /Q "$(PROGRAM_CPP_EXE_BACKSLASH)"
	#SHARED_LIBRARY_HEADER_CMD = type $(LIBRARY_SRC_DIR)\mingw_threads.h >> $(LIBRARY_CPP_HEADER_BACKSLASH) 2>NUL & \
	#	type $(LIBRARY_SRC_DIR)\ResourceFile.h >> $(LIBRARY_CPP_HEADER_BACKSLASH) 2>NUL & \
	#	type $(LIBRARY_SRC_DIR)\*.h >> $(LIBRARY_CPP_HEADER_BACKSLASH) 2>NUL
	SHARED_LIBRARY_HEADER_DEL_CMD = if exist "$(LIBRARY_CPP_HEADER_BACKSLASH)" del /F /Q "$(LIBRARY_CPP_HEADER_BACKSLASH)"
	PROGRAM_ONE_HEADER_EXE_DEL_CMD = if exist "$(PROGRAM_ONE_HEADER_EXE_BACKSLASH)" del /F /Q "$(PROGRAM_ONE_HEADER_EXE_BACKSLASH)"
endif
ifeq ($(HOST_OS),UNIX)
	# commands
	LIBRARY_OBJ_DIR_CMD = mkdir -p $(LIBRARY_OBJ_DIR)
	LIBRARY_PLATFORM_DIR_CMD = mkdir -p $(LIBRARY_PLATFORM_DIR)
	PROGRAM_OBJ_DIR_CMD = mkdir -p $(PROGRAM_OBJ_DIR)
	COPY_SHARED_LIBRARY_CMD_UNUSED = yes | cp -rf $(LIBRARY_CPP_SHARED_BIN) $(PROGRAM_BIN_DIR)
	COPY_SHARED_LIBRARY_CMD = 
	LIBRARY_TEMP_DIR_DEL = yes | rm -rf $(LIBRARY_TEMP_DIR)
	PROGRAM_OBJ_DIR_DEL = yes | rm -rf $(PROGRAM_OBJ_DIR)
	SHARED_LIBRARY_DEL_CMD = yes | rm -f "$(LIBRARY_CPP_SHARED_BIN)"
	STATIC_LIBRARY_DEL_CMD = yes | rm -f "$(LIBRARY_CPP_STATIC_BIN)"
	PROGRAM_CSHARP_DEL_CMD = yes | rm -f "$(PROGRAM_CSHARP_EXE)"
	PROGRAM_CSHARP_DEL_POST_CMD = $(PROGRAM_CSHARP_DEL_CMD)
	BUNDLE_CSHARP_DEL_CMD = yes | rm -f "$(PROGRAM_CSHARP_BUNDLE)"
	PROGRAM_CPP_DEL_CMD = yes | rm -f "$(PROGRAM_CPP_EXE)"
	PROGRAM_CPP_APP_DEL_CMD = yes | rm -rf "$(PROGRAM_CPP_APP)"
	#SHARED_LIBRARY_HEADER_CMD = cat $(LIBRARY_SRC_DIR)/*.h >> $(LIBRARY_CPP_HEADER)
	SHARED_LIBRARY_HEADER_DEL_CMD = yes | rm -f "$(LIBRARY_CPP_HEADER)"
	PROGRAM_ONE_HEADER_EXE_DEL_CMD = yes | rm -f "$(PROGRAM_ONE_HEADER_EXE)"
endif

LIBRARY_SRC_FILES := $(wildcard $(LIBRARY_SRC_DIR)/*.cpp)
LIBRARY_OBJ_FILES := $(patsubst $(LIBRARY_SRC_DIR)/%.cpp,$(LIBRARY_OBJ_DIR)/%.o,$(LIBRARY_SRC_FILES))
PROGRAM_SRC_FILES := $(wildcard $(PROGRAM_SRC_DIR)/*.cpp)
PROGRAM_OBJ_FILES := $(patsubst $(PROGRAM_SRC_DIR)/%.cpp,$(PROGRAM_OBJ_DIR)/%.o,$(PROGRAM_SRC_FILES))

EXAMPLE_SRC = *.cs
EXTRA_SRC = ResourceFileUtility.cs

all: directories $(PROGRAM_ONE_HEADER_EXE) one_header $(LIBRARY_CPP_STATIC_BIN) $(LIBRARY_CPP_SHARED_BIN) $(PROGRAM_CPP_EXE) $(PROGRAM_CSHARP_EXE_ENABLE) $(PROGRAM_CPP_APP_ENABLE)

$(PROGRAM_CSHARP_EXE_ENABLE):
	$(CSC) $(CSC_FLAGS) /out:$@ /t:exe -lib:$(PROGRAM_SHARED_LIB_DIR) $(LIBRARY_INCLUDE_DIR)/$(EXTRA_SRC) $(PROGRAM_SRC_DIR)/*.cs
	$(COPY_SHARED_LIBRARY_CMD)
	$(BUNDLE_CMD)
	$(PROGRAM_CSHARP_DEL_POST_CMD)
	$(LIBRARY_TEMP_DIR_DEL)
	
$(LIBRARY_CPP_SHARED_BIN): $(LIBRARY_OBJ_FILES)
	$(GCC) $(SHARED_CPP_LINK_FLAGS) -o $@ $^
	
$(LIBRARY_CPP_STATIC_BIN): $(LIBRARY_OBJ_FILES)
	$(AR) rcs $@ $^ $(STATIC_CPP_LINK)

$(LIBRARY_OBJ_DIR)/%.o: $(LIBRARY_SRC_DIR)/%.cpp
	$(GCC) $(LIBRARY_OBJ_COMPILE_FLAGS) -c -o $@ $<
	
$(PROGRAM_CPP_EXE): $(PROGRAM_OBJ_FILES)
	$(GCC) $(PROGRAM_CPP_LINK) -o $@ $^ $(PROGRAM_CPP_LIBS)
	$(PROGRAM_OBJ_DIR_DEL)
	
$(PROGRAM_OBJ_DIR)/%.o: $(PROGRAM_SRC_DIR)/%.cpp
	$(GCC) $(PROGRAM_CPP_COMPILE) -c -o $@ $<

$(PROGRAM_CPP_APP):
	yes | rm -rf "$(PROGRAM_CPP_APP)"
	mkdir -p $(PROGRAM_CPP_APP)/Contents/MacOS
	mkdir -p $(PROGRAM_CPP_APP)/Contents/Resources
	cp $(PROGRAM_SRC_DIR)/Info.plist "$(PROGRAM_CPP_APP)/Contents/"
	cp $(PROGRAM_CPP_EXE) "$(PROGRAM_CPP_APP)/Contents/MacOS/$(PROGRAM_CPP_APP_NAME)"

$(PROGRAM_ONE_HEADER_EXE):
	$(GCC) $(PROGRAM_ONE_HEADER_COMPILE_FLAGS) $(PROGRAM_ONE_HEADER_LINK_FLAGS) -o $@ $(PROGRAM_ONE_HEADER_SRC)/$(PROGRAM_ONE_HEADER_MAIN_NAME).cpp
	
one_header:
	$(SHARED_LIBRARY_HEADER_DEL_CMD)
	$(PROGRAM_ONE_HEADER_EXE) $(LIBRARY_CPP_ONE_HEADER) $(LIBRARY_CPP_HEADER)
	
directories:
	$(PROGRAM_ONE_HEADER_EXE_DEL_CMD)
	$(PROGRAM_CPP_APP_DEL_CMD)
	$(LIBRARY_TEMP_DIR_DEL)
	$(PROGRAM_OBJ_DIR_DEL)
	$(LIBRARY_OBJ_DIR_CMD)
	$(PROGRAM_OBJ_DIR_CMD)
	$(LIBRARY_PLATFORM_DIR_CMD)
	$(SHARED_LIBRARY_DEL_CMD)
	$(STATIC_LIBRARY_DEL_CMD)
	$(PROGRAM_CSHARP_DEL_CMD)
	$(BUNDLE_CSHARP_DEL_CMD)
	$(PROGRAM_CPP_DEL_CMD)

clean:
	$(LIBRARY_TEMP_DIR_DEL)
	$(PROGRAM_OBJ_DIR_DEL)
	$(SHARED_LIBRARY_DEL_CMD)
	$(STATIC_LIBRARY_DEL_CMD)
	$(PROGRAM_CSHARP_DEL_CMD)
	$(BUNDLE_CSHARP_DEL_CMD)
	$(PROGRAM_CPP_DEL_CMD)
