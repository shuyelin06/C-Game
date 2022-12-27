# Compiler
CC 			= gcc
# Flags
FLAGS		:= -MMD
# Include Directories
INCLUDE		= -I./include -I./src

# Library Path
LIB			= -L./lib
# Library Files
LIBPATH 	:= -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

# Source Files 
SOURCES		:= main.c rendering/graphics.c physics/physics.c geometry/polygon.c components/game.c
# Object Files
OBJECTS 	:= $(patsubst %.c, bin/%.o, ${SOURCES})
# Target File
EXE  		= main.exe

# Default Target
default: all
all: ${EXE}

# Target Dependencies
${EXE}: ${OBJECTS}
	${CC} ${FLAGS} ${LIB} ${OBJECTS} -o ${EXE} ${LIBPATH}

# Compiling Object Files
bin/%.o: src/%.c
	$(CC) ${FLAGS} ${INCLUDE} -c $< -o $@

# Include Dependencies
-include $(OBJECTS:.o=.d)