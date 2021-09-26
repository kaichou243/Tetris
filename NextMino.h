#pragma once
#include "Mino.h"

class NextMino : public Mino {
public:
	int first, second, third;
	NextMino(){}
	NextMino(int first, int second, int third) :first(first), second(second), third(third) {
	}
	void DrawMino(const Font& font);
};