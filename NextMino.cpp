#include "Siv3D.hpp"
#include "NextMino.h"

void NextMino::DrawMino(const Font& font) {
	font(U"Now").draw(300, 10);
	for(int i = 0;i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if(Mino::mino[first][i][j] == 1) {
				Rect(300 + j * 20, 50 + i * 20, 20, 20).draw(Color(64, 64, 255));
			}
		}
	}
	font(U"Next").draw(300, 120);
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (Mino::mino[second][i][j] == 1) {
				Rect(300 + j * 20, 180 + i * 20, 20, 20).draw(Color(64, 64, 255));
			}
		}
	}

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (Mino::mino[third][i][j] == 1) {
				Rect(300 + j * 20, 250 + i * 20, 20, 20).draw(Color(64, 64, 255));
			}
		}
	}
}


