# Before pulling anything: READ THE CHANGELOG

## How to run on Linux:
- (The exe is in bin folder) Press F5 (Runs `make` automatically)
If you get the "Errors exist after running PreLaunchTask 'build debug'" -> *your code still has errors...*

## How to configure the makefile (Retroengineering 😎):
The global Makefile in the working directory (now visible on Github) uses multiple implicit and unimplicit variables, which makes it pretty unreadable...

### Cheatsheet:

**makefile**
- `$(VAR)` is an alias for the value held in a variable (e.g.: `CC = gcc -> $(CC) -o main main.c`)
- `$@` is an alias for the name of the target (the rule's target)
- `.PHONY` is a target always executed, no matter the dependencies

**make manual (bash)**
- `-C dir`: before executing the rest of the command, moves to dir path
- `-f file`: specifies the makefile used

### Retroengineering
Here's the part of the makefile we're (probably) gonna use:
Nb : l62 tells us to run make config=release_X** to build the release version (cf. make help)
```
Buns_Rush: raylib
ifneq (,$(Buns_Rush_config))
    @echo "==== Building Buns_Rush ($(Buns_Rush_config)) ===="
    @${MAKE} --no-print-directory -C build/build_files -f Buns_Rush.make config=$(Buns_Rush_config)
endif
```

=> It goes to the Buns_Rush/build/build_files/Buns_Rush.make makefile 

**Interesting lines and variables**

Line 22: `INCLUDES += -I../../src -I../../include -I../external/raylib-master/src -I../external/raylib-master/src/external -I../external/raylib-master/src/external/glfw/include`
The -I options tells GCC to add these file paths to a list of paths that have necessary headers
=> We can add our headers to either src/ or include/

TARGETDIR: the build's directory
TARGET: the subdirectory of TARGETDIR
OBJDIR: the directory where the code object is output

Line 179: The -MF option of GCC may have something to do with outputting the dependencies for the make command? Look into it

**16/11/24 :** Premake5 is the tool that automatically generates .make makefiles. 
To take into account new, separate C files, just re-run it by running cd into build/ then ./premake5 gmake2

# License

Copyright (c) 2020-2024 Jeffery Myers

This software is provided "as-is", without any express or implied warranty. In no event will the authors be held liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:

    The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.

    Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.

    This notice may not be removed or altered from any source distribution.
