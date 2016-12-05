.SUFFIXES:
.SUFFIXES: .c .o

CC = cc
CFLAGS =
INCLUDES = -I. -I/usr/local/include
LIBS = -L/usr/local/lib
SDL_LIBS = -lSDL2 -lSDL2_image
OBJS = test_sdl.o

test_sdl : $(OBJS)
	@echo "Building.."
	cc -o $@ $(OBJS) $(LIBS) $(SDL_LIBS)

%.o : %.c
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning up.."
	-rm -rf $(OBJS)
	-rm test_sdl
