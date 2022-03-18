#include <iostream>
#include <bits/stdc++.h>

using namespace std;


class Action{
public:
    /// Вес действия. Чем больше -> тем вероятнее
    long long weight = 1;
    std::function<void(bool)> Action_Function;

    //Action(void (*Action_Function_)(bool isGoodGuy)){
    //    Action_Function = Action_Function_;
    //}
};
