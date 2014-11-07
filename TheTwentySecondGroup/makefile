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

M64 = -m32
ARCH = x86
ifeq "$(M64)" "-m64"
    ARCH=x64
endif
  
EXAMPLE     = testprogram
BINDIR      = ./
SRCS 		= $(shell ls source/*.cpp)
OBJDIR      = obj
LIBDIR      = lib/gcc4/$(ARCH)/$(VARIANT)
INCDIR      = include

TARGET      = $(BINDIR)/$(EXAMPLE)
OBJS        = \
	./source/main.o\
	./source/draw.o\
    ./source/Model.o 
OBJSFINAL   = \
	$(OBJDIR)/main.o\
	$(OBJDIR)/draw.o\
    $(OBJDIR)/Model.o

CC          = gcc
LD          = gcc 
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

LIBS = $(FBXSDK_LIB) -lm -lrt -luuid -lstdc++ -lpthread -ldl   -lglut -lGLU -lGL -lSDL -lSDL_image -lSDL_gfx -lSDL_ttf  -lcwiimote 

.SUFFIXES: .cpp

all: $(TARGET)

$(TARGET): $(OBJS)
	mkdir -p $(BINDIR)
	$(LD) $(CXXFLAGS) $(LDFLAGS) -o $@ $(OBJSFINAL) -L$(LIBDIR) -L/usr/lib $(LIBS) $(RPATH_DEF)

.cpp.o:
	mkdir -p $(OBJDIR)
	$(CC) $(CXXFLAGS) -I$(INCDIR) -c $< -o $*.o
	mv $*.o $(OBJDIR)

clean:
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)







