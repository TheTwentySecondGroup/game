SRC = main.cpp draw.cpp Title.cpp Effect.cpp Tutorial.cpp mode.cpp Map.cpp system.cpp
HEADERS = global.h draw.h Title.h Effect.h Tutorial.h mode.h Map.h system.h
OBJS = main.o draw.o Title.o Effect.o Tutorial.o mode.o Map.o system.o

.SUFFIXES: .c .o


main: $(OBJS)  $(HEADERS)
	$(CC) -o $@ $(OBJS) -g  -D_ENABLE_TILT -D_ENABLE_FORCE  -lm  -lglut -lGLU -lGL -lSDL -lSDL_image -lSDL_gfx -lSDL_ttf  -lcwiimote  -lpthread -luuid -L/usr/lib
	rm -rf $(OBJS) *~


.c.o: 
	$(CC) -c -g  $<
                                                             
clean:
	rm -rf $(OBJS) *~
