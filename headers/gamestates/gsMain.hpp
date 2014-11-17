// Author: Bob Rubbens - Knights of the Compiler
// Creation date: ma 21-07-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef GSMAIN_HPP
#define GSMAIN_HPP

// Public
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <Eigen/Dense>

// Private
#include "nnb/states/GameState.hpp"
#include "nnb/utils/FloatRect.hpp"

class gsMain : public nnb::GameState {
public:
	gsMain();
	~gsMain();

	void event(SDL_Event& e);
	void logic(float delta);
	void render() const;

	void activate(); 
	void deactivate();

	std::string getID();

private:
	Uint32 stateStart = 0;
	SDL_Texture *bg;
} ;

#endif
