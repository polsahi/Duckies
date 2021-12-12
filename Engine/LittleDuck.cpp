#include "LittleDuck.h"
#include "Game.h"
#include "Colors.h"
#include "Duck.h"


LittleDuck::LittleDuck (const int x, const int y, Color color) {
     posx = x;
     posy = y;
     duck_color = color;
     boost = false;
 }


int LittleDuck::Getposx() const {
     return posx;
}

int LittleDuck::Getposy() const {
    return posy;
}

void LittleDuck::Draw(Graphics& gfx) {
    for (int i = -10; i < 10; ++i) {
		for (int j = -10; j < 10; ++j) {
			gfx.PutPixel(posx + i, posy + j, duck_color);
		}
    }
}

void LittleDuck::Followx(const int x) {
    posx += x;
}

void LittleDuck::Followy(const int y) {
    posy += y;
}