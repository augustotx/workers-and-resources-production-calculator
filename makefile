BUILDDIR=$(CURDIR)/bin

all:
	mkdir -p $(BUILDDIR)
	mkdir -p $(BUILDDIR)/gui

	cc `pkg-config --cflags gtk+-3.0` *.c gui/*.c -o $(BUILDDIR)/soviet-calc `pkg-config --libs gtk+-3.0`
	cp gui/*.glade $(BUILDDIR)/gui


clean:
	BUILDDIR=$(CURDIR)/bin
	cd $(BUILDDIR)
	rm -rf $(BUILDDIR)