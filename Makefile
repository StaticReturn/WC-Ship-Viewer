# Makefile for OSX
# 

CC	= clang
CFLAGS	= -Wall -O0 -g -I /Library/Frameworks/SDL2.framework/Headers
LDFLAGS	= -framework SDL2 -lcurses
OBJ	= main.o image.o sdl_graphics.o file.o viewer.o
HFILES = main.h filedata.h palette.h

# Create a dynamically linked binary.
prince: $(OBJ)
	$(CC) -o wc $^ $(LDFLAGS) 

%.o: %.c $(HFILES)
	$(CC) -c $< $(CFLAGS)

clean:
	rm -rf $(OBJ) wc
