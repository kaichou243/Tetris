#include "Siv3D.hpp"
#include "Player.h"

Vec2 Player::InputKey() {
	int dx = 0, dy = 0;
	if (KeyRight.down())dx = 1;
	else if (KeyLeft.down())dx = -1;
	else if (KeyDown.down()) dy = 1;
	return Vec2(dx, dy);
}



