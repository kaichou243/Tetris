#pragma once
#include "Siv3D.hpp"
#include "Mino.h"

class CurrentMino : public Mino{
public:
	Vec2 pos;
	int holdMinoNumber;
	bool isUsedHold;
	Stopwatch pushRight, pushLeft, pushDown;
	CurrentMino(){}
	CurrentMino(int minoNumber) {
		Mino::minoNumber = minoNumber;
	}
	CurrentMino(int minoNumber, Vec2 pos) {
		Mino::minoNumber = minoNumber;
		Mino::colorNumber = minoNumber;
		this->pos = pos;
	}
	CurrentMino(int minoNumber, Vec2 pos,int holdMinoNumber,bool isUsedHold) {
		Mino::minoNumber = minoNumber;
		Mino::colorNumber = minoNumber;
		this->pos = pos;
		this->holdMinoNumber = holdMinoNumber;
		this->isUsedHold = isUsedHold;
	}
	void DrawMino();
	void MoveMino(short field[100][100]);
	void ForceFall(short field[100][100]);
	void FreeFall(short field[100][100]);
	void RightRotateMino(short field[100][100]);
	void LeftRotateMino(short field[100][100]);
	bool GameOver();
	bool IsConflict(Vec2 nextPos, short field[100][100]);
	bool IsStop(short field[100][100]);
};
