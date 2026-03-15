CC = g++
FLAGS = -I include -I /opt/homebrew/include -L /opt/homebrew/lib -lglfw -framework OpenGL -lm -DGL_SILENCE_DEPRECATION
SRC = main.cpp glad.c

main: $(SRC)
	$(CC) $(SRC) $(FLAGS) -o main

clean:
	rm -f main