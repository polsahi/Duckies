#include "MainWindow.h"
#include "Game.h"
#include <vector>
#include <random>

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	duck1(200, 200, Color(Colors::Yellow)),
	duck2(Graphics::ScreenWidth - 210, Graphics::ScreenHeight - 210, Color(Colors::White)),
	food(gfx.ScreenWidth/2, gfx.ScreenHeight/2),
	foodcounter(),
	cdcounter1(),
	cdcounter2()
	//sprite("lake2.bmp")
{
}

void Game::Go()
{

	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	duck1.Stop();
	duck2.Stop();
	if (wnd.kbd.KeyIsPressed(VK_UP)) {
		duck1.vy -= 4 + duck1.GetBoost();
		duck1.nose_dir = 8;
	}
	if (wnd.kbd.KeyIsPressed(VK_DOWN)) {
		duck1.vy += 4 + duck1.GetBoost();
		duck1.nose_dir = 2;
	}
	if (wnd.kbd.KeyIsPressed(VK_LEFT)) {
		duck1.vx -= 4 + duck1.GetBoost();
		duck1.nose_dir = 4;
	}
	if (wnd.kbd.KeyIsPressed(VK_RIGHT)) {
		duck1.vx += 4 + duck1.GetBoost();
		duck1.nose_dir = 6;
	}
	if (wnd.kbd.KeyIsPressed(0x57)) {
		duck2.vy -= 4 + duck2.GetBoost();
		duck2.nose_dir = 8;
	}
	if (wnd.kbd.KeyIsPressed(0x53)) {
		duck2.vy += 4 + duck2.GetBoost();
		duck2.nose_dir = 2;
	}
	if (wnd.kbd.KeyIsPressed(0x41)) {
		duck2.vx -= 4 + duck2.GetBoost();
		duck2.nose_dir = 4;
	}
	if (wnd.kbd.KeyIsPressed(0x44)) {
		duck2.vx += 4 + duck2.GetBoost();
		duck2.nose_dir = 6;
	}
	if (IsColliding(duck1, duck2)) {
		if (duck1.Getposx() - duck2.Getposx() < 0) {
			if (duck1.vx > 0) duck1.vx = 0;
			if (duck2.vx < 0) duck2.vx = 0;
		}
		else {
			if (duck1.vx < 0) duck1.vx = 0;
			if (duck2.vx > 0) duck2.vx = 0;
		}
		if (duck1.Getposy() - duck2.Getposy() < 0) {
			if (duck1.vy > 0) duck1.vy = 0;
			if (duck2.vy < 0) duck2.vy = 0;
		}
		else {
			if (duck1.vy < 0) duck1.vy = 0;
			if (duck2.vy > 0) duck2.vy = 0;
		}
	}
	int duckies = duck1.Duckies();
	for (int i = 0; i < duckies; ++i) {
		if (IsColliding(duck2, duck1.little_ducks[i])) {
			if (duck2.Duckies() != 0 && !cdcounter2.running) {
				duck2.little_ducks.pop_back();
				cdcounter2.running = true;
			}
			if (duck1.little_ducks[i].Getposx() - duck2.Getposx() < 0) {
				if (duck2.vx < 0) duck2.vx = 0;
			}
			else {
				if (duck2.vx > 0) duck2.vx = 0;
			}
			if (duck1.little_ducks[i].Getposy() - duck2.Getposy() < 0) {
				if (duck2.vy < 0) duck2.vy = 0;
			}
			else {
				if (duck2.vy > 0) duck2.vy = 0;
			}
		}
	}
	duckies = duck2.Duckies();
	for (int i = 0; i < duckies; ++i) {
		if (IsColliding(duck1, duck2.little_ducks[i])) {
			if (duck1.Duckies() != 0 && !cdcounter1.running) {
				duck1.little_ducks.pop_back();
				cdcounter1.running = true;
			}
			if (duck2.little_ducks[i].Getposx() - duck1.Getposx() < 0) {
				if (duck1.vx < 0) duck1.vx = 0;
			}
			else {
				if (duck1.vx > 0) duck1.vx = 0;
			}
			if (duck2.little_ducks[i].Getposy() - duck1.Getposy() < 0) {
				if (duck1.vy < 0) duck1.vy = 0;
			}
			else {
				if (duck1.vy > 0) duck1.vy = 0;
			}
		}
	}
	duck2.Move();
	duck1.Move();

	if (IsColliding(duck1, food)) {
		food = Food();
		foodcounter.AddCount();
		board.GetBreadsDuck1(duck1);
		++duck1.bread_count;
	}
	if (IsColliding(duck2, food)) {
		food = Food();
		foodcounter.AddCount();
		board.GetBreadsDuck2(duck2);
		++duck2.bread_count;
	}
	if (IsColliding(duck1, boost) && !boost.used) {
		boost = Boost();
		duck1.boost = true;
		boost_counter1 = 0;
		boost.used = true;
	}
	if (IsColliding(duck2, boost) && !boost.used) {
		boost = Boost();
		duck2.boost = true;
		boost_counter2 = 0;
		boost.used = true;
	}
	if (duck1.boost) ++boost_counter1;
	if (duck2.boost) ++boost_counter2;
	if (foodcounter.GetCounter() == 5) {
		boost = Boost();
		foodcounter.ResetCounter();
	}
	if (boost_counter1 == 300) {
		duck1.boost = false;
		boost_counter1 = 0;
	}
	if (boost_counter2 == 300) {
		duck2.boost = false;
		boost_counter2 = 0;
	}
	if (duck1.Duckies() == 5) {
		duck1.winner = true;
	}
	else if (duck2.Duckies() == 5) {
		duck2.winner = true;
	}

	if (duck1.bread_count == 3) {
		duck1.AddDuck();
		duck1.bread_count = 0;
	}
	else if (duck2.bread_count == 3) {
		duck2.AddDuck();
		duck2.bread_count = 0;
	}
	if (duck1.Duckies() != 0) {
		
		if (abs(duck1.Getposx() - duck1.little_ducks[0].Getposx()) > 60) {
			if (duck1.Getposx() - duck1.little_ducks[0].Getposx() < 0) {
				duck1.little_ducks[0].Followx(-4);
			}
			else {
				duck1.little_ducks[0].Followx(4);
			}
		}
		if (abs(duck1.Getposy() - duck1.little_ducks[0].Getposy()) > 60) {
			if (duck1.Getposy() - duck1.little_ducks[0].Getposy() < 0) {
				duck1.little_ducks[0].Followy(-4);
			}
			else {
				duck1.little_ducks[0].Followy(4);
			}
		}
		int duckies = duck1.Duckies();
		for (int i = 1; i < duckies; ++i) {
			if (abs(duck1.little_ducks[i - 1].Getposx() - duck1.little_ducks[i].Getposx()) > 60) {
				if (duck1.little_ducks[i - 1].Getposx() - duck1.little_ducks[i].Getposx() < 0) {
					duck1.little_ducks[i].Followx(-4);
				}
				else {
					duck1.little_ducks[i].Followx(4);
				}
			}
			if (abs(duck1.little_ducks[i - 1].Getposy() - duck1.little_ducks[i].Getposy()) > 60) {
				if (duck1.little_ducks[i - 1].Getposy() - duck1.little_ducks[i].Getposy() < 0) {
					duck1.little_ducks[i].Followy(-4);
				}
				else {
					duck1.little_ducks[i].Followy(4);
				}
			}
		}
	}
	if (duck2.Duckies() != 0) {

		if (abs(duck2.Getposx() - duck2.little_ducks[0].Getposx()) > 60) {
			if (duck2.Getposx() - duck2.little_ducks[0].Getposx() < 0) {
				duck2.little_ducks[0].Followx(-4);
			}
			else {
				duck2.little_ducks[0].Followx(4);
			}
		}
		if (abs(duck2.Getposy() - duck2.little_ducks[0].Getposy()) > 60) {
			if (duck2.Getposy() - duck2.little_ducks[0].Getposy() < 0) {
				duck2.little_ducks[0].Followy(-4);
			}
			else {
				duck2.little_ducks[0].Followy(4);
			}
		}
		int duckies = duck2.Duckies();
		for (int i = 1; i < duckies; ++i) {
			if (abs(duck2.little_ducks[i - 1].Getposx() - duck2.little_ducks[i].Getposx()) > 60) {
				if (duck2.little_ducks[i - 1].Getposx() - duck2.little_ducks[i].Getposx() < 0) {
					duck2.little_ducks[i].Followx(-4);
				}
				else {
					duck2.little_ducks[i].Followx(4);
				}
			}
			if (abs(duck2.little_ducks[i - 1].Getposy() - duck2.little_ducks[i].Getposy()) > 60) {
				if (duck2.little_ducks[i - 1].Getposy() - duck2.little_ducks[i].Getposy() < 0) {
					duck2.little_ducks[i].Followy(-4);
				}
				else {
					duck2.little_ducks[i].Followy(4);
				}
			}
		}
	}
	if (cdcounter1.running) {
		++cdcounter1.frames;
	}
	if (cdcounter1.frames > 120) {
		cdcounter1.frames = 0;
		cdcounter1.running = false;
	}
	if (cdcounter2.running) {
		++cdcounter2.frames;
	}
	if (cdcounter2.frames > 120) {
		cdcounter2.frames = 0;
		cdcounter2.running = false;
	}
}

