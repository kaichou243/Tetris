#pragma once
#include "Siv3D.hpp"
#include "Mino.h"
#include "CurrentMino.h"

class Field {
public:
	int score;
	short field[100][100];
	Color fieldColor[100][100];
	const int W = 100;
	const int H = 100;
	Field(){}
	Field(short field[100][100]) {
		score = 0;
		for (int y = 0; y < H; ++y)
			for (int x = 0; x < W; ++x)this->field[y][x] = field[y][x];
	}
	void DrawField();
	void VanishColumn();
	void ConstructField(Vec2 pos, CurrentMino mino);
private :
	void DownColumn(int column);
};
