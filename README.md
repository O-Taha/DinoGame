# Before pulling anything: READ THE CHANGELOG

## How to run on Linux:
- Run `make`
- (The exe is in bin folder) Press F5

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
DinoGame: raylib
ifneq (,$(DinoGame_config))
    @echo "==== Building DinoGame ($(DinoGame_config)) ===="
    @${MAKE} --no-print-directory -C build/build_files -f DinoGame.make config=$(DinoGame_config)
endif
```

=> It goes to the DinoGame/build/build_files/DinoGame.make makefile 

**Interesting lines and variables**

Line 22: `INCLUDES += -I../../src -I../../include -I../external/raylib-master/src -I../external/raylib-master/src/external -I../external/raylib-master/src/external/glfw/include`
The -I options tells GCC to add these file paths to a list of paths that have necessary headers
=> We can add our headers to either src/ or include/

TARGETDIR: the build's directory
TARGET: the subdirectory of TARGETDIR
OBJDIR: the directory where the code object is output

Line 179: The -MF option of GCC may have something to do with outputting the dependencies for the make command? Look into it
