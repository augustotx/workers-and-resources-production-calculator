# linux
gcc `pkg-config --cflags gtk+-3.0` *.c gui/*.c -o soviet-calc `pkg-config --libs gtk+-3.0`
# windows build from linux (requires mingw-w64)
x86_64-w64-mingw32-gcc `x86_64-w64-mingw32-pkg-config --cflags gtk+-3.0` *.c gui/*.c -o soviet-calc `x86_64-w64-mingw32-pkg-config --libs gtk+-3.0`