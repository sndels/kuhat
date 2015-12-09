CC=g++
CPPFLAGS=-O2 -g -Wall -std=c++11
LDLIBS=-lsfml-system -lsfml-window -lsfml-graphics
SRCDIR=src
OBJDIR=obj
OBJECTS=$(OBJDIR)/main.o $(OBJDIR)/game.o $(OBJDIR)/minIni.o
EXECUTABLE=kuhat

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CPPFLAGS) $(OBJECTS) -o $(EXECUTABLE) $(LDLIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJDIR)/minIni.o: resource/libs/minIni/minIni.c
	$(CC) $(CPPFLAGS) -c $< -o $@

clean:
	-rm -f $(OBJECTS) kuhat

run: kuhat
	./kuhat
