#pragma once

class FoodCounter {
public:
    FoodCounter() {
        bread_counter = 0;
    }
    int GetCounter() const;
    void AddCount();
    void ResetCounter();
private:
    int bread_counter;
};