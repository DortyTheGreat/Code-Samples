#include <iostream>
#include <vector>
using namespace std;

void drow_field(sizex, sizey);
int main()
{
    void drow_field(10, 10)
    return 0;
}



void drow_field(sizex, sizey) {
    vector <vector <char>> field(sizex);
    vector <char> y(sizey);
    for(int i = 0; i < sizex; i++) field.push_back(y);

    for(int i = 0; i < sizex; i++){
        for(int j = 0; j < sizey; j++) cout << "#";
        cout<<endl;
    }


}
