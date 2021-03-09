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


void Window::DrawObject(CollidableObject& obj) // needs to be tested
{
	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
	int size = obj.GetPoints()->size();
	double x = obj.transform.GetPosition().x;
	double y = obj.transform.GetPosition().y;
	SDL_Point* const drawPoints = new SDL_Point[size + 1];
	array2D<double, 2, 2>& rotation = obj.transform.GetRotation();
	auto pointPositions = obj.GetPoints();
	double rotatedX, rotatedY;
	for(int i = 0; i < size + 1; i++)
	{
		double positionX = (*pointPositions)[i % size].x;
		double positionY = (*pointPositions)[i % size].y;

		rotatedX = (positionX * rotation[0][0] + rotation[1][0] * positionY) + 0.5 + x;
		rotatedY = (positionX * rotation[0][1] + rotation[1][1] * positionY) + 0.5 + y;
		drawPoints[i] = SDL_Point{ (int)rotatedX, (int)rotatedY};
	}

	SDL_RenderDrawLines(_renderer, drawPoints, size + 1);
	delete[] drawPoints;
}

void Window::DrawPlayer() {

	double x = _player->transform.GetPosition().x;
	double y = _player->transform.GetPosition().y;
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









