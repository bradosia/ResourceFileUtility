# Architecture detection
ifndef OS_DET
	ifeq ($(OS),Windows_NT)
	OS_DET = WIN32
		ifeq ($(PROCESSOR_ARCHITEW6432),AMD64)
			ARCH = AMD64
		else
			ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
             	ARCH = AMD64
			endif
			ifeq ($(PROCESSOR_ARCHITECTURE),x86)
             	ARCH = IA32
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
			ARCH = AMD64
		endif
		ifneq ($(filter %86,$(UNAME_P)),)
			ARCH = IA32
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
PROGRAM_INC_DIR = include
LIBRARY_DIR = bin
PROGRAM_CSHARP_EXE = $(PROGRAM_BIN_DIR)/example_csharp.exe
PROGRAM_CSHARP_BUNDLE = $(PROGRAM_BIN_DIR)/example_csharp
PROGRAM_CPP_EXE = $(PROGRAM_BIN_DIR)/example_cpp.exe
PROGRAM_CPP_APP_NAME = example_cpp
PROGRAM_CPP_APP = $(PROGRAM_BIN_DIR)/example_cpp.app
PROGRAM_CPP_APP_ENABLE = 
PROGRAM_CPP_APP_DEL_CMD = 

ifeq ($(OS_DET),WIN32)
	SHARED_CPP_NAME = ResourceFileUtility.dll
	STATIC_CPP_NAME = libResourceFileUtility.a
	ifeq ($(ARCH),IA32)
		# paths
		VERSION_NAME = win32_mingw
		LIBRARY_PLATFORM_DIR = $(LIBRARY_DIR)/$(VERSION_NAME)
		SHARED_CPP_PATH = $(LIBRARY_PLATFORM_DIR)/$(SHARED_CPP_NAME)
		STATIC_CPP_PATH = $(LIBRARY_PLATFORM_DIR)/$(STATIC_CPP_NAME)
		LIBRARY_SRC_DIR = src
		LIBRARY_TEMP_DIR = $(VERSION_NAME)
		LIBRARY_OBJ_DIR = $(LIBRARY_TEMP_DIR)/src
		# cpp library commands and flags
		GCC = g++
		LIBRARY_OBJ_COMPILE_FLAGS = -O3 -g3 -std=gnu++11 -Wall -c -fmessage-length=0
		SHARED_CPP_LINK_FLAGS = -static-libgcc -static-libstdc++ -static -shared
		AR = ar
		STATIC_CPP_LINK = 
		# program c#
		CSC = csc
		CSC_FLAGS = /nologo /optimize /langversion:latest
		BUNDLE_CMD = 
		# program c++
		PROGRAM_CPP_COMPILE = -I"$(PROGRAM_INC_DIR)" -O3 -g3 -std=gnu++11 -Wall -c -fmessage-length=0
		PROGRAM_CPP_LINK = -static-libgcc -static-libstdc++ -static -L"$(LIBRARY_PLATFORM_DIR)"
		PROGRAM_CPP_LIBS = -lResourceFileUtility
		# backslash
		LIBRARY_OBJ_DIR_BACKSLASH = $(subst /,\\,$(LIBRARY_OBJ_DIR))
		LIBRARY_TEMP_DIR_BACKSLASH = $(subst /,\\,$(LIBRARY_TEMP_DIR))
		LIBRARY_PLATFORM_DIR_BACKSLASH= $(subst /,\\,$(LIBRARY_PLATFORM_DIR))
		SHARED_CPP_PATH_BACKSLASH= $(subst /,\\,$(SHARED_CPP_PATH))
		STATIC_CPP_PATH_BACKSLASH= $(subst /,\\,$(STATIC_CPP_PATH))
		PROGRAM_CSHARP_EXE_BACKSLASH= $(subst /,\\,$(PROGRAM_CSHARP_EXE))
		PROGRAM_CSHARP_BUNDLE_BACKSLASH= $(subst /,\\,$(PROGRAM_CSHARP_BUNDLE))
		PROGRAM_CPP_EXE_BACKSLASH=$(subst /,\\,$(PROGRAM_CPP_EXE))
		PROGRAM_OBJ_DIR_BACKSLASH=$(subst /,\\,$(PROGRAM_OBJ_DIR))
		# commands
		LIBRARY_OBJ_DIR_CMD = if not exist "$(LIBRARY_OBJ_DIR_BACKSLASH)" mkdir $(LIBRARY_OBJ_DIR_BACKSLASH)
		LIBRARY_PLATFORM_DIR_CMD = if not exist "$(LIBRARY_PLATFORM_DIR_BACKSLASH)" mkdir $(LIBRARY_PLATFORM_DIR_BACKSLASH)
		PROGRAM_OBJ_DIR_CMD = if not exist "$(PROGRAM_OBJ_DIR_BACKSLASH)" mkdir $(PROGRAM_OBJ_DIR_BACKSLASH)
		COPY_SHARED_LIBRARY_CMD = copy $(SHARED_CPP_PATH_BACKSLASH) $(PROGRAM_BIN_DIR) /Y
		LIBRARY_TEMP_DIR_DEL = if exist "$(LIBRARY_TEMP_DIR_BACKSLASH)" rd /s /q "$(LIBRARY_TEMP_DIR_BACKSLASH)"
		PROGRAM_OBJ_DIR_DEL = if exist "$(PROGRAM_OBJ_DIR_BACKSLASH)" rd /s /q "$(PROGRAM_OBJ_DIR_BACKSLASH)"
		SHARED_LIBRARY_DEL_CMD = if exist "$(SHARED_CPP_PATH_BACKSLASH)" del /F /Q "$(SHARED_CPP_PATH_BACKSLASH)"
		STATIC_LIBRARY_DEL_CMD = if exist "$(STATIC_CPP_PATH_BACKSLASH)" del /F /Q "$(STATIC_CPP_PATH_BACKSLASH)"
		PROGRAM_CSHARP_DEL_CMD = if exist "$(PROGRAM_CSHARP_EXE_BACKSLASH)" del /F /Q "$(PROGRAM_CSHARP_EXE_BACKSLASH)"
		PROGRAM_CSHARP_DEL_POST_CMD = 
		BUNDLE_CSHARP_DEL_CMD = if exist "$(PROGRAM_CSHARP_BUNDLE_BACKSLASH)" del /F /Q "$(PROGRAM_CSHARP_BUNDLE_BACKSLASH)"
		PROGRAM_CPP_DEL_CMD = if exist "$(PROGRAM_CPP_EXE_BACKSLASH)" del /F /Q "$(PROGRAM_CPP_EXE_BACKSLASH)"
	endif
	ifeq ($(ARCH),AMD64)
		# paths
		VERSION_NAME = win64_mingw
		LIBRARY_PLATFORM_DIR = $(LIBRARY_DIR)/$(VERSION_NAME)
		SHARED_CPP_PATH = $(LIBRARY_PLATFORM_DIR)/$(SHARED_CPP_NAME)
		STATIC_CPP_PATH = $(LIBRARY_PLATFORM_DIR)/$(STATIC_CPP_NAME)
		LIBRARY_SRC_DIR = src
		LIBRARY_TEMP_DIR = $(VERSION_NAME)
		LIBRARY_OBJ_DIR = $(LIBRARY_TEMP_DIR)/src
		# cpp library commands and flags
		GCC = g++
		LIBRARY_OBJ_COMPILE_FLAGS = -O3 -g3 -std=gnu++11 -Wall -c -fmessage-length=0
		SHARED_CPP_LINK_FLAGS = -static-libgcc -static-libstdc++ -static -shared
		AR = ar
		STATIC_CPP_LINK = 
		# program c#
		CSC = csc
		CSC_FLAGS = /nologo /optimize /langversion:latest
		BUNDLE_CMD = 
		# program c++
		PROGRAM_CPP_COMPILE = -I"$(PROGRAM_INC_DIR)" -O3 -g3 -std=gnu++11 -Wall -c -fmessage-length=0
		PROGRAM_CPP_LINK = -static-libgcc -static-libstdc++ -static -L"$(LIBRARY_PLATFORM_DIR)"
		PROGRAM_CPP_LIBS = -lResourceFileUtility
		# backslash
		LIBRARY_OBJ_DIR_BACKSLASH = $(subst /,\\,$(LIBRARY_OBJ_DIR))
		LIBRARY_TEMP_DIR_BACKSLASH = $(subst /,\\,$(LIBRARY_TEMP_DIR))
		LIBRARY_PLATFORM_DIR_BACKSLASH= $(subst /,\\,$(LIBRARY_PLATFORM_DIR))
		SHARED_CPP_PATH_BACKSLASH= $(subst /,\\,$(SHARED_CPP_PATH))
		STATIC_CPP_PATH_BACKSLASH= $(subst /,\\,$(STATIC_CPP_PATH))
		PROGRAM_CSHARP_EXE_BACKSLASH= $(subst /,\\,$(PROGRAM_CSHARP_EXE))
		PROGRAM_CSHARP_BUNDLE_BACKSLASH= $(subst /,\\,$(PROGRAM_CSHARP_BUNDLE))
		PROGRAM_CPP_EXE_BACKSLASH=$(subst /,\\,$(PROGRAM_CPP_EXE))
		PROGRAM_OBJ_DIR_BACKSLASH=$(subst /,\\,$(PROGRAM_OBJ_DIR))
		# commands
		LIBRARY_OBJ_DIR_CMD = if not exist "$(LIBRARY_OBJ_DIR_BACKSLASH)" mkdir $(LIBRARY_OBJ_DIR_BACKSLASH)
		LIBRARY_PLATFORM_DIR_CMD = if not exist "$(LIBRARY_PLATFORM_DIR_BACKSLASH)" mkdir $(LIBRARY_PLATFORM_DIR_BACKSLASH)
		PROGRAM_OBJ_DIR_CMD = if not exist "$(PROGRAM_OBJ_DIR_BACKSLASH)" mkdir $(PROGRAM_OBJ_DIR_BACKSLASH)
		COPY_SHARED_LIBRARY_CMD = copy $(SHARED_CPP_PATH_BACKSLASH) $(PROGRAM_BIN_DIR) /Y
		LIBRARY_TEMP_DIR_DEL = if exist "$(LIBRARY_TEMP_DIR_BACKSLASH)" rd /s /q "$(LIBRARY_TEMP_DIR_BACKSLASH)"
		PROGRAM_OBJ_DIR_DEL = if exist "$(PROGRAM_OBJ_DIR_BACKSLASH)" rd /s /q "$(PROGRAM_OBJ_DIR_BACKSLASH)"
		SHARED_LIBRARY_DEL_CMD = if exist "$(SHARED_CPP_PATH_BACKSLASH)" del /F /Q "$(SHARED_CPP_PATH_BACKSLASH)"
		STATIC_LIBRARY_DEL_CMD = if exist "$(STATIC_CPP_PATH_BACKSLASH)" del /F /Q "$(STATIC_CPP_PATH_BACKSLASH)"
		PROGRAM_CSHARP_DEL_CMD = if exist "$(PROGRAM_CSHARP_EXE_BACKSLASH)" del /F /Q "$(PROGRAM_CSHARP_EXE_BACKSLASH)"
		PROGRAM_CSHARP_DEL_POST_CMD = 
		BUNDLE_CSHARP_DEL_CMD = if exist "$(PROGRAM_CSHARP_BUNDLE_BACKSLASH)" del /F /Q "$(PROGRAM_CSHARP_BUNDLE_BACKSLASH)"
		PROGRAM_CPP_DEL_CMD = if exist "$(PROGRAM_CPP_EXE_BACKSLASH)" del /F /Q "$(PROGRAM_CPP_EXE_BACKSLASH)"
	endif
