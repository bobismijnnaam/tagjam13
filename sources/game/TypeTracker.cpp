// Author: Bob Rubbens - Knights of the Compiler
// Creation date: ma 08-08-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public
#include <boost/algorithm/string.hpp>
#include <cctype>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

// Private
#include "game/TypeTracker.hpp"
#include "main/global.hpp"

TypeTracker::TypeTracker(SDL_Renderer *renderTgt, TTF_Font *renderFont) :
text(renderTgt) {
	text.setFont(renderFont);
	text.setPosition(320, 435);
	text.setAlign(Align::CENTER);
	
	SDL_Color clr;
	clr.r = 255;
	clr.b = 255;
	clr.g = 255;
	clr.a = 255;

	text.setColor(clr);
	text.commit();
}

TypeTracker::~TypeTracker() {
}

void TypeTracker::event(SDL_Event &e) {
	if (frozen) return;

	switch (e.type) {
		case SDL_TEXTINPUT:
			{
				char c = e.text.text[0];
				if (std::isalpha(c)) {
					currStr += c;
				}
				text.setText(currStr);
				text.commit();
				break;
			}
		case SDL_KEYUP:
			switch (e.key.keysym.sym) {
				case SDLK_RETURN:
				case SDLK_DELETE:
					currStr = "";
					text.setText(currStr);
					text.commit();
					break;
				case SDLK_BACKSPACE:
					if (currStr.size() > 0) {
						currStr.pop_back();
						text.setText(currStr);
						text.commit();
					}
					break;
				default:
					// Do nothing
					break;
			}
			break;
		default:
			// Do nothing
			break;
	}
}

std::string TypeTracker::getCurrentString() const {
	return currStr;
}

int TypeTracker::matchString(std::string other) const {
	std::string _currStr = currStr;

	if (other.size() == _currStr.size()) {
		boost::algorithm::to_lower(other);
		boost::algorithm::to_lower(_currStr);

		for (Uint32 i = 0; i < _currStr.size(); i++) {
			if (_currStr[i] != other[i]) {
				return i;
			}
		}
		
		return TYPETRACKER_MATCH;
	}

	return TYPETRACKER_NOMATCH;
}

void TypeTracker::clear() {
	if (frozen) return;

	currStr = "";
	text.setText("");
	text.commit();
}

void TypeTracker::freeze() {
	frozen = true;
}

void TypeTracker::render() const {
	text.render(g_renderer);
}
