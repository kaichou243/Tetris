#pragma once
#include "Siv3D.hpp"
#include "CurrentMino.h"

class Player {
public:
	Vec2 InputKey();
	void InputX(CurrentMino currentMino,short field[30][12]);
};