endif
ifeq ($(OS_DET),OSX)
	# paths
	SHARED_CPP_NAME = libResourceFileUtility.dll
	STATIC_CPP_NAME = libResourceFileUtility.a
	VERSION_NAME = apple
	LIBRARY_PLATFORM_DIR = $(LIBRARY_DIR)/$(VERSION_NAME)
	SHARED_CPP_PATH = $(LIBRARY_PLATFORM_DIR)/$(SHARED_CPP_NAME)
	STATIC_CPP_PATH = $(LIBRARY_PLATFORM_DIR)/$(STATIC_CPP_NAME)
	LIBRARY_SRC_DIR = src
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
	BUNDLE_CMD = mkbundle -o $(PROGRAM_CSHARP_BUNDLE) --simple $(PROGRAM_CSHARP_EXE) --library $(SHARED_CPP_PATH)
	# program c++
	PROGRAM_CPP_COMPILE = -I"$(PROGRAM_INC_DIR)" -O3 -g3 -std=gnu++11 -Wall -c -fmessage-length=0 -mmacosx-version-min=10.9
	PROGRAM_CPP_LINK = -L"$(LIBRARY_PLATFORM_DIR)" -mmacosx-version-min=10.9
	PROGRAM_CPP_LIBS = -lResourceFileUtility
	# mac app
	PROGRAM_CPP_APP_ENABLE = $(PROGRAM_CPP_APP)
	# commands
	LIBRARY_OBJ_DIR_CMD = mkdir -p $(LIBRARY_OBJ_DIR)
	LIBRARY_PLATFORM_DIR_CMD = mkdir -p $(LIBRARY_PLATFORM_DIR)
	PROGRAM_OBJ_DIR_CMD = mkdir -p $(PROGRAM_OBJ_DIR)
	COPY_SHARED_LIBRARY_CMD_UNUSED = yes | cp -rf $(SHARED_CPP_PATH) $(PROGRAM_BIN_DIR)
	COPY_SHARED_LIBRARY_CMD = 
	LIBRARY_TEMP_DIR_DEL = yes | rm -rf $(LIBRARY_TEMP_DIR)
	PROGRAM_OBJ_DIR_DEL = yes | rm -rf $(PROGRAM_OBJ_DIR)
	SHARED_LIBRARY_DEL_CMD = yes | rm -f "$(SHARED_CPP_PATH)"
	STATIC_LIBRARY_DEL_CMD = yes | rm -f "$(STATIC_CPP_PATH)"
	PROGRAM_CSHARP_DEL_CMD = yes | rm -f "$(PROGRAM_CSHARP_EXE)"
	PROGRAM_CSHARP_DEL_POST_CMD = $(PROGRAM_CSHARP_DEL_CMD)
	BUNDLE_CSHARP_DEL_CMD = yes | rm -f "$(PROGRAM_CSHARP_BUNDLE)"
	PROGRAM_CPP_DEL_CMD = yes | rm -f "$(PROGRAM_CPP_EXE)"
	PROGRAM_CPP_APP_DEL_CMD = yes | rm -rf "$(PROGRAM_CPP_APP)"
