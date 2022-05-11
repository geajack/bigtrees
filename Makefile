main: main.cpp
	g++ -o main main.cpp -lSDL2 -lm

run: main
	./main