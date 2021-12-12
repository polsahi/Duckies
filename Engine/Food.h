#pragma once
#include "Graphics.h"
class Food {
public:
	Food(); //appears
	Food(const int x, const int y) {
		posx = x;
		posy = y;
	};
	static int bread_counter;
	void Draw(Graphics& fdx);
	int Getposx() const;
	int Getposy() const;
private:
	int posx, posy;
};