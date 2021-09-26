#include "Siv3D.hpp"
#include "CurrentMino.h"

int dx[] = { 0,-1,1,-2,2 };
int dy[] = { 0,1,2,3 };

void CurrentMino::DrawMino() {
	for (int i = 0; i < Mino::minoSize[minoNumber]; ++i) {
		for (int j = 0; j < Mino::minoSize[minoNumber]; ++j) {
			if (Mino::mino[minoNumber][i][j] == 1)Rect(pos.x * 20 + j * 20, pos.y * 20 + i * 20, 20, 20).draw(color[colorNumber]);
		}
	}
}

void CurrentMino::MoveMino(short field[100][100]) {
	Vec2 nextPos = pos;
	if (KeyRight.down()&&nextPos.x < 11) {
		nextPos.x++;
		pushRight.start();
	}
	else if (KeyLeft.down()&&nextPos.x >= -1) {
		nextPos.x--;
		pushLeft.start();
	}
	else if (KeyDown.down()&&nextPos.y < 20) {
		nextPos.y++;
		pushDown.start();
	}
	if (KeyRight.down()&&pushRight.ms() >= 400) nextPos.x++;
	if (KeyLeft.down()&&pushLeft.ms() >= 400) nextPos.x--;
	if (KeyDown.pressed()&&pushDown.ms() >= 400) nextPos.y++;
	if (KeyRight.up())pushRight.reset();
	if (KeyLeft.up())pushLeft.reset();
	if (KeyDown.up())pushDown.reset();
	if (IsConflict(nextPos, field))return;
	pos = nextPos;
}

void CurrentMino::FreeFall(short field[100][100]) {
	pos.y++;
}

void CurrentMino::ForceFall(short field[100][100]) {
	while (!IsConflict(Vec2(pos.x, pos.y + 1), field)) {
		FreeFall(field);
	}
}

void CurrentMino::RightRotateMino(short field[100][100]) {
	int minoSize = Mino::minoSize[minoNumber];
	short rotatedMino[4][4];
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			rotatedMino[i][j] = Mino::mino[minoNumber][i][j];
		}
	}
	for (int i = 0; i < minoSize; ++i) {
		for (int j = 0; j < minoSize; ++j) {
			Mino::mino[minoNumber][i][j] = rotatedMino[minoSize - 1 - j][i];
		}
	}
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 4; ++j) {
			Vec2 justPos = Vec2(pos.x + dx[i], pos.y + dy[j]);
			if (!IsConflict(justPos, field)) {
				pos = justPos;
				return;
			}
		}
	}
	if (IsConflict(pos, field)) {
		if(IsConflict(pos,field)){
			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 4; ++j) {
					Mino::mino[minoNumber][i][j] = rotatedMino[i][j];
				}
			}
		}
	}
}

void CurrentMino::LeftRotateMino(short field[100][100]) {
	int minoSize =  Mino::minoSize[minoNumber];
	short rotatedMino[4][4];
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			rotatedMino[i][j] = Mino::mino[minoNumber][i][j];
		}
	}
	for (int i = 0; i < minoSize; ++i) {
		for (int j = 0; j < minoSize; ++j) {
			Mino::mino[minoNumber][i][j] = rotatedMino[j][minoSize - 1 - i];
		}
	}
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 4; ++j) {
			Vec2 justPos = Vec2(pos.x + dx[i], pos.y + dy[j]);
			if (!IsConflict(justPos, field)) {
				pos = justPos;
				return;
			}
		}
	}
	if(IsConflict(pos,field)) {
		if (IsConflict(pos, field)) {
			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 4; ++j) {
					Mino::mino[minoNumber][i][j] = rotatedMino[i][j];
				}
			}
		}
	}
}

bool CurrentMino::GameOver() {
	for (int y = 0; y < 4; ++y) {
		for (int x = 0; x < 4; ++x) {
			if (y + pos.y < 2 && Mino::mino[minoNumber][y][x] == 1)return true;
		}
	}
	return false;
}


bool CurrentMino::IsConflict(Vec2 nextPos, short field[100][100]) {
	for (int y = 0; y < 4; ++y) {
		for (int x = 0; x < 4; ++x) {
			if (field[y + (int)nextPos.y][x + (int)nextPos.x] == 1 && Mino::mino[minoNumber][y][x] == 1) {
				return true;
			}
			if (y + nextPos.y >= 20 && Mino::mino[minoNumber][y][x] == 1)return true;
			if (x + nextPos.x < 0 && Mino::mino[minoNumber][y][x] == 1)return true;
			if (x + nextPos.x > 11 && Mino::mino[minoNumber][y][x] == 1)return true;
		}
	}
	return false;
}

bool CurrentMino::IsStop(short field[100][100]) {
	if (IsConflict(Vec2(pos.x, pos.y + 1), field))return true;
	return false;
}

