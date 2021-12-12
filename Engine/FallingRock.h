#pragma once
class FallingRock {
public:
	FallingRock(const int x, const int y) {
		posx = x;
		posy = y;
		state = 0;
		frames = 0;
	};
	int Getposx() const;
	int Getposy() const;
	int frames;
private:
	int posx, posy, state;
};