CC ?= gcc

OBJECTS = $(patsubst src/%.c,build/%.o,$(wildcard src/*.c))

all: build/scoban

build:
	mkdir -p build

clean:
	rm -rf build

build/scoban: $(OBJECTS)
	$(CC) -g -o $@ $^

build/%.o: src/%.c | build
	$(CC) -Og -c -o $@ $<
