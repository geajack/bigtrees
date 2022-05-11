main: main.cpp
	gcc -o main main.cpp -lSDL2 -lm

run: main
	./main