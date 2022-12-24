all:
	gcc -I./include -L./lib -o main.exe src/main/main.c src/rendering/graphics.c src/physics/physics.c -lmingw32 -lSDL2main -lSDL2