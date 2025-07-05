# Gravity
Gravity simulation made in C++ with SFML

## Build & Run
The project contains prebuild binaries for Windows 10 and Archlinux. Check to see if they suit you. If not, just delete the executables and build the source files.
### Windows
The cmake provided should find the SFML package. Make sure you have cmake and make installed
```cmd
cd windows-build
cmake ..
make
```
Alternative method: If cmake can't find the package, try using the simple Makefile provided,
but first make sure the SFML lib locations are correct:
```Makefile
## extern lib (SFML) related
SFML_PATH       ="C:/Program Files/SFML-3.0.0"
SFML_INCLUDE    =-I${SFML_PATH}/include
SFML_LIB        =-L${SFML_PATH}/lib
```
```cmd
cd windows-build
make
```
### Linux
Again, cmake should find the sfml package and proceed to generate build files for make
```bash
cd linux-build
cmake ..
make
```

## How to use
The program loads a mock-up of a solar system. You can add planets to the scene by left-clicking and dragging (to achieve different sized objects).
Once you have the desired radius of the object, release the click. Then just do a second click somwhere around (like a slingshot).
That will give the object an initial velocity.

## Disclaimer
This is a very simple program, a lot of things could be improved: collision for starters:)
