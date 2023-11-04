# linux
#gcc *.c -o soviet-calc
cc `pkg-config --cflags gtk+-3.0` *.c gui/*.c -o soviet-calc `pkg-config --libs gtk+-3.0`
echo "IMPORTANT: Keep the 'gui' folder in the same place as the executable file. It contains '*.glade' files required to run GUI."
# windows (requires mingw-w64)
# x86_64-w64-mingw32-gcc *.c -o soviet-calc
echo "WARNING: Windows cross-compilation currently does not work :("
