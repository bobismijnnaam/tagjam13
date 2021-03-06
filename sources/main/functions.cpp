// Author: Bob Rubbens - Knights of the Compiler
// Creation date: ma 10-08-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// Private
#include "main/global.hpp"

SDL_Color getSDLColor(int r, int g, int b, int a) {
	SDL_Color clr;
	clr.r = r;
	clr.g = g;
	clr.b = b;
	clr.a = a;

	return clr;
}

float randfloat() {
	return randgen() / (float) randgen.max();
}

