#include "FunctionalAction.h"

#include <bits/stdc++.h>

BattleField MainField;

Character Baba,Me;

std::function<void(bool)> Convert_to_Void(FunctionalAction TMP,Character self_){
    cout << TMP.weight << endl;
    return [TMP,self_](bool isGoodGuy) {
                TMP.Action_Function(isGoodGuy,self_);

                }; // end of lambda expression
};

void assign_action(Character &char_, FunctionalAction FA ){
    char_.MyAction.Action_Function = Convert_to_Void(FA,char_);
}

void initGameFiles(){

    FunctionalAction Attack(
      [](bool isGoodGuy, Character Caster) {
      /// Call to opposing team, then to mine

        Team * OpposingTeam;

        if (isGoodGuy){
            OpposingTeam = &MainField.BadGuysSide;
            cout << "I am Good!" << endl;
        }else{
            OpposingTeam = &MainField.GoodGuysSide;
        }






        if ((*OpposingTeam).Characters.size() != 0){
            (*OpposingTeam).Characters[0].HP -=  10;

            cout << "first Opponent: " << (*OpposingTeam).Characters[0].Name << ";HP: " << (*OpposingTeam).Characters[0].HP << endl;
        }

        return;
        } // end of lambda expression
    );


    Baba.TurnSpeed = 1000;
    Baba.HP = 1000;
    Baba.Name = "Baba";
    assign_action(Baba,Attack);

    Me.TurnSpeed = 5000;
    Me.HP = 5000;
    Me.Name = "Me";
    assign_action(Me,Attack);


    std::function<void(bool)> function_;

    ///Baba.MyAction.Action_Function = Convert_to_Void(Attack,Baba);
}
