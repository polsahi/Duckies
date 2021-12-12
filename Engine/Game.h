#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Duck.h"
#include "Food.h"
#include "Boost.h"
#include "FoodCounter.h"
#include "Board.h"
#include "CollisionCooldown.h"
//sprite
// #include "Sprite.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
	bool IsColliding(const Duck&, const Food&);
	bool IsColliding(const Duck&, const Duck&);
	bool IsColliding(const Duck&, const Boost&);
	bool IsColliding(const Duck&, const LittleDuck&);
	void AddRock(const int x, const int y);
	void DrawBox(const int boxx, const int boxy);
	void DrawBush(const int bushx, const int bushy);
	void DrawMap();
	int boost_counter1;
	int boost_counter2;
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	Duck duck1, duck2;
	Food food;
	Boost boost;
	FoodCounter foodcounter;
	CollisionCooldown cdcounter1, cdcounter2;
	Board board;
	//sprite
	//aqui poser el nom de la imatge
	// Sprite sprite;
	/********************************/
	/*  User Variables              */
	/********************************/
};