// Author: Bob Rubbens - Knights of the Compiler
// Creation date: ma 08-08-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public
#include <boost/lexical_cast.hpp>
#include <cmath>
#include <Eigen/Dense>
#include <algorithm>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>

// Private
#include "gamestates/gsGame.hpp"
#include "main/functions.hpp"
#include "main/global.hpp"
#include "nnb/states/GameState.hpp"
#include "nnb/log/log.hpp"
#include "nnb/utils/constants.hpp"

void renderProper(SDL_Texture *txtr, int x, int y) {
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	SDL_QueryTexture(txtr, NULL, NULL, &dst.w, &dst.h);

	SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);
	dst.w += 30;
	dst.x -= 20;
	SDL_RenderFillRect(g_renderer, &dst);

	dst.x = x;
	SDL_QueryTexture(txtr, NULL, NULL, &dst.w, &dst.h);

	SDL_RenderCopy(g_renderer, txtr, NULL, &dst);
}

gsGame::gsGame() :
typetracker(g_renderer, proFont),
cloudManager(),
lastCloud(SDL_GetTicks()),
bg(IMG_LoadTexture(g_renderer, "media/backgrounds/bg.png")),
sea(IMG_LoadTexture(g_renderer, "media/sprites/sea.png")),
grass(IMG_LoadTexture(g_renderer, "media/backgrounds/grass_ground.png")),
buildings(IMG_LoadTexture(g_renderer, "media/backgrounds/buildings.png")) {
}

gsGame::~gsGame() {
	SDL_DestroyTexture(bg);
	SDL_DestroyTexture(sea);
	SDL_DestroyTexture(grass);
	SDL_DestroyTexture(buildings);
}

void gsGame::event(SDL_Event& e) {
	
	typetracker.event(e);

	switch (e.type) {
		case SDL_QUIT:
			g_gm->changeState(nnb::StateAction::SET, nnb::StateMachine::STATE_EXIT);
			NNB_LOG << "Exit was requested";
			break;
		case SDL_MOUSEBUTTONUP:
			NNB_LOG << "Mouse button was pressed at (" << e.button.x << "; " << e.button.y << ")";
			break;
		case SDL_KEYDOWN:
			if (e.key.keysym.sym == SDLK_RETURN && gameIsOver) {
				g_gm->changeState(nnb::StateAction::SET, "game");
			}
			break;
		default:
			break;
	}

}

void gsGame::logic(float delta) {
	if (SDL_GetTicks() - lastCloud >= 1100) {
		cloudManager.launchCloud();
		lastCloud = SDL_GetTicks();
	}
	
	cloudManager.logic(typetracker, delta);

	if ((cloudManager.getWaterLvl() >= 5.8) && !gameIsOver) {
		triggerEndScreen();
	}
}

void gsGame::render() const {
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_renderer);
	
	// Render scenery
	// Blue sky
	SDL_RenderCopy(g_renderer, bg, NULL, NULL);

	SDL_Rect dst;

	// Buildings
	dst.x = 188;
	dst.y = 207;
	SDL_QueryTexture(buildings, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(g_renderer, buildings, NULL, &dst);

	// Sea
	float p = cloudManager.getWaterLvl();
	dst.x = 0;
	dst.y = std::max(430 + 50 * (1 - p), 0.0f);
	SDL_QueryTexture(sea, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(g_renderer, sea, NULL, &dst);
	
	// Clouds of DOOOOM11
	cloudManager.render(g_renderer);

	// Grass
	dst.x = 50;
	dst.y = 430;
	SDL_QueryTexture(grass, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(g_renderer, grass, NULL, &dst);

	typetracker.render();

	if (gameIsOver) {
		renderProper(gameOver, 70, 60);
		renderProper(score, 150, 250);
		renderProper(playagain, 150, 350);
	}

	SDL_RenderPresent(g_renderer);
}

void gsGame::activate() {
	NNB_LOG << "main activated";
}

void gsGame::deactivate() {
	NNB_LOG << "main deactivated";
}

void gsGame::triggerEndScreen() {
	typetracker.freeze();
	
	SDL_Color clr = {255,255,255, 255};
	
	SDL_Surface *ts = TTF_RenderText_Blended(proFontBig, "GAME OVER", clr); 
	gameOver = SDL_CreateTextureFromSurface(g_renderer, ts);
	SDL_FreeSurface(ts);

	ts = TTF_RenderText_Blended(proFont, ("Your score: " + boost::lexical_cast<std::string>(cloudManager.getTypedWords())).c_str(), clr); 
	score = SDL_CreateTextureFromSurface(g_renderer, ts);
	SDL_FreeSurface(ts);

	ts = TTF_RenderText_Blended(proFont, "Play again? Press [ENTER]!", clr); 
	playagain = SDL_CreateTextureFromSurface(g_renderer, ts);
	SDL_FreeSurface(ts);

	gameIsOver = true;

	NNB_LOG << "Engame!";
}

std::string gsGame::getID() {
	return "game";
}

