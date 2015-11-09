CC=g++
CPPFLAGS=-c -std=c++11
LDLIBS=-lsfml-system -lsfml-window -lsfml-graphics
SOURCES=main.cpp game.cpp game.hpp m_menu.cpp m_menu.hpp m_option.cpp m_option.hpp
OBJECTS=main.o game.o m_menu.o m_option.o
EXECUTABLE=kuhat

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDLIBS)

.cc.o:
	$(CC) $(CPPFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

run: kuhat
	./kuhat
