CFLAGS += -g -fsanitize=undefined,address -Wall -Wextra -Wshadow
CXXFLAGS += $(CFLAGS) -std=c++17
DEST_DIR ?= /usr/local

sources = $(wildcard src/*.c src/*.cpp)
objects = $(sources:src/%=build/%.o)

prog = build/hipass

.PHONY: all
all: $(prog)

.PHONY: test
test: all
	./$(prog)

.PHONY: clean
clean:
	rm -f $(objects)
	rm -f $(prog)

$(prog): $(objects)
	$(LINK.cc) $^ -o $@ $(LDLIBS)

build/%.c.o: src/%.c
	@mkdir -p build
	$(COMPILE.c) $< -o $@

build/%.cpp.o: src/%.cpp
	@mkdir -p build
	$(COMPILE.cc) $< -o $@

.PHONY: install
install: $(prog)
	cp $< $(DEST_DIR)/bin/$(notdir $<)

.PHONY: unisntall
uninstall:
	rm -f $(DEST_DIR)/bin/$(notdir $(prog))
