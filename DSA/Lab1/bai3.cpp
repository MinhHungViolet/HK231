#include <cstdlib>

class Character {
protected:
    int hp;
    int x;
    int y;

public:
    // Constructor: set the values of x and y and hp to 0
    Character() {
        hp = 0;
        x = 0;
        y = 0;
    }

    // Constructor: set the values of hp, x and y to each parameter
    Character(int hp, int x, int y) {
        this->hp = hp;
        this->x = x;
        this->y = y;
    }

    // Set and get hp
    int getHp() {
        return hp;
    }

    void setHp(int hp) {
        this->hp = hp;
    }

    // Set and get x
    int getX() {
        return x;
    }

    void setX(int x) {
        this->x = x;
    }

    // Set and get y
    int getY() {
        return y;
    }

    void setY(int y) {
        this->y = y;
    }

    // Get Manhattan distance to other character
    int getManhattanDistTo(Character* other) {
        int dx = abs(x - other->getX());
        int dy = abs(y - other->getY());
        return dx + dy;
    }
};