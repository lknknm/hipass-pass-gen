CFLAGS += -Wall -Wextra -Wshadow

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
