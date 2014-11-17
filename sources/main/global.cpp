// Author: Bob Rubbens - Knights of the Compiler
// Creation date: ma 21-07-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public
#include <chrono>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <random>
#include <vector>

// Private
#include "main/global.hpp"
#include "nnb/states/StateMachine.hpp"

SDL_Window *g_window = NULL;
SDL_Surface *g_windowSurface = NULL;
SDL_Renderer *g_renderer = NULL;

TTF_Font *proggyClean = NULL;
TTF_Font *proFont = NULL;
TTF_Font *proFontSmall = NULL;
TTF_Font *proFontMedium = NULL;
TTF_Font *proFontBig = NULL;

nnb::StateMachine *g_gm = NULL;

std::vector<std::string> words {
	"xbox",
	"hard",
	"drive",
	"gamedev",
	"indie",
	"steam",
	"gabe",
	"sdl",
	"libgdx",
	"arbitrary",
	"gamejam",
	"development",
	"masterrace",
	"cementation",
	"triterpene",
	"cementation",
	"asteroid",
	"psycho",
	"laughter",
	"community",
	"bread",
	"broiling",
	"furniture",
	"hyphenated"
} ;

std::mt19937 randgen(std::chrono::system_clock::now().time_since_epoch().count()); 