endif
ifeq ($(OS_DET),LINUX)
	# paths
	SHARED_CPP_NAME = libResourceFileUtility.so
	STATIC_CPP_NAME = libResourceFileUtility.a
	VERSION_NAME = linux
	LIBRARY_PLATFORM_DIR = $(LIBRARY_DIR)/$(VERSION_NAME)
	SHARED_CPP_PATH = $(LIBRARY_PLATFORM_DIR)/$(SHARED_CPP_NAME)
	STATIC_CPP_PATH = $(LIBRARY_PLATFORM_DIR)/$(STATIC_CPP_NAME)
	LIBRARY_SRC_DIR = src
	LIBRARY_TEMP_DIR = $(VERSION_NAME)
	LIBRARY_OBJ_DIR = $(LIBRARY_TEMP_DIR)/src
	# cpp library commands and flags
	GCC = g++
	LIBRARY_OBJ_COMPILE_FLAGS = -O3 -g3 -std=gnu++11 -Wall -c -fmessage-length=0
	SHARED_CPP_LINK_FLAGS = -std=gnu++11 -static -shared
	LIBRARY_SRC_DIR := src
	LIBRARY_OBJ_DIR := $(VERSION_NAME)/src
	AR = ar
	STATIC_CPP_LINK = 
	# program c#
	CSC = csc
	CSC_FLAGS = /nologo /optimize /langversion:latest
	BUNDLE_CMD = 
	# program c++
	PROGRAM_CPP_COMPILE = -I"$(PROGRAM_INC_DIR)" -O3 -g3 -std=gnu++11 -Wall -c -fmessage-length=0
	PROGRAM_CPP_LINK = -static -L"$(LIBRARY_PLATFORM_DIR)"
	PROGRAM_CPP_LIBS = -lResourceFileUtility
	# commands
	LIBRARY_OBJ_DIR_CMD = mkdir -p $(LIBRARY_OBJ_DIR)
	LIBRARY_PLATFORM_DIR_CMD = mkdir -p $(LIBRARY_PLATFORM_DIR)
	PROGRAM_OBJ_DIR_CMD = mkdir -p $(PROGRAM_OBJ_DIR)
	COPY_SHARED_LIBRARY_CMD_UNUSED = yes | cp -rf $(SHARED_CPP_PATH) $(PROGRAM_BIN_DIR)
	COPY_SHARED_LIBRARY_CMD = 
	LIBRARY_TEMP_DIR_DEL = yes | rm -rf $(LIBRARY_TEMP_DIR)
	PROGRAM_OBJ_DIR_DEL = yes | rm -rf $(PROGRAM_OBJ_DIR)
	SHARED_LIBRARY_DEL_CMD = yes | rm -f "$(SHARED_CPP_PATH)"
	STATIC_LIBRARY_DEL_CMD = yes | rm -f "$(STATIC_CPP_PATH)"
	PROGRAM_CSHARP_DEL_CMD = yes | rm -f "$(PROGRAM_CSHARP_EXE)"
	PROGRAM_CSHARP_DEL_POST_CMD = $(PROGRAM_CSHARP_DEL_CMD)
	BUNDLE_CSHARP_DEL_CMD = yes | rm -f "$(PROGRAM_CSHARP_BUNDLE)"
	PROGRAM_CPP_DEL_CMD = yes | rm -f "$(PROGRAM_CPP_EXE)"
