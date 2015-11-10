libs=-lGL -lGLU -lglut

.PHONY: all
all: drawer

drawer: drawer.cpp
	g++ -o $@ $< $(libs)
