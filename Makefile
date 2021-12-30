LUA_VERSION =       5.4
TARGET =            ../../luaclib/mapSearch.so
PREFIX =            /usr/local
CFLAGS =            -O3 -g -Wall -pedantic -DNDEBUG -Wunused-function
CADD_CFLAGS =       -fPIC -std=gnu++11
LUA_INCLUDE_DIR =   ../../skynet/3rd/lua

LNK_FLAGS = -Xlinker --unresolved-symbols=ignore-in-shared-libs
LNX_LDFLAGS = -shared -lstdc++ -lm
MAC_LDFLAGS = -shared -undefined dynamic_lookup -lstdc++ -lm

CC = gcc
LDFLAGS = $(MYLDFLAGS)

BUILD_CFLAGS =      -I$(LUA_INCLUDE_DIR) $(CADD_CFLAGS)
OBJS =              lua-mapSearch.o mapSearch.o wrapper.o

all:
	@echo "Usage: $(MAKE) <platform>"
	@echo "  * linux"
	@echo "  * macosx"
	@echo "  * demo"
	@echo "  * demo2"
	@echo "  * clean"

.c.o:
	$(CC) -c $(CFLAGS) $(BUILD_CFLAGS) -o $@ $<

.cpp.o:
	$(CC) -c $(CFLAGS) $(BUILD_CFLAGS) -o $@ $<

linux:
	@$(MAKE) $(TARGET) MYLDFLAGS="$(LNX_LDFLAGS)"

macosx:
	@$(MAKE) $(TARGET) MYLDFLAGS="$(MAC_LDFLAGS)"

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

demo:
	$(CC) -o $@ -I./ -std=gnu++11 -lstdc++ -lm astar_demo.cpp

demo2:
	$(CC) -o $@ -g -I./ -std=gnu++11 -lstdc++ -lm astar_demo2.cpp mapSearch.cpp

clean:
	rm -f *.o *.so demo demo2 test
