#include "Duck.h"
#include "Game.h"
#include "Colors.h"

Duck::Duck(const int x, const int y, Color color) {
	posx = x;
	posy = y;
	duck_color = color;
	vx = 0;
	vy = 0;
	if (x < 400) {
		nose_dir = 6;
	} 
	else {
		nose_dir = 4;
	}
	boost = false;
	bread_count = 0;
	winner = false;
}

void Duck::Move() {
	posx += vx;
	posy += vy;	
	if (posx < 95) {
		posx = 95;
	}
	else if (posx > Graphics::ScreenWidth - 95) {
		posx = Graphics::ScreenWidth - 95;
	}
	if (posy < 95) {
		posy = 95;
	}
	else if (posy > Graphics::ScreenHeight - 95) {
		posy = Graphics::ScreenHeight - 95;
	}
}

void Duck::Stop() {
	vx = 0;
	vy = 0;
}

int Duck::Getposx() const {
	return posx;
}

int Duck::Getposy() const {
	return posy;
}

int Duck::GetBoost() const {
	if (boost) return 1;
	return 0;
}

void Duck::AddDuck() {
	LittleDuck duck = LittleDuck(posx, posy, duck_color);
	little_ducks.push_back(duck);
}

void Duck::Draw(Graphics& gfx) {
	for (int i = -20; i < 20; ++i) {
		for (int j = -20; j < 20; ++j) {
			gfx.PutPixel(posx + i, posy + j, duck_color);
		}
	}
	if (nose_dir == 6) {
		for (int i = 0; i < 40; ++i) {
			for (int j = i; j < 40 - i; ++j) {
				gfx.PutPixel(posx + 20 + i, posy -20 + j, Color(Colors::Red));
			}
		}
	}
	else if (nose_dir == 4) {
		for (int i = 0; i < 40; ++i) {
			for (int j = 39-i; j >= i; --j) {
				gfx.PutPixel(posx -20 -i, posy -20 +j, Color(Colors::Red));
			}
		}
	}
	else if (nose_dir == 8) {
		for (int i = 0; i < 40; ++i) {
			for (int j = i; j < 40 - i; ++j) {
				gfx.PutPixel(posx -20 + j, posy -20 - i, Color(Colors::Red));
			}
		}
	}
	else if (nose_dir == 2) {
		for (int i = 0; i < 40; ++i) {
			for (int j = i; j < 40 - i; ++j) {
				gfx.PutPixel(posx - j + 20, posy + i + 20, Color(Colors::Red));
			}
		}
	}
}

void Duck::SetPosx(const int x) {
	posx = x;
}

void Duck::SetPosy(const int y) {
	posy = y;
}

int Duck::Duckies() const {
	return little_ducks.size();
}

