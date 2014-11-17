// Author: Bob Rubbens - Knights of the Compiler
// Creation date: ma 21-07-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef TEXT_HPP
#define TEXT_HPP

// Public
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

// Private

enum class Align {
	LEFT,
	CENTER,
	RIGHT
} ;

class Text {
public:
	Text(SDL_Renderer* tgt);
	~Text();

	void setText(std::string newText);
	void setFont(TTF_Font *newFont);
	void setPosition(int newX, int newY);
	void setX(int p);
	void setY(int p);
	void setAlign(Align newAlign);
	void setColor(SDL_Color newClr);
	void calculateBounds();
	void commit();

	void render(SDL_Renderer *renderTgt) const;

	int getWidth() const;
	int getHeight() const;
	int getX() const;
	int getY() const;
private:
	int x = 0, y = 0;
	TTF_Font *font = NULL;
	std::string text = "";
	Align align = Align::LEFT;
	SDL_Texture *textTexture = NULL;
	SDL_Renderer *tgt = NULL;
	SDL_Rect dst;
	SDL_Color clr;
	bool dirty = true;
} ;

#endif