void Game::ComposeFrame() {
	if (!duck1.winner && !duck2.winner) {
		DrawMap();
		board.Draw(gfx);
		food.Draw(gfx);
		if (!boost.used) boost.Draw(gfx);
		int duckies = duck1.Duckies();
		for (int i = 0; i < duckies; ++i) {
			duck1.little_ducks[i].Draw(gfx);
		}
		duckies = duck2.Duckies();
		for (int i = 0; i < duckies; ++i) {
			duck2.little_ducks[i].Draw(gfx);
		}
		duck1.Draw(gfx);
		duck2.Draw(gfx);
	}
	else {
		if (duck1.winner) {
			duck1.SetPosx(Graphics::ScreenWidth / 2);
			duck1.SetPosy(Graphics::ScreenHeight / 2);
			duck1.Draw(gfx);
		}
		else {
			duck2.SetPosx(Graphics::ScreenWidth/2);
			duck2.SetPosy(Graphics::ScreenHeight/2);
			duck2.Draw(gfx);
		}
		//aquí la corona Eduardo Tommy
	}

	//sprite
	//gfx.DrawSprite(200 , 200, sprite);

}

bool Game::IsColliding(const Duck& duck, const Food& food) {
	if ((abs(duck.Getposx() - food.Getposx()) < 30) && (abs(duck.Getposy() - food.Getposy()) < 40)) return true;
	return false;
}

