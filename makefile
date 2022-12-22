all:
	gcc -I./include -L./lib -o main.exe src/main.c -lmingw32 -lSDL2main -lSDL2