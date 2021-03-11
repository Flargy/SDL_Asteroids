#pragma once
#include <string>
#include <SDL.h>
#include <iostream>
#include <vector>
#include "Player.h"
#include <vector>
#include <array>
#include "Asteroid.h"

class Window {
public:
	Window(const std::string& title, int width, int height);
	~Window();

	inline bool IsClosed() const { return _closed; }
	void SetBackground();
	void DrawRect(int height, int width, int xPos, int yPos);
	void PresentRenderer();
	void DrawObject(CollidableObject& obj);
	void DrawPlayer();

	SDL_Renderer* _renderer = nullptr;

private:
	bool Init();
	std::string _title;
	int _width = 800;
	int _height = 600;
	bool _closed = false;
	SDL_Window* _window = nullptr;
	

};