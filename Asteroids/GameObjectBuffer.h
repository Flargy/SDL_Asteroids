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
	GameObjectBuffer() 
	{
	}

	

	int decrease_active_size() {
		if (activeSize > 0)
			return --activeSize;
	}

	int increase_active_size() {
		if (activeSize < SIZE)
			return ++activeSize;
	}

	

	int active_size() {
		return activeSize;
	}

	void reset() {
		activeSize = 0;
	}

	TObject& get_last() {
		return buffer[activeSize-1];
	}

	void push_back(TObject& obj) {
		increase_active_size();
		get_last() = obj;
	}

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
	void for_each(TLambda f)
	{
		std::for_each(buffer.begin(),buffer.end(), f);
	}

};

