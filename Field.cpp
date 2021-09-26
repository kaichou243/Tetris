#include "Siv3D.hpp"
#include "Field.h"
#include "CurrentMino.h"

void Field::DrawField() {
	for (int i = 0; i < 100; ++i) {
		for (int j = 0; j < 100; ++j) {
			if(field[i][j] == 1) {
				Rect(j * 20, i * 20, 20, 20).draw(fieldColor[i][j]);
			}
		}
	}
	for (int i = 0; i < 20; ++i) {

		Line(0, 20 * i, 400, 20 * i).draw(Palette::Gray);
	}
	for (int i = 0; i < 12; ++i) {
		Line(20 * i, 0, 20 * i, 400).draw(Palette::Gray);
	}
	Rect(0, 0, 240, 20).draw(Palette::Gray);
	Rect(240, 0, 600, 600).draw(Palette::Gray);
	Rect(0, 400, 600, 600).draw(Palette::Gray);
}

void Field::VanishColumn() {
	for (int y = 0; y < 30; ++y) {
		bool isVanish = true;
		for(int x = 0;x < 12; ++x) {
			if(field[y][x] != 0) continue;
			isVanish = false;
		}
		if (isVanish) {
			DownColumn(y);
			score+=100;
		}
	}
}

void Field::ConstructField(Vec2 pos, CurrentMino mino) {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (mino.mino[mino.minoNumber][i][j] == 1) {
				field[(int)pos.y + i][(int)pos.x + j] = 1;
				fieldColor[(int)pos.y + i][(int)pos.x + j] = mino.color[mino.colorNumber];
			}
		}
	}
}


void Field::DownColumn(int column) {
	for (int y = column; y > 0; --y) {
		for (int x = 0; x < W; ++x) {
			field[y][x] = field[y - 1][x];
			fieldColor[y][x] = fieldColor[y - 1][x];
		}
	}
}