endif
ifeq ($(OS_DET),android)
	# paths
	SHARED_CPP_NAME = libResourceFileUtility.dll
	STATIC_CPP_NAME = libResourceFileUtility.a
	ifeq ($(ARCH),armeabi)
		VERSION_NAME = linux-android-armeabi
		GCC = arm-linux-androideabi-g++
		AR = arm-linux-androideabi-ar
	endif
	ifeq ($(ARCH),armeabi-v7a)
		VERSION_NAME = linux-android-armeabi
		GCC = arm-linux-androideabi-g++
		AR = arm-linux-androideabi-ar
	endif
	ifeq ($(ARCH),arm64-v8a)
		VERSION_NAME = aarch64-linux-android
		GCC = aarch64-linux-android-g++
		AR = aarch64-linux-android-ar
	endif
		LIBRARY_PLATFORM_DIR = $(LIBRARY_DIR)/$(VERSION_NAME)
		SHARED_CPP_PATH = $(LIBRARY_PLATFORM_DIR)/$(SHARED_CPP_NAME)
		STATIC_CPP_PATH = $(LIBRARY_PLATFORM_DIR)/$(STATIC_CPP_NAME)
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
		PROGRAM_CPP_COMPILE = $(PROGRAM_CPP_COMPILE_INCLUDES) -I"$(PROGRAM_INC_DIR)" -I"$(NDK_PATH)/sysroot/usr/include" -O3 -g3 -std=gnu++11 -Wall -c -fmessage-length=0
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
		PROGRAM_CPP_COMPILE = $(PROGRAM_CPP_COMPILE_INCLUDES) -I"$(PROGRAM_INC_DIR)" -I"$(NDK_PATH)/sysroot/usr/include" -O3 -g3 -std=gnu++11 -Wall -c -fmessage-length=0
		PROGRAM_CPP_LINK = --sysroot="$(NDK_PATH)/platforms/android-21/arch-arm64" -static-libgcc -static-libstdc++ -static -L"$(LIBRARY_PLATFORM_DIR)"
		PROGRAM_CPP_LIBS = -lResourceFileUtility
	endif
		# backslash
		LIBRARY_OBJ_DIR_BACKSLASH = $(subst /,\\,$(LIBRARY_OBJ_DIR))
		LIBRARY_TEMP_DIR_BACKSLASH = $(subst /,\\,$(LIBRARY_TEMP_DIR))
		LIBRARY_PLATFORM_DIR_BACKSLASH= $(subst /,\\,$(LIBRARY_PLATFORM_DIR))
		SHARED_CPP_PATH_BACKSLASH= $(subst /,\\,$(SHARED_CPP_PATH))
		STATIC_CPP_PATH_BACKSLASH= $(subst /,\\,$(STATIC_CPP_PATH))
		PROGRAM_CSHARP_EXE_BACKSLASH= $(subst /,\\,$(PROGRAM_CSHARP_EXE))
		PROGRAM_CSHARP_BUNDLE_BACKSLASH= $(subst /,\\,$(PROGRAM_CSHARP_BUNDLE))
		PROGRAM_CPP_EXE_BACKSLASH=$(subst /,\\,$(PROGRAM_CPP_EXE))
		PROGRAM_OBJ_DIR_BACKSLASH=$(subst /,\\,$(PROGRAM_OBJ_DIR))
		# commands
		LIBRARY_OBJ_DIR_CMD = if not exist "$(LIBRARY_OBJ_DIR_BACKSLASH)" mkdir $(LIBRARY_OBJ_DIR_BACKSLASH)
		LIBRARY_PLATFORM_DIR_CMD = if not exist "$(LIBRARY_PLATFORM_DIR_BACKSLASH)" mkdir $(LIBRARY_PLATFORM_DIR_BACKSLASH)
		PROGRAM_OBJ_DIR_CMD = if not exist "$(PROGRAM_OBJ_DIR_BACKSLASH)" mkdir $(PROGRAM_OBJ_DIR_BACKSLASH)
		COPY_SHARED_LIBRARY_CMD = copy $(SHARED_CPP_PATH_BACKSLASH) $(PROGRAM_BIN_DIR) /Y
		LIBRARY_TEMP_DIR_DEL = if exist "$(LIBRARY_TEMP_DIR_BACKSLASH)" rd /s /q "$(LIBRARY_TEMP_DIR_BACKSLASH)"
		PROGRAM_OBJ_DIR_DEL = if exist "$(PROGRAM_OBJ_DIR_BACKSLASH)" rd /s /q "$(PROGRAM_OBJ_DIR_BACKSLASH)"
		SHARED_LIBRARY_DEL_CMD = if exist "$(SHARED_CPP_PATH_BACKSLASH)" del /F /Q "$(SHARED_CPP_PATH_BACKSLASH)"
		STATIC_LIBRARY_DEL_CMD = if exist "$(STATIC_CPP_PATH_BACKSLASH)" del /F /Q "$(STATIC_CPP_PATH_BACKSLASH)"
		PROGRAM_CSHARP_DEL_CMD = if exist "$(PROGRAM_CSHARP_EXE_BACKSLASH)" del /F /Q "$(PROGRAM_CSHARP_EXE_BACKSLASH)"
		PROGRAM_CSHARP_DEL_POST_CMD = 
		BUNDLE_CSHARP_DEL_CMD = if exist "$(PROGRAM_CSHARP_BUNDLE_BACKSLASH)" del /F /Q "$(PROGRAM_CSHARP_BUNDLE_BACKSLASH)"
		PROGRAM_CPP_DEL_CMD = if exist "$(PROGRAM_CPP_EXE_BACKSLASH)" del /F /Q "$(PROGRAM_CPP_EXE_BACKSLASH)"
