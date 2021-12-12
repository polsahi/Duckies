#include "FoodCounter.h"

int FoodCounter::GetCounter() const {
    return bread_counter;
}

void FoodCounter::AddCount() {
    ++bread_counter;
}

void FoodCounter::ResetCounter() {
    bread_counter = 0;
}