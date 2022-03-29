#include <iostream>
#include <vector>
using namespace std;

class FootSoldier {
protected:
    int speed;
    int damage;
    int armor;
    int distance;
    FootSoldier(int s, int d, int a, int di) : speed(s), damage(d), armor(a), distance(di) {};
public:
    FootSoldier() : speed(2), damage(1), armor(0), distance(0) {};
    void info() {
        cout << "Speed:    " << speed    << endl
             << "Damage:   " << damage   << endl
             << "Armor:    " << armor    << endl
             << "Distance: " << distance << endl
             << endl;
    }
};
