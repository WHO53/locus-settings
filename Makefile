NAME=locus-settings
BIN=${NAME}
SRC=.

PKGS = locus libnm upower-glib

LOCUS_SETTINGS_SOURCES += $(wildcard $(SRC)/*.c) $(wildcard $(SRC)/**/*.c)
LOCUS_SETTINGS_HEADERS += $(wildcard $(SRC)/*.h) $(wildcard $(SRC)/**/*.h)

CFLAGS += -std=gnu99 -Wall -g -Wno-format-truncation
CFLAGS += $(shell pkg-config --cflags $(PKGS))
LDFLAGS += $(shell pkg-config --libs $(PKGS)) -lm -lutil -lrt

SOURCES = $(LOCUS_SETTINGS_SOURCES)

OBJECTS = $(SOURCES:.c=.o)

all: ${BIN}

$(OBJECTS): $(LOCUS_SETTINGS_HEADERS)

$(BIN):$(OBJECTS)
	$(CC) -o $(BIN) $(OBJECTS) $(LDFLAGS)

clean:
	rm -f $(OBJECTS) ${BIN}

format:
	clang-format -i $(LOCUS_SETTINGS_SOURCES) $(LOCUS_SETTINGS_HEADERS)
