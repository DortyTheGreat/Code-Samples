#include <iostream>
#include "DortyBuild.h"
#include "DotaMath.h"

using namespace std;

template<typename T>
void request(string printer,T &value ){
    cout << printer << endl;
    cin >> value;
}


int main()
{
    AppBuild();
    //cout << GetArmorMult(12);

    double attack_speed;
    request("insert global max_attack_speed",attack_speed);

    double BAT;
    request("insert Basic Attack Time of hero (std = 1.7)",BAT);

    double stack_earning_speed;
    request("insert stack mult (melee = 2, range = 7,drow = 14, medusa = 9)",stack_earning_speed);



    double ATTACKS_PER_SECOND = attack_speed/100/BAT;

    double STACKS_PER_SECOND = ATTACKS_PER_SECOND * stack_earning_speed;

    double RAW_AVERAGE_DAMAGE = ATTACKS_PER_SECOND * STACKS_PER_SECOND * 16;

    cout << "--------------" << endl;
    cout << "STACKS PER SECOND: " << STACKS_PER_SECOND << endl;
    cout << "RAW_AVERAGE_DAMAGE: " << RAW_AVERAGE_DAMAGE << endl;

}
