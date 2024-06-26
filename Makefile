CC = gcc
PKG_CONFIG	?= pkg-config
CFLAGS = -I/usr/include -I/usr/include/ogg -I/usr/include/opus -I/usr/include/stb -Iinclude/imgtotxt/ext -Iinclude/imgtotxt -I/usr/include/ffmpeg -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -Iinclude/miniaudio -O1 $(shell $(PKG_CONFIG) --cflags libavcodec libavutil libavformat libswresample gio-2.0 chafa fftw3f opus opusfile vorbis)
CFLAGS += -fstack-protector-strong -Wformat -Werror=format-security -fPIE -fstack-protector -fstack-protector-strong -D_FORTIFY_SOURCE=2
CFLAGS += -Wall -Wextra -Wpointer-arith
LIBS = -L/usr/lib -lfreeimage -lpthread -lrt -pthread -lm -lglib-2.0  $(shell $(PKG_CONFIG) --libs libavcodec libavutil libavformat libswresample gio-2.0 chafa fftw3f opus opusfile vorbis vorbisfile)
LDFLAGS = -pie -Wl,-z,relro

ifeq ($(CC),gcc)
    LIBS += -latomic
endif

OBJDIR = src/obj
PREFIX = /usr
SRCS = src/common_ui.c src/sound.c src/directorytree.c src/soundcommon.c src/search_ui.c src/playlist_ui.c src/player.c src/soundbuiltin.c src/mpris.c src/playerops.c src/utils.c src/file.c src/chafafunc.c src/cache.c src/songloader.c src/playlist.c src/term.c  src/settings.c src/visuals.c src/kew.c
OBJS = $(SRCS:src/%.c=$(OBJDIR)/%.o)

MAN_PAGE = kew.1
MAN_DIR ?= $(PREFIX)/share/man

all: kew

$(OBJDIR)/%.o: src/%.c Makefile | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/write_ascii.o: include/imgtotxt/write_ascii.c Makefile | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $< $(LDFLAGS)

$(OBJDIR):
	mkdir -p $(OBJDIR)

kew: $(OBJDIR)/write_ascii.o $(OBJS) Makefile
	$(CC) -o kew $(OBJDIR)/write_ascii.o $(OBJS) $(LIBS)

.PHONY: install
install: all
	mkdir -p $(DESTDIR)$(MAN_DIR)/man1
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	install -m 0755 kew $(DESTDIR)$(PREFIX)/bin/kew
	install -m 0644 docs/kew.1 $(DESTDIR)$(MAN_DIR)/man1/kew.1

.PHONY: uninstall
uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/kew
	rm -f $(DESTDIR)$(MAN_DIR)/man1/kew.1

.PHONY: clean
clean:
	rm -rf $(OBJDIR) kew
