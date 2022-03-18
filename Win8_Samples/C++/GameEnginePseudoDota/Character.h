#include <iostream>
#include "Action.h"

using namespace std;

class Character{
public:
    std::string Name = "Template";
    double HP = 100;
    long long TurnSpeed = 10000;

    Action MyAction;

    void PerformAction(bool isGoodGuy){

        /// 1 - Good, 2 - Bad

        MyAction.Action_Function(isGoodGuy);

        ///cout << Name << ": Just Permormed a temporary action! Shvazi!" << endl;
    }

};
