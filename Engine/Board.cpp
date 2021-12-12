#include "Board.h"

void Board::Draw(Graphics & gfx) {
    
}

void Board::GetBreadsDuck1(const Duck& duck) {
    duck1_breads = duck.bread_count;
}

void Board::GetBreadsDuck2(const Duck& duck) {
    duck2_breads = duck.bread_count;
}