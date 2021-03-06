// Author: Bob Rubbens - Knights of the Compiler
// Creation date: ma 08-08-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef CLOUD_HPP
#define CLOUD_HPP

// Public
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// Private
#include <game/TypeTracker.hpp>
#include <utils/Text.hpp>

enum class CloudState {
	RAINING = 0,
	STORMY = 1,
	LEAVING = 2,
	ENTERING = 3,
	DONE = 4
} ;

int cloudStateToInt(CloudState cs);

// Ofcourse, in Pixels Per Second
const float CLOUD_SPEED = 30;
// Cloud turns into storm after 40 secs
const int CLOUD_STORMTIME = 40;
extern SDL_Rect const cloudClip[4];
extern SDL_Rect const rainClip[2];

class Cloud {
public:
	Cloud(std::string targetWord, SDL_Texture *cloudSkin, SDL_Texture *rainSkin, TTF_Font *cloudFont);
	~Cloud();

	void logic(TypeTracker const &ttracker);
	void render() const;

	CloudState getState() const;
	void gotoNewDestination();

private:
	std::string word;
	SDL_Texture *skin;
	SDL_Texture *rain;
	TTF_Font* font;
	int targetX = 0, targetY = 0;
	int startX = 0, startY = 0;
	float duration = 0, cloudStart = 0;
	int stormyTimer;
	int rainTimer;
	int rainIndex = 0;
	Text text;
	CloudState state = CloudState::ENTERING;
	bool safe = false;
	bool done = false;
} ;

#endif
