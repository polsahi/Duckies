#pragma once
#include "Graphics.h"

class Boost {
public:
	Boost();
	void Draw(Graphics& gfx);
	int Getposx() const;
	int Getposy() const;
	bool used;
private:
	int posx, posy;
};