endif

LIBRARY_SRC_FILES := $(wildcard $(LIBRARY_SRC_DIR)/*.cpp)
LIBRARY_OBJ_FILES := $(patsubst $(LIBRARY_SRC_DIR)/%.cpp,$(LIBRARY_OBJ_DIR)/%.o,$(LIBRARY_SRC_FILES))
PROGRAM_SRC_FILES := $(wildcard $(PROGRAM_SRC_DIR)/*.cpp)
PROGRAM_OBJ_FILES := $(patsubst $(PROGRAM_SRC_DIR)/%.cpp,$(PROGRAM_OBJ_DIR)/%.o,$(PROGRAM_SRC_FILES))

EXAMPLE_SRC = *.cs
EXTRA_SRC = ResourceFileUtility.cs

all: directories $(SHARED_CPP_PATH) $(STATIC_CPP_PATH) $(PROGRAM_CSHARP_EXE) $(PROGRAM_CPP_EXE) $(PROGRAM_CPP_APP_ENABLE)
	
$(PROGRAM_CSHARP_EXE):
	$(CSC) $(CSC_FLAGS) /out:$@ /t:exe -lib:$(PROGRAM_SHARED_LIB_DIR) $(PROGRAM_INC_DIR)/$(EXTRA_SRC) $(PROGRAM_SRC_DIR)/*.cs
	$(COPY_SHARED_LIBRARY_CMD)
	$(BUNDLE_CMD)
	$(PROGRAM_CSHARP_DEL_POST_CMD)
	$(LIBRARY_TEMP_DIR_DEL)
	
$(SHARED_CPP_PATH): $(LIBRARY_OBJ_FILES)
	$(GCC) $(SHARED_CPP_LINK_FLAGS) -o $@ $^
	
$(STATIC_CPP_PATH): $(LIBRARY_OBJ_FILES)
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
	mkdir -p $(PROGRAM_CPP_APP)/Contents/{MacOS,Resources}
	cp $(PROGRAM_SRC_DIR)/Info.plist "$(PROGRAM_CPP_APP)/Contents/"
	cp $(PROGRAM_CPP_EXE) "$(PROGRAM_CPP_APP)/Contents/MacOS/$(PROGRAM_CPP_APP_NAME)"

directories:
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
