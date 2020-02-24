# --	compiler
CC = clang

#	--	include paths
INC = -I./include

# --	objects
OBJS = src/main.o

#	--	libraries
LIBS = -lm -lSDL -lSDL_image

#	--	objs, names
OBJS := src/main.o src/fade.o src/mokou.o src/keine.o
OBJS += src/kosuzu.o src/player.o src/kaguya.o
NAME = build/mokokene

#	--	main event
%.o: %.c
	$(CC) -c -o $@ $< $(INC) -Wall -Wextra

$(NAME): $(OBJS)
	$(CC) -o $@ $^ $(INC) $(LIBS)

clean:
	rm $(OBJS)

