// Author: Bob Rubbens - Knights of the Compiler
// Creation date: ma 10-08-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public
#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// Private
#include "game/Cloud.hpp"
#include "game/TypeTracker.hpp"
#include "main/functions.hpp"
#include "main/global.hpp"
#include "nnb/log/log.hpp"

SDL_Rect const cloudClip[4] = {
	{0, 0, 164, 83},
	{337, 0, 164, 83},
	{165, 0, 164, 83},
	{0, 0, 164, 83}
} ;

SDL_Rect const rainClip[2] = {
	{0, 0, 83, 480},
	{83, 0, 83, 480}
} ;

int cloudStateToInt(CloudState cs) {
	switch (cs) {
	case CloudState::RAINING:
		return 0;
	case CloudState::STORMY:
		return 1;
	case CloudState::LEAVING:
		return 2;
	case CloudState::ENTERING:
		return 3;
	case CloudState::DONE:
		return 4;
	default:
		NNB_LOG << "IMPOSSIBRUUU";
		return static_cast<int>(cs);
	}
}

Cloud::Cloud(std::string targetWord, SDL_Texture *cloudSkin, SDL_Texture *rainSkin, TTF_Font *cloudFont) :
word(targetWord),
skin(cloudSkin),
rain(rainSkin),
font(cloudFont),
stormyTimer(SDL_GetTicks()),
rainTimer(SDL_GetTicks()),
text(g_renderer) {
	text.setFont(font);
	text.setAlign(Align::CENTER);
	text.setColor(getSDLColor(0, 0, 0, 255));
	text.setText(word);
	text.commit();

	gotoNewDestination();
	startY = randfloat() * 248 + 100;
	targetY = startY;
	if (randfloat() < 0.5) {
		startX = 0 - cloudClip[cloudStateToInt(state)].w / 2;
	} else {
		startX = SCR_W + cloudClip[cloudStateToInt(state)].w / 2;
	}

	int distance = abs(startX - targetX);
	duration = distance / CLOUD_SPEED * 1000;

}

Cloud::~Cloud() {
}

void Cloud::logic(TypeTracker const &ttracker) {
	switch (state) {
	case CloudState::ENTERING:
		{
			int w = cloudClip[cloudStateToInt(state)].w;
			int left = text.getX() - w / 2;
			int right = text.getX() + w / 2;
			if (left > 0 && right > 0 && left < SCR_W && right < SCR_W) {
				state = CloudState::RAINING;
				stormyTimer = SDL_GetTicks();
			}
		}
	case CloudState::RAINING:
		if (SDL_GetTicks() - stormyTimer > CLOUD_STORMTIME * 1000) {
			state = CloudState::STORMY;
		}
	case CloudState::STORMY:
		if (ttracker.matchString(word) == TYPETRACKER_MATCH) {
			state = CloudState::LEAVING;
			text.setText("");
			text.commit();
			
			int w = cloudClip[cloudStateToInt(state)].w;
			startX = text.getX();
			if (randfloat() < 0.5) {
				targetX = w / -2;
			} else {
				targetX = SCR_W + w / 2;
			}
			cloudStart = SDL_GetTicks();
			duration = abs(targetX - startX) / CLOUD_SPEED * 1000;
		}


		if (SDL_GetTicks() - cloudStart >= duration) {
			gotoNewDestination();
		}
		break;
	case CloudState::LEAVING:
		if (SDL_GetTicks() - cloudStart >= duration) {
			state = CloudState::DONE;
		}
		break;
	case CloudState::DONE:
		break;
	default:
		NNB_LOG << "ERROR! This case is not supposed to be triggered. Value: " << cloudStateToInt(state);
		break;
	}

	if (SDL_GetTicks() - rainTimer >= 800) {
		rainTimer = SDL_GetTicks();
		rainIndex = (rainIndex + 1) % 2;
	}

	float dt = (SDL_GetTicks() - cloudStart) / (float) duration;
	int x = startX * (1 - dt) + targetX * dt;
	int y = startY * (1 - dt) + targetY * dt;

	text.setPosition(x, y);
}

void Cloud::render() const {
	if (state == CloudState::RAINING || state == CloudState::STORMY) {
		SDL_Rect dst;
		dst.w = rainClip[rainIndex].w;
		dst.h = rainClip[rainIndex].h;
		dst.x = text.getX() - dst.w / 2;
		dst.y = text.getY();
		SDL_RenderCopy(g_renderer, rain, &rainClip[rainIndex], &dst);
	}

	if (skin && state != CloudState::DONE) {
		SDL_Rect dst;
		dst.w = cloudClip[cloudStateToInt(state)].w;
		dst.h = cloudClip[cloudStateToInt(state)].h;
		dst.x = text.getX() - dst.w / 2;
		dst.y = text.getY() - 40;
		SDL_RenderCopy(g_renderer, skin, &cloudClip[cloudStateToInt(state)], &dst);

	}
	
	text.render(g_renderer);
}

CloudState Cloud::getState() const {
	return state;
}

void Cloud::gotoNewDestination() {
	startX = targetX;

	targetX = randfloat() * 280 + 180;
	cloudStart = SDL_GetTicks();

	int distance = abs(targetX - startX);
	duration = distance / CLOUD_SPEED * 1000;
}
