libs=-lGL -lGLU -lglut

.PHONY: all
all: drawer combination

combination: Combination.cpp
	g++ -o $@ $< $(libs)

drawer: drawer.cpp
	g++ -o $@ $< $(libs)
