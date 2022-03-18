#include <iostream>
#include "BattleField.h"

using namespace std;


class FunctionalAction{
public:
    /// Вес действия. Чем больше -> тем вероятнее
    long long weight = 1;
    void (*Action_Function)(bool isGoodGuy, Character Caster);

    FunctionalAction(void (*Action_Function_)(bool isGoodGuy, Character Caster)){
        Action_Function = Action_Function_;
    }
};

