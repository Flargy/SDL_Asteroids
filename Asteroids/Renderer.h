#pragma once
#include <string>
#include <SDL.h>
#include <iostream>
#include <vector>
#include "Player.h"
#include <vector>
#include <array>
#include "Asteroid.h"
#include "SDL_ttf.h"

class Font;

class Window {
public:
	Window(const std::string& title, int width, int height);
	~Window();

	inline bool IsClosed() const { return _closed; }
	void SetBackground();
	void DrawRect(int height, int width, int xPos, int yPos);
	void PresentRenderer();
	void DrawObject(CollidableObject& obj);
	void DrawText(std::string text, int xPos, int yPos);

	SDL_Renderer* _renderer = nullptr;

private:
	bool Init();
	std::string _title;
	int _width = 800;
	int _height = 600;
	bool _closed = false;
	SDL_Window* _window = nullptr;
	SDL_Rect messageDest;
	SDL_Rect messageSrc;
	std::shared_ptr<Font> font;
	SDL_Color textColor = { 255,255,255 };

};