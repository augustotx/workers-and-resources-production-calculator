# Workers and Resources Production Calculator

Production Calculator for the game Workers and Resources: Soviet Republic programmed in C.

## Build project

### Linux

1. Install GCC, make and GTK 3 (ìf you don't have them)
2. Clone this repository into a directory using Git
3. Run the build script: `./build-linux`.
4. There should now be a file called `soviet-calc`. That's the program.

### Mac OS

1. Install dependencies, e.g. using the homebrew installer: `brew install gtk+3`, `brew install pkg-config`
3. Clone this repository into a directory using Git (or simply download the project files)
4. Run `make` in the terminal from the root project directory.
5. There should now be a file called `soviet-calc` in `./bin`, which you can run: `./bin/soviet-calc'

### Windows

Despite the game being Windows only, the build process is meant for Linux,
so you need a Linux-like environment in order to successfully build it.
You can build this project for Windows using one of these options:

* cross-compilation from Linux or [WSL](https://learn.microsoft.com/en-us/windows/wsl/install)
with [MinGW-w64](https://www.mingw-w64.org/)
* native compilation with MinGW-w64 using [MSYS2](https://www.msys2.org/)

The latter way is strongly recommended as you only need to install the necessary packages
in MSYS to build the project from Windows. Linux/WSL users would probably need some
[more preparations](https://discourse.gnome.org/t/desperately-need-help-with-mingw64-and-gtk-3-0-for-cross-compilation-from-linux-wsl-ubuntu-to-windows/15150/7)
to make the project buildable with cross-complation.

The following Linux/MSYS packages are required in order to build this project for Windows:

* make
* mingw-w64-x86_64-gcc
* mingw-w64-x86_64-gtk3
* mingw-w64-x86_64-pkg-config

Just run launch your Linux/MSYS terminal and follow the instructions from the "Linux" subsection.

## How to run it

To run it, compile it with GCC and run the executable. There's a build script which you can modify for your own uses.

You can also just download it from the [releases tab](https://github.com/augustopereiratx/workers-and-resources-production-calculator/releases).

## License

The code is free and open source. You can download it, run it, modify it and redistribute it (GPLv3). Just credit me if you make a fork, ok?

## Stuff I haven't done yet

Right now basically everything works. You can calculate every factory's production line from top to bottom. The next thing is to put vehicle production chains.

I also want to calculate if the production chain is enough for the amount of workers it requires (e.g. if food production sustains the workers it requires and if there's anything remaining, as well as how many remaining workers that food factory can feed).

There is also sewage to be done still.

## Program usage

1. Choose a resource you want to produce and number of factories you want to build for it.
2. Click button "Calculate" or follow terminal instructions.
3. Number of factories and workers required to build up the production chain will be displayed on a table below or on the terminal.
