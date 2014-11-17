// Author: Bob Rubbens - Knights of the Compiler
// Creation date: ma 21-07-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// Private
#include <nnb/log/log.hpp>
#include <utils/Text.hpp>

Text::Text(SDL_Renderer *renderTgt) :
	tgt(renderTgt) {
	
}

Text::~Text() {
	if (textTexture != NULL) {
		SDL_DestroyTexture(textTexture);
		textTexture = NULL;
	}
}

void Text::setText(std::string newText) {
	text = newText;
	dirty = true;
}

void Text::setFont(TTF_Font *newFont) {
	font = newFont;
	dirty = true;
}

void Text::setPosition(int newX, int newY) {
	setX(newX);
	setY(newY);
}

void Text::setX(int p) {
	x = p;

	calculateBounds();
}

void Text::setY(int p) {
	y = p;

	calculateBounds();
}

void Text::setAlign(Align newAlign) {
	align = newAlign;
	calculateBounds();
}

void Text::setColor(SDL_Color newClr) {
	clr = newClr;

	dirty = true;
}

void Text::calculateBounds() {
	int w, h;
	if (textTexture == NULL) {
		w = 0;
		h = 0;
	} else {
		SDL_QueryTexture(textTexture, NULL, NULL, &w, &h);
	}
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;

	switch (align) {
		case Align::LEFT:
			// Nothing to do, it's already correctly aligned by default
			break;
		case Align::CENTER:
			dst.x -= dst.w / 2;
			break;
		case Align::RIGHT:
			dst.x -= dst.w;
			break;
		default:
			NNB_LOG << "ERROR! This case should not be triggered at any given time";
			break;
	}
}

void Text::commit() {
	if (text == "") {
		if (textTexture != NULL) {
			SDL_DestroyTexture(textTexture);
			textTexture = NULL;
		}
	} else {
		SDL_Surface *tempText = TTF_RenderText_Blended(font, text.c_str(), clr);
		if (tempText == NULL) {
			NNB_LOG << "ERROR! Text generation of \"" << text << "\" failed. The error message: " << TTF_GetError();
		}
		SDL_DestroyTexture(textTexture);
		textTexture = SDL_CreateTextureFromSurface(tgt, tempText);
		SDL_FreeSurface(tempText);

		calculateBounds();
	}

	dirty = false;
}

void Text::render(SDL_Renderer* renderTgt) const {
	if (dirty)
		NNB_LOG << "WARNING! Dirty render";

	if (renderTgt != tgt) {
		NNB_LOG << "WARNING! Rendertarget is not the same as creation target";
	}

	SDL_RenderCopy(tgt, textTexture, NULL, &dst);
}

int Text::getWidth() const {
	if (textTexture) {
		int w, h;
		SDL_QueryTexture(textTexture, NULL, NULL, &w, &h);
		return w;
	} else {
		return 0;
	}

}

int Text::getHeight() const {
	if (textTexture) {
		int w, h;
		SDL_QueryTexture(textTexture, NULL, NULL, &w, &h);
		return h;
	} else {
		return 0;
	}
}

int Text::getX() const {
	return x;
}

int Text::getY() const {
	return y;
}
