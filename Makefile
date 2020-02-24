# --	compiler
CC = clang

#	--	include paths
INC = -I./include

# --	objects
OBJS = src/main.o

#	--	libraries
LIBS = -lm -lSDL -lSDL_image

#	--	objs, names
OBJS = src/main.o src/mokou.o src/keine.o src/kosuzu.o src/player.o src/kaguya.o
NAME = mokokene

#	--	main event
%.o: %.c
	$(CC) -c -o $@ $< $(INC) -Wall -Wextra

$(NAME): $(OBJS)
	$(CC) -o $@ $^ $(INC) $(LIBS)

clean:
	rm $(OBJS)

