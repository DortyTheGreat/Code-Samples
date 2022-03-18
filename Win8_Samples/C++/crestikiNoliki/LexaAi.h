#include <utility>

using namespace std;

const string LexaAiName = "TotallyRandomGosunov";

pair<int, int> LexaAi(string field, int W){

    pair<int,int> temp;
    temp.first = rand() % W;
    temp.second = rand() % W;
    return temp;
}
