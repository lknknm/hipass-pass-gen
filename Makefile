CFLAGS += -g -fsanitize=undefined,address -Wall -Wextra -Wshadow
DEST_DIR ?= /usr/local

sources = $(wildcard src/*.c)
objects = $(sources:src/%.c=build/%.o)

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
	$(LINK.c) $^ -o $@ $(LDLIBS)

build/%.o: src/%.c
	@mkdir -p build
	$(COMPILE.c) $< -o $@

.PHONY: install
install: $(prog)
	cp $< $(DEST_DIR)/bin/$(notdir $<)

.PHONY: unisntall
uninstall:
	rm -f $(DEST_DIR)/bin/$(notdir $(prog))