bool Game::IsColliding(const Duck& duck1, const Duck& duck2) {
	if ((abs(duck1.Getposx() - duck2.Getposx()) < 40) && (abs(duck1.Getposy() - duck2.Getposy()) < 40)) return true;
	return false;
}

bool Game::IsColliding(const Duck& duck, const Boost& tangerine) {
	if ((abs(duck.Getposx() - tangerine.Getposx()) < 30) && (abs(duck.Getposy() - tangerine.Getposy()) < 40)) return true;
	return false;
}

bool Game::IsColliding(const Duck& duck, const LittleDuck& duckie) {
	if ((abs(duck.Getposx() - duckie.Getposx()) < 30) && (abs(duck.Getposy() - duckie.Getposy()) < 30)) return true;
	return false;
}

void Game::DrawBox(const int boxx, const int boxy) {
	for (int i = -2; i < 3; ++i) {
		for (int j = -2; j < 3; ++j) {
			gfx.PutPixel(boxx + i, boxy + j, Color(0, 77, 0));
		}
	}
}
void Game::DrawBush(const int bushx, const int bushy) {
	for (int i = bushx - 30; i < bushx + 30; ++i) {
		for (int j = bushy - 20; j < bushy + 20; ++j) {
			gfx.PutPixel(i, j, Color(0,102,0));
		}
	}
	for (int i = bushx - 20; i < bushx + 20; ++i) {
		for (int j = bushy - 30; j < bushy + 30; ++j) {
			gfx.PutPixel(i, j, Color(0,102,0));
		}
	}
	for (int i = -2; i < 3; ++i) {

	}
	std::mt19937 mt(40);
	std::uniform_int_distribution<int> distx(-23, 23);
	std::uniform_int_distribution<int> disty(-23, 23);
	for (int i = 0; i < 40; ++i) {
		DrawBox(bushx + distx(mt), bushy + disty(mt));
	}
	/*
	DrawBox(bushx + 2, bushy - 3);
	DrawBox(bushx + 10, bushy - 7);
	DrawBox(bushx + 8, bushy);
	DrawBox(bushx - 4, bushy + 3);
	DrawBox(bushx - 7, bushy - 10);
	DrawBox(bushx + 8, bushy - 15);
	DrawBox(bushx + 17, bushy - 1);
	DrawBox(bushx + 5, bushy + 10);
	DrawBox(bushx - 7, bushy - 10);
	DrawBox(bushx + 8, bushy - 15);
	DrawBox(bushx + 17, bushy - 1);
	DrawBox(bushx + 5, bushy + 10);
	*/
}

