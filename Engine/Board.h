#pragma once
#include "Duck.h"

class Board {
public:
    Board() {

    };
    void Draw(Graphics& gfx);
    void GetBreadsDuck1(const Duck&);
    void GetBreadsDuck2(const Duck&);
private:
    int duck1_breads;
    int duck2_breads;
};