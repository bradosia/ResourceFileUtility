CSC = csc
CSC_FLAGS = /nologo /optimize /langversion:latest

BIN = ..\ResourceFileLoader64
LIB = ..\ResourceFileLoader64
SRC = .

PROGRAM_EXE = $(BIN)/test.exe
PROGRAM_SRC = *.cs

#DLLS = ResourceFileUtility.dll

MONO_LIB = C:\Program Files\Mono\lib
CORE_LIB = C:\Program Files\dotnet\shared\Microsoft.NETCore.App\2.0.6

all: $(PROGRAM_EXE)
$(PROGRAM_EXE):
	$(CSC) $(CSC_FLAGS) /out:$@ /t:exe -lib:$(LIB) $(PROGRAM_SRC)

clean:
	rm -f $(BOT_EXE)
