#include "Character.h"
#include <vector>

using namespace std;

class Team{
public:
    std::vector<Character> Characters;

    void AddChar(Character char_){
        Characters.push_back(char_);
    }

};
