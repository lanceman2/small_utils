# This is a GNU make file.

-include config.make

VERSION := 0.2
PREFIX ?= /usr/local/encap/small_utils-$(VERSION)

# prefix prepended to all installed files in bin
#PRE ?= U
PRE ?=

built_image_bins =\
 rotateRight\
 rotateLeft\
 flip\
 flop

# files installed in PREFIX/bin
bin =\
 md2githtml\
 errno\
 spew\
 colorSelecter\
 colorSelecter3\
 fontSelecter\
 warn\
 makeWallPaper\
 sizeof\
 m3u2list\
 PushSshKeys\
 SaveGitWork\
 MovePointer\
 Gnuradio-companion\
 grrun\
 LinesOfCCode\
 $(built_image_bins)

# These files are generated
built =\
 errno.c\
 errno\
 spew\
 colorSelecter\
 colorSelecter3\
 fontSelecter\
 MovePointer\
 $(built_image_bins)

CFLAGS := -g -Wall -Wno-deprecated

colorSelecter_CFLAGS = $(shell pkg-config --cflags gtk+-2.0)
colorSelecter_LFLAGS = $(shell pkg-config --libs gtk+-2.0)
colorSelecter3_CFLAGS = $(shell pkg-config --cflags gtk+-3.0)
colorSelecter3_LFLAGS = $(shell pkg-config --libs gtk+-3.0)
fontSelecter_CFLAGS = $(shell pkg-config --cflags gtk+-3.0)
fontSelecter_LFLAGS = $(shell pkg-config --libs gtk+-3.0)
MovePointer_LFLAGS = -lX11


# imagemagick's convert @OPERATION@ "${1}" ${tmpfile} 
rotateRight_OPERATION = "-rotate 90"
rotateLeft_OPERATION = "-rotate -90"
flip_OPERATION = "-flip"
flop_OPERATION = "-flop"

#This will replace the IMAGE_FILE with the same type of image file that is
rotateRight_DESC = "rotated 90 degrees to the right"
rotateLeft_DESC = "rotated 90 degrees to the left"
flip_DESC = "fliped top to bottom"
flop_DESC = "floped left to right"



build: $(built)


$(built_image_bins): image_ GNUmakefile
	(echo "#!/bin/bash" > $@ &&\
 echo "# This is a generated file" >> $@ &&\
 sed $< -e s/@PROG@/$@/g\
   -e s/@OPERATION@/$($@_OPERATION)/g\
   -e s/@DESC@/$($@_DESC)/g >> $@ &&\
 chmod 755 $@ ) || exit 1


%: %.c
	$(CC) $(CFLAGS) -Wall -g $($@_CFLAGS) $^ -o $@ $($@_LFLAGS)

errno.c: mk_errno_c.bash
	./mk_errno_c.bash > $@

mkdirs:
	mkdir -p $(PREFIX)/bin


install: $(built) mkdirs 
	for b in $(bin) ; do\
	  cp $$b $(PREFIX)/bin/$(PRE)$$b ;\
	  done

clean:
	rm -f $(built)

distclean: clean
	rm -f config.make

