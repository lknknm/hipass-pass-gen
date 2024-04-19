CFLAGS += -g -fsanitize=undefined,address -Wall -Wextra -Wshadow
CPPFLAGS += -isystem extern/include
CXXFLAGS += $(CFLAGS) -std=c++17
DEST_DIR ?= /usr/local
MAN_DIR ?= share/man/man1

sources = $(wildcard src/*.c src/*.cpp)
objects = $(sources:src/%=build/%.o)
manuals = $(wildcard docs/*.1.gz)

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
	cp -R $(manuals) $(DEST_DIR)/$(MAN_DIR)

.PHONY: unisntall
uninstall:
	rm -f $(DEST_DIR)/bin/$(notdir $(prog))
