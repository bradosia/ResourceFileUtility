# ResourceFileUtility
A utility for compiling media assets into a single resource file. Includes a driver for c#.

# Libraries Used
JSON for C++<BR>
License: MIT
https://github.com/nlohmann/json

# Build Instructions

## Makefile
```sh
make
```

## Darwin
Please make sure the commands in the makefile for creating and deleting directories are good. They haven't been tested.<BR>
Currently working on windows 10 with MinGW 64

# Usage Instructions
## C++
there is only a single include needed when statically linking against this library
```cpp
#include "include/ResourceFileUtility.h"
```

## C#
add ```include/ResourceFileUtility.cs``` to your project<BR>
The following call will pack all resources in your json file to a single resource file
```csharp
ResourceFileUtility.Compiler RFUCompiler = new ResourceFileUtility.Compiler();
RFUCompiler.info("resources.json");
RFUCompiler.pack("assets.data");
```

The following call will pack all resources in your json file to a single resource file
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


# License
The class is licensed under the MIT License: <BR>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.