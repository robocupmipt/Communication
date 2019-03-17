PROJECT = server

SOURCES = src/main.cpp src/server.cpp
INCLUDES += -I include
LIBS =
DEFINES =
CFLAGS = #-Wall -Wextra
COMP = g++

OBJS = $(SOURCES:.cpp=.o)

CFLAGS += $(DEFINES) $(INCLUDES) $(DEFINES)

RM = rm -rf

.PHONY: all clean tags

link: $(OBJS)
	$(COMP) -o $(PROJECT) $(OBJS) $(LIBS)

all: clean link

clean:
	$(RM) $(PROJECT) $(OBJS)

%.o: %.cpp
	$(COMP) $(CFLAGS) -c $(@:.o=.cpp) -o $@

tags:
	ctags -R
