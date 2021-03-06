// Author: Bob Rubbens - Knights of the Compiler
// Creation date: ma 08-08-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef TYPETRACKER_HPP
#define TYPETRACKER_HPP

// Public
#include <SDL2/SDL.h>
#include <string>

// Private
#include <utils/Text.hpp>

int const TYPETRACKER_NOMATCH = 0;
int const TYPETRACKER_MATCH = -1;

class TypeTracker {
public:
	TypeTracker(SDL_Renderer *renderTgt, TTF_Font *renderFont);
	~TypeTracker();

	void event(SDL_Event &e);
	std::string getCurrentString() const;
	int matchString(std::string other) const;
	void clear();
	void freeze();
	
	void render() const;
private:
	std::string currStr = "";
	Text text;
	bool frozen = false;
} ;

#endif
