#pragma once
#include "Siv3D.hpp"

class Mino {
public:
	Color color[8] = { Palette::Purple,Palette::Aqua,Palette::Blue,Palette::Orange,Palette::Red,Palette::Green,Palette::Yellow };
	int colorNumber;
	int minoNumber;
	short minoSize[7] = { 3,3,3,3,3,4,2 };
	short mino[7][4][4] = {
		{
			{ 0,1,0,0 },
			{ 1,1,1,0 },
			{ 0,0,0,0 },
			{ 0,0,0,0 }
		},
		{
			{ 1,0,0,0 },
			{ 1,1,1,0 },
			{ 0,0,0,0 },
			{ 0,0,0,0 }
		},
		{
			{ 0,0,1,0 },
			{ 1,1,1,0 },
			{ 0,0,0,0 },
			{ 0,0,0,0 }
		},
		{
			{ 1,1,0,0 },
			{ 0,1,1,0 },
			{ 0,0,0,0 },
			{ 0,0,0,0 }
		},
		{
			{ 0,1,1,0 },
			{ 1,1,0,0 },
			{ 0,0,0,0 },
			{ 0,0,0,0 }
		},
		{
			{ 0,0,0,0 },
			{ 0,0,0,0 },
			{ 1,1,1,1 },
			{ 0,0,0,0 }
		},
		{
			{ 1,1,0,0 },
			{ 1,1,0,0 },
			{ 0,0,0,0 },
			{ 0,0,0,0 }
		}
	};

	virtual void DrowMino();
};
