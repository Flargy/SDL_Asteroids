#include <iostream>
#include "renderer.h"


Window::Window(const std::string& title, int width, int height) :
	_title(title), _width(width), _height(height) {

	_closed = !Init();
}

Window::~Window() {
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

bool Window::Init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		std::cout << SDL_GetError() << std::endl;
		return false;
	}

	_window = SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, SDL_WINDOW_SHOWN);

	if (_window == nullptr) {
		std::cout << SDL_GetError() << std::endl;
		return false;
	}

	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (_renderer == nullptr) {
		std::cout << SDL_GetError() << std::endl;
		return false;
	}

	return true;

}

void Window::SetBackground() {

	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
	SDL_RenderClear(_renderer);


}

void Window::DrawRect(int height, int width, int xPos, int yPos) {

	SDL_Rect rect;
	rect.w = width;
	rect.h = height;
	rect.x = xPos;
	rect.y = yPos;
	
	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(_renderer, &rect);
}

void Window::PresentRenderer() {
	SDL_RenderPresent(_renderer);

}

void Window::DrawLine(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
	SDL_Point points[4] = { {x1,y1}, {x2,y2}, {x3,y3}, {x4,y4} };

	SDL_RenderDrawLines(_renderer, points, 4);
}

void Window::DrawLine(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int x5, int y5) {
	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
	SDL_Point points[5] = { {x1,y1}, {x2,y2}, {x3,y3}, {x4,y4},{x5,y5} };

	SDL_RenderDrawLines(_renderer, points, 5);
}

void Window::DrawLine(int x1, int y1, int x2, int y2){
	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
	SDL_Point points[2] = { {x1,y1}, {x2,y2}};

	SDL_RenderDrawLines(_renderer, points, 2);
}

void Window::DrawLineDynamic(std::vector<std::array<int, 2>> vec) // needs to be tested
{
	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
	int size = vec.size() + 1;
	SDL_Point* const points = new SDL_Point[size];
	for(int i = 0; i < size; i++)
	{
		points[i] = SDL_Point{vec[i][0], vec[i][1]};
	}
	SDL_RenderDrawLines(_renderer, points, size);
	delete points;
}

void Window::DrawPlayer() {

	double x = _player->transform->GetPosition()[0];
	double y = _player->transform->GetPosition()[1];
	//_points = _player->GetPoints();
	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
	SDL_Point lines[4] = { 
		{(*_points)[0][0] + 0.5 + x, (*_points)[0][1] + 0.5 + y},
		{(*_points)[1][0] + 0.5 + x, (*_points)[1][1] + 0.5 + y},
		{(*_points)[2][0] + 0.5 + x, (*_points)[2][1] + 0.5 + y},
		{(*_points)[0][0] + 0.5 + x, (*_points)[0][1] + 0.5 + y} };

	SDL_RenderDrawLines(_renderer, lines, 4);
}

// -------------- Debug Stuff ---------------------

void Window::RenderDebugCube()
{
	double x = debugAsteroid->transform->GetPosition()[0];
	double y = debugAsteroid->transform->GetPosition()[1];

	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
	SDL_Point lines[4] = { 
		{(*_debugPoints)[0][0] + 0.5 + x,(*_debugPoints)[0][1] + 0.5 + y}, 
		{(*_debugPoints)[1][0] + 0.5 + x,(*_debugPoints)[1][1] + 0.5 + y},
		{(*_debugPoints)[2][0] + 0.5 + x,(*_debugPoints)[2][1] + 0.5 + y},
		{(*_debugPoints)[0][0] + 0.5 + x,(*_debugPoints)[0][1] + 0.5 + y} };

	SDL_RenderDrawLines(_renderer, lines, 4);


}
void Window::SetDebugAsteroid(Asteroid* asteroid)
{
	debugAsteroid = asteroid;
	_debugPoints = debugAsteroid->GetPoints();
}


// This will not be needed here later, functionality will be moved to Game.cpp
bool Window::PollEvents() {
	SDL_Event event;

	//std::vector<int> positions;

	SDL_PumpEvents();
	const Uint8* state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_LEFT]) {
		RotatePlayer(3);
	}
	if (state[SDL_SCANCODE_RIGHT]) {
		RotatePlayer(-3);
	}
	if (state[SDL_SCANCODE_UP]) {
		_player->Accelerate();
	}
	if (state[SDL_SCANCODE_SPACE]) // && fire timer < time since last shot
	{
		// shoot
	}


	while (SDL_PollEvent(&event)) {
		switch (event.type)
		{
		case SDL_QUIT:
			_closed = true;
			break;
		default:
			break;
		}
	}


	return false;
}

void Window::RotatePlayer(int direction) {
	_player->Rotate(direction);
}

void Window::Setplayer(Player* player) {
	_player = player;
	_points = _player->GetPoints();
}


