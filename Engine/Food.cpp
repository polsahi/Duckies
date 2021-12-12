#include "Food.h"
#include "Game.h"
#include "Colors.h"
#include <random>

static int bread_counter = 0;

Food::Food() {
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> distx(125, Graphics::ScreenWidth - 125);
	std::uniform_int_distribution<int> disty(125, Graphics::ScreenHeight - 125);

	posx = distx(mt);
	posy = disty(mt);
}

void Food::Draw(Graphics& fdx) {
	for (int i = -12; i < 13; ++i) {
		for (int j = -20; j < 20; ++j) {
			fdx.PutPixel(posx + i, posy + j, Color(255,184,77));
		}
	}
}

int Food::Getposx() const {
	return posx;
}

int Food::Getposy() const {
	return posy;
}