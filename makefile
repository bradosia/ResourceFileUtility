# Architecture detection
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

EXAMPLE_BIN_DIR = example
EXAMPLE_LIB_DIR = example
EXAMPLE_SRC_DIR = example/src
EXAMPLE_INC_DIR = include
EXAMPLE_EXE = $(EXAMPLE_BIN_DIR)/example.exe

ifeq ($(OS_DET),WIN32)
	DLL_NAME = ResourceFileUtility.dll
	ifeq ($(ARCH),IA32)
		VERSION_NAME = win32_mingw$(UNAME_S)
		DLL_BIN = bin/$(VERSION_NAME)
		GCC = g++
		GCC_COMPILE_FLAGS = -O3 -g3 -std=gnu++11 -Wall -c -fmessage-length=0
		GCC_LINK_FLAGS = -static-libgcc -static-libstdc++ -static -shared
		GCC_SRC_DIR := src
		GCC_OBJ_DIR := $(VERSION_NAME)/src
		CSC = csc
		CSC_FLAGS = /nologo /optimize /langversion:latest
		DLL_DIR = $(DLL_BIN)/$(DLL_NAME)
		MONO_LIB = C:\Program Files\Mono\lib
		CORE_LIB = C:\Program Files\dotnet\shared\Microsoft.NETCore.App\2.0.6
		# commands
		OBJ_DIR_BACKSLASH = $(subst /,\\,$(GCC_OBJ_DIR))
		DLL_BIN_BACKSLASH= $(subst /,\\,$(DLL_BIN))
		DLL_DIR_BACKSLASH= $(subst /,\\,$(DLL_DIR))
		EXAMPLE_EXE_BACKSLASH= $(subst /,\\,$(EXAMPLE_EXE))
		OBJ_DIR_CMD = if not exist "$(OBJ_DIR_BACKSLASH)" mkdir $(OBJ_DIR_BACKSLASH)
		DLL_DIR_CMD = if not exist "$(DLL_BIN_BACKSLASH)" mkdir $(DLL_BIN_BACKSLASH)
		CPY_DLL_CMD = copy $(DLL_DIR_BACKSLASH) $(EXAMPLE_BIN_DIR) /Y
		OBJ_DIR_DEL = del /F /Q $(OBJ_DIR_BACKSLASH)\*
		DLL_DEL_CMD = if exist "$(DLL_DIR_BACKSLASH)" del /F /Q "$(DLL_DIR_BACKSLASH)"
		EXE_DEL_CMD = if exist "$(EXAMPLE_EXE_BACKSLASH)" del /F /Q "$(EXAMPLE_EXE_BACKSLASH)"
	endif
	ifeq ($(ARCH),AMD64)
		VERSION_NAME = win64_mingw
		DLL_BIN = bin/$(VERSION_NAME)
		GCC = g++
		GCC_COMPILE_FLAGS = -O3 -g3 -std=gnu++11 -Wall -c -fmessage-length=0
		GCC_LINK_FLAGS = -static-libgcc -static-libstdc++ -static -shared
		GCC_SRC_DIR := src
		GCC_OBJ_DIR := $(VERSION_NAME)/src
		CSC = csc
		CSC_FLAGS = /nologo /optimize /langversion:latest
		DLL_DIR = $(DLL_BIN)/$(DLL_NAME)
		MONO_LIB = C:\Program Files\Mono\lib
		CORE_LIB = C:\Program Files\dotnet\shared\Microsoft.NETCore.App\2.0.6
		# commands
		OBJ_DIR_BACKSLASH = $(subst /,\\,$(GCC_OBJ_DIR))
		DLL_BIN_BACKSLASH= $(subst /,\\,$(DLL_BIN))
		DLL_DIR_BACKSLASH= $(subst /,\\,$(DLL_DIR))
		EXAMPLE_EXE_BACKSLASH= $(subst /,\\,$(EXAMPLE_EXE))
		OBJ_DIR_CMD = if not exist "$(OBJ_DIR_BACKSLASH)" mkdir $(OBJ_DIR_BACKSLASH)
		DLL_DIR_CMD = if not exist "$(DLL_BIN_BACKSLASH)" mkdir $(DLL_BIN_BACKSLASH)
		CPY_DLL_CMD = copy $(DLL_DIR_BACKSLASH) $(EXAMPLE_BIN_DIR) /Y
		OBJ_DIR_DEL = del /F /Q $(OBJ_DIR_BACKSLASH)\*
		DLL_DEL_CMD = if exist "$(DLL_DIR_BACKSLASH)" del /F /Q "$(DLL_DIR_BACKSLASH)"
		EXE_DEL_CMD = if exist "$(EXAMPLE_EXE_BACKSLASH)" del /F /Q "$(EXAMPLE_EXE_BACKSLASH)"
	endif
