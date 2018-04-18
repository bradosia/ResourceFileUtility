CSC = csc
CSC_FLAGS = /nologo /optimize /langversion:latest

GCC = g++
GCC_FLAGS = -static-libgcc -static-libstdc++ -static -shared

BIN = example
LIB = example
SRC = example/src
CSC_BIN = example
CSC_LIB = example
CSC_SRC = example/src
CSC_INC = include
DLL_BIN = bin/win64_mingw
DLL_CPY = ResourceFileUtility.dll

PROGRAM_EXE = $(CSC_BIN)/test.exe
PROGRAM_SRC = *.cs
EXTRA_SRC = ResourceFileUtility.cs

#DLLS = ResourceFileUtility.dll

MONO_LIB = C:\Program Files\Mono\lib
CORE_LIB = C:\Program Files\dotnet\shared\Microsoft.NETCore.App\2.0.6

all: $(PROGRAM_EXE)
$(PROGRAM_EXE):
	$(CSC) $(CSC_FLAGS) /out:$@ /t:exe -lib:$(LIB) $(CSC_SRC)/$(PROGRAM_SRC) $(CSC_INC)/*.cs
#cp $(DLL_BIN)/$(DLL_CPY) $(CSC_BIN)/$(DLL_CPY)

clean:
	rm -f $(PROGRAM_EXE)
