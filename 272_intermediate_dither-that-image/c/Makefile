.SUFFIXES:
.SUFFIXES: .c .o

CC = clang
CFLAGS = -g -Wall -std=c89
INCLUDES = -I. -I/usr/local/include/SDL2
LIBS = -L/usr/local/lib
SDL_LIBS = -lSDL2 -lSDL2_image
OBJS = test_sdl.o

test_sdl : $(OBJS)
	@echo "Building.."
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS) $(SDL_LIBS)

%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: clean test

clean:
	@echo "Cleaning up.."
	-rm -rf $(OBJS)
	-rm test_sdl

test: test_sdl
	@echo "Testing"
	./test_sdl
