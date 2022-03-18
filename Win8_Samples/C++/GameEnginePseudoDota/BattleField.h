#include "Team.h"
#include <vector>
#include <sstream>
#include <set>


using namespace std;

template <typename T>
  std::string NumberToString ( T Number )
  {
     std::ostringstream ss;
     ss << Number;
     return ss.str();
  }

class TimeMove{
public:
    long long time;
    Character Char;

    int TeamAdvantage;

    bool operator<(const TimeMove& other) const {
    if (time != other.time){
        return (time < other.time);
    }else{
        return (TeamAdvantage < other.TeamAdvantage);
    }
    }

};

class BattleField{
public:
    Team GoodGuysSide;
    Team BadGuysSide;

    void initField(Team GG, Team BG){
        GoodGuysSide = GG;
        BadGuysSide = BG;
    }

    void StartBattle(){

        int GoodGuysChance = 1;
        int BadGuysChance = 1;
        int AllGuysChance = GoodGuysChance + BadGuysChance;
        int FirstTurnAssigment = rand() % AllGuysChance;

        int GGTA;
        int BGTA;
        if (FirstTurnAssigment < GoodGuysChance){
            cout << "GoogGuys Won the coin flip";
            GGTA = 0;
            BGTA = 1;
        }else{
            cout << "Bad Guys Won the coin flip";
            GGTA = 1;
            BGTA = 0;
        }

        cout << " ("+ NumberToString(FirstTurnAssigment + 1) + "\\" + NumberToString(AllGuysChance) + ")" << endl;

        set<TimeMove> ListOfMoves;
        for(int i =0;i<GoodGuysSide.Characters.size();i++){
            TimeMove TM;
            TM.Char = GoodGuysSide.Characters[i];
            TM.time = GoodGuysSide.Characters[i].TurnSpeed;
            TM.TeamAdvantage = GGTA;
            ListOfMoves.insert(TM);
        }

        for(int i =0;i<BadGuysSide.Characters.size();i++){
            TimeMove TM;
            TM.Char = BadGuysSide.Characters[i];
            TM.time = BadGuysSide.Characters[i].TurnSpeed;
            TM.TeamAdvantage = BGTA;
            ListOfMoves.insert(TM);
        }


        ///Debug Only
        for (TimeMove that : ListOfMoves){
            string teamName;
            if (that.TeamAdvantage == GGTA){
                teamName = "Good";
            }else{
                teamName = "Bad";
            }
            cout << that.time << " " <<teamName << " " << that.Char.Name << endl;
        }

        for(int TURNS_LIMIT = 0;TURNS_LIMIT<20;TURNS_LIMIT++){
            TimeMove thatMove = *ListOfMoves.begin();

            string teamName;

            if (thatMove.TeamAdvantage == GGTA){
                teamName = "Good";
            }else{
                teamName = "Bad";
            }

            thatMove.Char.PerformAction(teamName == "Good");

            ListOfMoves.erase(ListOfMoves.begin());
            thatMove.time += thatMove.Char.TurnSpeed;
            ListOfMoves.insert(thatMove);
        }


    }
};
