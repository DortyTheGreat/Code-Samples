#include <iostream>
#include <iostream>
#include <cmath>

double GetArmorMult(int armor){
/// Даёт множитель урона в зависимости от брони
double b = 1; // База Брони
double f = 0.06; // Фактор брони
return 1 - (f * armor) / (b + f * abs(armor));

}

#include <iostream>

using namespace std;

template<typename T>
void request(string printer,T &value ){
    cout << printer << endl;
    cin >> value;
}


int main()
{
     
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

