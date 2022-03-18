#include <iostream>
#include "add.h"
#include <fstream>
using namespace std;

int main()
{
    ofstream a("custom.txt");
    a <<"HUI233";
    cout << add(3,4);
}
