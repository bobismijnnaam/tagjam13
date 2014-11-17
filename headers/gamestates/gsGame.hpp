// Author: Bob Rubbens - Knights of the Compiler
// Creation date: ma 21-07-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef GSGAME_HPP  
#define GSGAME_HPP  

// Public
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <Eigen/Dense>

// Private
#include "nnb/states/GameState.hpp"
#include "nnb/utils/FloatRect.hpp"
#include "game/CloudManager.hpp"
#include "game/TypeTracker.hpp"

class gsGame : public nnb::GameState {
public:
	gsGame();
	~gsGame();

	void event(SDL_Event &e);
	void logic(float delta);
	void render() const;

	void activate(); 
	void deactivate();

	void triggerEndScreen();

	std::string getID();

private:
	TypeTracker typetracker;
	CloudManager cloudManager;
	int lastCloud;
	bool gameIsOver = false;

	SDL_Texture *bg;
	SDL_Texture *sea;
	SDL_Texture *grass;
	SDL_Texture *buildings;

	SDL_Texture *gameOver = NULL;
	SDL_Texture *score = NULL;
	SDL_Texture *playagain = NULL;
} ;

#endif