endif
ifeq ($(OS_DET),OSX)
	DLL_NAME = ResourceFileUtility.dylib
	VERSION_NAME = apple
	DLL_BIN = bin/$(VERSION_NAME)
	GCC = g++
	GCC_COMPILE_FLAGS = -O3 -g3 -std=gnu++11 -Wall -fvisibility=hidden -c -fmessage-length=0 -mmacosx-version-min=10.9
	GCC_LINK_FLAGS = -dynamiclib -std=gnu++11 -current_version 1.0 -compatibility_version 1.0 -fvisibility=hidden -mmacosx-version-min=10.9
	GCC_SRC_DIR := src
	GCC_OBJ_DIR := $(VERSION_NAME)/src
	CSC = csc
	CSC_FLAGS = /nologo /optimize /langversion:latest /appconfig:example/src/ResourceFileUtility.config
	DLL_DIR = $(DLL_BIN)/$(DLL_NAME)
	MONO_LIB = 
	CORE_LIB = 
	# commands
	OBJ_DIR_CMD = mkdir -p $(GCC_OBJ_DIR)
	DLL_DIR_CMD = mkdir -p $(DLL_BIN)
	CPY_DLL_CMD = yes | cp -rf $(DLL_DIR) $(EXAMPLE_BIN_DIR)
	OBJ_DIR_DEL = yes | rm -f $(GCC_OBJ_DIR)/*
	DLL_DEL_CMD = yes | rm -f "$(DLL_DIR)"
	EXE_DEL_CMD = yes | rm -f "$(EXAMPLE_EXE)"
endif
ifeq ($(OS_DET),LINUX)
	DLL_NAME = ResourceFileUtility.so
	VERSION_NAME = linux
	DLL_BIN = bin/$(VERSION_NAME)
	GCC = g++
	GCC_COMPILE_FLAGS = -O3 -g3 -std=gnu++11 -Wall -c -fmessage-length=0
	GCC_LINK_FLAGS = -std=gnu++11 -static -shared
	GCC_SRC_DIR := src
	GCC_OBJ_DIR := $(VERSION_NAME)/src
	CSC = csc
	CSC_FLAGS = /nologo /optimize /langversion:latest
	DLL_DIR = $(DLL_BIN)/$(DLL_NAME)
	MONO_LIB = 
	CORE_LIB = 
	# commands
	OBJ_DIR_CMD = mkdir -p $(GCC_OBJ_DIR)
	DLL_DIR_CMD = mkdir -p $(DLL_BIN)
	CPY_DLL_CMD = yes | cp -rf $(DLL_DIR) $(EXAMPLE_BIN_DIR)
	OBJ_DIR_DEL = yes | rm -f $(GCC_OBJ_DIR)/*
	DLL_DEL_CMD = yes | rm "$(DLL_DIR)"
	EXE_DEL_CMD = yes | rm "$(EXAMPLE_EXE)"
endif

GCC_SRC_FILES := $(wildcard $(GCC_SRC_DIR)/*.cpp)
GCC_OBJ_FILES := $(patsubst $(GCC_SRC_DIR)/%.cpp,$(GCC_OBJ_DIR)/%.o,$(GCC_SRC_FILES))

EXAMPLE_SRC = *.cs
EXTRA_SRC = ResourceFileUtility.cs

all: directories $(DLL_DIR) $(EXAMPLE_EXE)
	
$(EXAMPLE_EXE):
	$(CSC) $(CSC_FLAGS) /out:$@ /t:exe -lib:$(EXAMPLE_LIB_DIR) $(EXAMPLE_INC_DIR)/$(EXTRA_SRC) $(EXAMPLE_SRC_DIR)/*.cs
	$(CPY_DLL_CMD)
	
$(DLL_DIR): $(GCC_OBJ_FILES)
	$(GCC) $(GCC_LINK_FLAGS) -o $@ $^

$(GCC_OBJ_DIR)/%.o: $(GCC_SRC_DIR)/%.cpp
	$(GCC) $(GCC_COMPILE_FLAGS) -c -o $@ $<
	
directories:
	$(OBJ_DIR_CMD)
	$(DLL_DIR_CMD)
	$(OBJ_DIR_DEL)
	$(DLL_DEL_CMD)
	$(EXE_DEL_CMD)

clean:
	$(OBJ_DIR_DEL)
	$(DLL_DEL_CMD)
	$(EXE_DEL_CMD)
