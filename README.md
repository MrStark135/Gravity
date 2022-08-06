# Gravity
Gravity simulation made in C++ with SFML

## Build & Run
The repository already conatins a compiled executable that runs on Windows 10.
In order to build the code from scratch use the Makefile provided. build and run with
```bash
make
./main
```

The repository contains all you need to use the simulator. The DLLs are here along with the SFML library (headers and libs).

## How to use
The program loads a mock-up of a solar system. You can add planets to the scene by left-clicking and dragging.
Once you have the desired radius of the object, release the click. Then just do a second click somwhere around.
That will give the object an initial velocity.
