#pragma once
#include <string>
#include <SDL.h>
#include <iostream>
#include <vector>
#include "Player.h"

class Window {
public:
	Window(const std::string& title, int width, int height);
	~Window();

	inline bool IsClosed() const { return _closed; }
	void SetBackground();
	bool PollEvents();
	void DrawRect(int height, int width, int xPos, int yPos, bool alive);
	void PresentRenderer();
	void DrawLine(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
	void DrawLine(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int x5, int y5);
	void DrawPlayer();
	void Setplayer(Player* player);
	void RotatePlayer(int direction);

private:
	bool Init();
	std::string _title;
	int _width = 800;
	int _height = 600;
	bool _closed = false;
	SDL_Window* _window = nullptr;
	SDL_Renderer* _renderer = nullptr;
	Player* _player;
	double** _points;
};