void Game::DrawMap() {
	for (int i = 0; i < gfx.ScreenWidth; ++i) {
		for (int j = 0; j < 50; ++j) {
			gfx.PutPixel(i, j, Color(52, 235, 70));
		}
	}
	for (int i = 0; i < 50; ++i) {
		for (int j = 0; j < gfx.ScreenHeight; ++j) {
			gfx.PutPixel(i, j, Color(52, 235, 70));
		}
	}
	for (int i = gfx.ScreenHeight - 50; i < gfx.ScreenHeight; ++i) {
		for (int j = 0; j < gfx.ScreenWidth; ++j) {
			gfx.PutPixel(j, i, Color(52, 235, 70));
		}
	}
	for (int i = gfx.ScreenWidth - 50; i < gfx.ScreenWidth; ++i) {
		for (int j = 0; j < gfx.ScreenHeight; ++j) {
			gfx.PutPixel(i, j, Color(52, 235, 70));
		}
	}
	for (int i = 50; i < gfx.ScreenWidth - 50; ++i) {
		for (int j = 50; j < gfx.ScreenHeight - 50; ++j) {
			gfx.PutPixel(i, j, Color(135, 169, 224));
		}
	}
	for (int i = 50; i < gfx.ScreenWidth-50; ++i) {
		for (int j = 50; j < 70; ++j) {
			gfx.PutPixel(i, j, Color(Colors::LightGray));
		}
	}
	for (int i = 50; i < 70; ++i) {
		for (int j = 50; j < gfx.ScreenHeight - 50; ++j) {
			gfx.PutPixel(i, j, Color(Colors::LightGray));
		}
	}
	for (int i = 50; i < gfx.ScreenWidth - 50; ++i) {
		for (int j = gfx.ScreenHeight - 70; j < gfx.ScreenHeight-50; ++j) {
			gfx.PutPixel(i, j, Color(Colors::LightGray));
		}
	}
	for (int i = gfx.ScreenWidth - 70; i < gfx.ScreenWidth-50; ++i) {
		for (int j = 50; j < gfx.ScreenHeight-50; ++j) {
			gfx.PutPixel(i, j, Color(Colors::LightGray));
		}
	}
	for (int i = 0; i < 6; ++i) {
		DrawBush(100+200*i, 35);
		DrawBush(100 + 200 * i, gfx.ScreenHeight - 35);
	}
}
// Per afegir una pedra al vector de pedres
void Game::AddRock(const int x, const int y) {

}