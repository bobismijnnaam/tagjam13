// Author: Bob Rubbens - Knights of the Compiler
// Creation date: ma 21-07-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public
#include <cmath>
#include <Eigen/Dense>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>

// Private
#include "gamestates/gsMain.hpp"
#include "main/global.hpp"
#include "nnb/states/GameState.hpp"
#include "nnb/log/log.hpp"
#include "nnb/utils/constants.hpp"

gsMain::gsMain() :
bg(IMG_LoadTexture(g_renderer, "media/backgrounds/front.png")) {
	
}

gsMain::~gsMain() {
	SDL_DestroyTexture(bg);
}

void gsMain::event(SDL_Event& e) {
	
	switch (e.type) {
		case SDL_QUIT:
			g_gm->changeState(nnb::StateAction::SET, nnb::StateMachine::STATE_EXIT);
			NNB_LOG << "Exit was requested";
			break;
		case SDL_MOUSEBUTTONUP:
			NNB_LOG << "Mouse button was pressed at (" << e.button.x << "; " << e.button.y << ")";
			break;
		case SDL_KEYDOWN:
			if (e.key.keysym.sym == SDLK_RETURN) {
				g_gm->changeState(nnb::StateAction::SET, "game");
			}
		default:
			break;
	}

}

void gsMain::logic(float delta) {
	
}

void gsMain::render() const {
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_renderer);

	SDL_RenderCopy(g_renderer, bg, NULL, NULL);

	SDL_RenderPresent(g_renderer);
}

void gsMain::activate() {
	stateStart = SDL_GetTicks();
	NNB_LOG << "main activated";
}

void gsMain::deactivate() {
	NNB_LOG << "main deactivated";
}

std::string gsMain::getID() {
	return "main";
}
