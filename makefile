SHELL       = /bin/sh

# default config:
#    release
#    x86
#    shared
#    
#    to build 64 bit:                make -e M64=-m64
#    to build static:                make -e STATIC_LINK=1
#    to build 64 bit static debug:   make -e M64=-m64 STATIC_LINK=1 VARIANT=debug
#

VARIANT      = release
ifeq "$(VARIANT)" "debug"
    GCC_DEBUG_FLAGS += -g -D_DEBUG
endif

M64 = -m64
ARCH = x86
ifeq "$(M64)" "-m64"
    ARCH=x64
endif
  
EXAMPLE     = Calamity
BINDIR      = ./
SRCS 		= $(shell ls source/*.cpp)
OBJDIR      = obj
LIBDIR      = lib/gcc4/$(ARCH)/$(VARIANT)
INCDIR      = include

TARGET      = $(BINDIR)/$(EXAMPLE)
OBJS        = \
	./source/main.o\
	./source/draw.o\
    ./source/Model.o\
    ./source/Map.o\
    ./source/Effect.o\
    ./source/system.o\
    ./source/Title.o\
    ./source/Tutorial.o\
    ./source/Player.o\
    ./source/io.o\
    ./source/net.o\
    ./source/netBase.o\
    ./source/lightEffect.o
    
OBJSFINAL   = \
	$(OBJDIR)/main.o\
	$(OBJDIR)/draw.o\
    $(OBJDIR)/Model.o\
    $(OBJDIR)/Map.o\
    $(OBJDIR)/Effect.o\
    $(OBJDIR)/system.o\
    $(OBJDIR)/Title.o\
    $(OBJDIR)/Tutorial.o\
    $(OBJDIR)/Player.o\
    $(OBJDIR)/io.o\
    $(OBJDIR)/net.o\
    $(OBJDIR)/netBase.o\
    $(OBJDIR)/lightEffect.o

CC          = g++
LD          = g++
RM          = /bin/rm -f

CXXFLAGS    = $(M64) $(GCC_DEBUG_FLAGS)  
LDFLAGS     = $(M64) $(GCC_LINK_FLAGS)

RPATH_DEF    =
STATIC_LINK  =
FBXSDK_LIB   = -lfbxsdk
ifeq "$(STATIC_LINK)" ""
    CXXFLAGS += -DFBXSDK_SHARED
    RPATH_DEF = -Wl,-rpath $(PWD)/$(LIBDIR)
else
    FBXSDK_LIB = $(LIBDIR)/libfbxsdk.a
endif


LIBS = $(FBXSDK_LIB) -lrt  -lstdc++ -lpthread -ldl -lGL -lGLU -lglut -lSDL  -lSDL_image -lSDL_gfx -lSDL_ttf -lSDL_mixer  -lcwiimote   -I/usr/local/include/opencv -I/usr/local/include/opencv2   -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_core -lopencv_highgui -lopencv_imgproc 

.SUFFIXES: .cpp

all: $(TARGET)

$(TARGET): $(OBJS)
	mkdir -p $(BINDIR)
	gcc $(CXXFLAGS) -I$(INCDIR)  -c ./source/Wii.c -o Wii.o
	$(LD) $(CXXFLAGS) $(LDFLAGS) -o $@ $(OBJSFINAL)  Wii.o  -L$(LIBDIR) $(LIBS) -L/usr/lib $(RPATH_DEF)
	rm Wii.o
.cpp.o:
	mkdir -p $(OBJDIR)
	$(CC) $(CXXFLAGS) -I$(INCDIR)  -c $< -o $*.o
	mv $*.o $(OBJDIR)

clean:
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)







