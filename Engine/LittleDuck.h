#pragma once
#include "Graphics.h"

class LittleDuck {
public:
    LittleDuck(const int x, const int y, Color color);
    void Followx(const int x);
    void Followy(const int y);
    int Getposx() const;
	int Getposy() const;
    void Draw(Graphics& gfx);
	bool boost;
	Color duck_color;
private:
    int posx, posy;
};