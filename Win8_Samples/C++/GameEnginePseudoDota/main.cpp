#include <iostream>
#include <ctime>

#include "GameHeader.h"

using namespace std;

int main()
{
    initGameFiles();



    Team T1,T2;

    T1.AddChar(Me);
    T2.AddChar(Baba);



    MainField.initField(T1,T2);

    srand(time(NULL));

    MainField.StartBattle();


}
