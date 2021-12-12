#pragma once
#include "Graphics.h"
#include "LittleDuck.h"
#include "FoodCounter.h"
#include <vector>
class Duck {
public:
	Duck(const int x, const int y, Color color);
	void Move();
	void Stop();
	int Getposx() const; 
	int Getposy() const;
	int GetBoost() const;
	void SetPosy(const int x);
	void SetPosx(const int y);
	void AddDuck();
	void Draw(Graphics& gfx);
	int Duckies() const;
	int nose_dir, vx, vy;
	bool boost;
	Color duck_color;
	bool winner;
	int bread_count;
	std::vector<LittleDuck> little_ducks;
private:
	int posx, posy; // numpad directions
	
};