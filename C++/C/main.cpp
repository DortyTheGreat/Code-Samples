#include <iostream>
#include <vector>
using namespace std;

vector<int> deck;

void shuffle(){
    vector<int> nw;
    nw.resize(64);

    for(int i = 0;i<64;i++){
        nw[i] = deck[32 * (i%2) + i/2];
    }
    deck = nw;

    for(int i = 0;i < 64; i++){
        cout << deck[i] << " ";
    }
    cout << endl;
}


int main()
{



    deck.resize(64);

    for(int i = 0;i<64;i++){
        deck[i] = i + 1;
    }

    shuffle();
    shuffle();
    shuffle();
    shuffle();
    shuffle();
    shuffle();

    cout << "Hello world!" << endl;
    return 0;
}
