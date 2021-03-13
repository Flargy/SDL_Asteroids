#pragma once
#include <SDL_ttf.h>
#include <string>

class Font
{
public:
	Font(std::string path, int fontSize)
	{
		font = TTF_OpenFont(path.c_str(), fontSize);
	}
	~Font()
	{
		TTF_CloseFont(font);
	}

	TTF_Font* GetFont()
	{
		return font;
	}
	

private:
	TTF_Font* font;
};