#pragma once
#include <array>
#include <stdexcept>
#include <algorithm>

template <typename TObject, int SIZE>
class GameObjectBuffer
{
	int activeSize = 0;
	std::array<TObject, SIZE> buffer;

public:
	GameObjectBuffer();

	~GameObjectBuffer();

	int decrease_active_size();

	int increase_active_size();

	int active_size();

	void reset();

	TObject& get_last();

	void push_back(TObject& obj);

	TObject& operator [](int i) {
		if (i >= activeSize || i < 0)
		{
			throw std::out_of_range("out of range");
		}
		else {
			return buffer[i];
		}
	}

	template <typename TLambda>
	void for_each(TLambda f);

};

template<typename TObject, int SIZE>
GameObjectBuffer<TObject, SIZE>::GameObjectBuffer()
{
}

template<typename TObject, int SIZE>
GameObjectBuffer<TObject, SIZE>::~GameObjectBuffer() {}

template<typename TObject, int SIZE>
int GameObjectBuffer<TObject, SIZE>::decrease_active_size()
{
	if (activeSize > 0)
		return --activeSize;
}

template<typename TObject, int SIZE>
int GameObjectBuffer<TObject, SIZE>::increase_active_size()
{
	if (activeSize < SIZE)
		return ++activeSize;
}

template<typename TObject, int SIZE>
int GameObjectBuffer<TObject, SIZE>::active_size()
{
	return activeSize;
}

template<typename TObject, int SIZE>
void GameObjectBuffer<TObject, SIZE>::reset()
{
	activeSize = 0;
}

template<typename TObject, int SIZE>
TObject& GameObjectBuffer<TObject, SIZE>::get_last()
{
	return buffer[activeSize - 1];
}

template<typename TObject, int SIZE>
void GameObjectBuffer<TObject, SIZE>::push_back(TObject& obj)
{
	increase_active_size();
	get_last() = obj;
}

template<typename TObject, int SIZE>
template<typename TLambda>
void GameObjectBuffer<TObject, SIZE>::for_each(TLambda f)
{
	std::for_each(buffer.begin(), buffer.end(), f);
}
