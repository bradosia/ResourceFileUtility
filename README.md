# ResourceFileUtility
A utility for compiling media assets into a single resource file. Includes a driver for c#.

# Build Instructions

## Auto-detection
Use gnu make command on project root
```sh
make
```

## Windows
Only Windows host<BR>
Install mingw

## Mac OSX
Only Mac OSX host<BR>
Install clang

## Linux Ubuntu
Install GCC

## Android
Install the android NDK<BR>
Add ```<NDK_PATH>\toolchains\arm-linux-androideabi-4.9\prebuilt\windows-x86_64\bin``` to PATH<BR>
Add ```<NDK_PATH>\toolchains\aarch64-linux-android-4.9\prebuilt\windows-x86_64\bin``` to PATH<BR>

## IOS
Only Mac OSX host<BR>
Install clang<BR>

## Supported
| OS | Architecture | Support |  Command |
| :---      | :---         | :--- | :--- |
| Windows   | x86          | X    | ``` make OS_DET=WIN32 ARCH=IA32 ``` |
| Windows   | x86_64       | X    | ``` make OS_DET=WIN32 ARCH=AMD64 ``` |
| iOS Mac   | x86          | O    | ``` make OS_DET=OSX ARCH=IA32 ``` |
| iOS Mac   | x86_64       | X    | ``` make OS_DET=OSX ARCH=AMD64 ``` |
| linux ubuntu   | x86     | O    | ``` make OS_DET=LINUX ARCH=IA32 ``` |
| linux ubuntu   | x86_64  | O    | ``` make OS_DET=LINUX ARCH=AMD64 ``` |
| iOS iphone   | armv7     | O    | ``` make OS_DET=IOS ARCH=armv7 ``` |
| iOS iphone   | armv7s    | O    | ``` make OS_DET=IOS ARCH=armv7s ``` |
| iOS iphone   | arm64     | O    | ``` make OS_DET=IOS ARCH=arm64 ``` |
| Android   | armeabi      | O    | ``` make OS_DET=android ARCH=armeabi NDK_PATH=C:\android-ndk-r16b-windows-x86_64\android-ndk-r16b ``` |
| Android   | armeabi-v7a  | O    | ``` make OS_DET=android ARCH=armeabi-v7a NDK_PATH=C:\android-ndk-r16b-windows-x86_64\android-ndk-r16b ``` |
| Android   | arm64-v8a    | O    | ``` make OS_DET=android ARCH=arm64-v8a NDK_PATH=C:\android-ndk-r16b-windows-x86_64\android-ndk-r16b ``` |
| Android   | x86          | O    | ``` make OS_DET=android ARCH=x86 NDK_PATH=C:\android-ndk-r16b-windows-x86_64\android-ndk-r16b ``` |
| Android   | x86_64       | O    | ``` make OS_DET=android ARCH=x86_64 NDK_PATH=C:\android-ndk-r16b-windows-x86_64\android-ndk-r16b ``` |
 
# Usage Instructions
## C++
there is only a single include needed when statically linking against this library
```cpp
#include "include/ResourceFileUtility.h"
```
Pack all resources in your json file to a single resource file
```cpp
ResourceFileUtility::Compiler RFUCompiler = new ResourceFileUtility::Compiler();
RFUCompiler.info("resources.json");
RFUCompiler.pack("assets.data");
```

Load a resource to memory and handle it
```cpp
ResourceFileUtility::Loader RFULoader = new ResourceFileUtility::Loader();
ResourceFileUtility::Info coneInfo = RFULoader.info("cone");
char modelBytes = RFULoader.open("cone"); //loads all cone data to memory
if(coneInfo.inType == "FILE_FORMAT"){
	// handle FILE_FORMAT
}
```

Stream a resource
```cpp
ResourceFileUtility::Loader RFULoader = new ResourceFileUtility::Loader();
ResourceFileUtility::Info songInfo = RFULoader.info("song");
ResourceFileUtility::Stream songStream = RFULoader.stream("song"); // stream data
songStream.pos(0); // set stream position to beginning of file
if(songInfo.inType == "FILE_FORMAT"){
	// handle FILE_FORMAT
	// get 4 bytes from selector, selector increments by 4
	char modelBytes4 = songStream.get(4); // first 4 bytes
	modelBytes4 = songStream.get(4); // next 4 bytes
}
```


## C#
add ```include/ResourceFileUtility.cs``` to your project<BR><BR>

Pack all resources in your json file to a single resource file
```csharp
ResourceFileUtility.Compiler RFUCompiler = new ResourceFileUtility.Compiler();
RFUCompiler.info("resources.json");
RFUCompiler.pack("assets.data");
```

Load a resource to memory and handle it
```csharp
ResourceFileUtility.Loader RFULoader = new ResourceFileUtility.Loader();
ResourceFileUtility.Info coneInfo = RFULoader.info("cone");
char modelBytes = RFULoader.open("cone"); //loads all cone data to memory
if(coneInfo.inType == "FILE_FORMAT"){
	// handle FILE_FORMAT
}
```

Stream a resource
```csharp
ResourceFileUtility.Loader RFULoader = new ResourceFileUtility.Loader();
ResourceFileUtility.Info songInfo = RFULoader.info("song");
ResourceFileUtility.Stream songStream = RFULoader.stream("song"); // stream data
songStream.pos(0); // set stream position to beginning of file
if(songInfo.inType == "FILE_FORMAT"){
	// handle FILE_FORMAT
	// get 4 bytes from selector, selector increments by 4
	char modelBytes4 = songStream.get(4); // first 4 bytes
	modelBytes4 = songStream.get(4); // next 4 bytes
}
```

## Libraries Used
JSON for C++<BR>
License: MIT<BR>
https://github.com/nlohmann/json

# License
The class is licensed under the MIT License: <BR>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.