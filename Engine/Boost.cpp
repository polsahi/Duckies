#include "Boost.h"
#include "Game.h" 
#include "Colors.h"
#include <random>

Boost::Boost() {
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> distx(125, Graphics::ScreenWidth - 125);
	std::uniform_int_distribution<int> disty(125, Graphics::ScreenHeight - 125);
	used = false;
	posx = distx(mt);
	posy = disty(mt);
}

void Boost::Draw(Graphics& gfx) {
	for (int i = -10; i < 10; ++i) {
		for (int j = -10; j < 10; ++j) {
			gfx.PutPixel(posx + i, posy + j, Color(255, 175, 39));
		}
	}

}

int Boost::Getposx() const {
	return posx;
}

int Boost::Getposy() const {
	return posy;
}