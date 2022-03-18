#include <iostream>
#include <set>

using namespace std;


int Field[10][10][10];

int pseudo_inf = 100000;

class coord{
public:
    int x,y,z;

     bool operator<(const coord& other) const {
        if (x != other.x){
            return (x < other.x);
        }

        if (y != other.y){
            return y < other.y;
        }


        return z < other.z;


    }


};

set<coord> MS;

bool out_of_bound(int var_){
return (var_ < 0 || var_ > 9);
}

void search_(int turn, int x,int y,int z){

    if (out_of_bound(x) || out_of_bound(y) || out_of_bound(z)){return;}

    if (Field[x][y][z] <= turn){return;}

    coord findel;
    findel.x = x; findel.y = y; findel.z = z;

    if (MS.find(findel) != MS.end()){return;}

    Field[x][y][z] = turn;

    search_(turn+1,x,y,z+1);
    search_(turn+1,x,y,z-1);

    search_(turn+1,x,y+1,z);
    search_(turn+1,x,y-1,z);

    search_(turn+1,x+1,y,z);
    search_(turn+1,x-1,y,z);
}

int main()
{
    for(int x = 0;x<10;x++){
        for(int y = 0;y<10;y++){
            for(int z = 0; z < 10;z++){
                Field[x][y][z] = pseudo_inf;
            }
        }
    }

    int sX,sY,sZ;


    cin >> sX >> sY >> sZ;

    sX--;
    sY--;
    sZ--;

    int fX,fY,fZ;

    cin >> fX >> fY >> fZ;

    fX--;
    fY--;
    fZ--;

    int m;
    cin >> m;



    for(int i =0;i<m;i++){
        coord C;
        cin >> C.x >> C.y >> C.z;

        C.x--;
        C.y--;
        C.z--;

        MS.insert(C);
    }

    search_(0,sX,sY,sZ);

    int num = Field[fX][fY][fZ];



    if (num == pseudo_inf){
        cout << "NO";
        return 0;
    }else{
        cout << num;
    }

    return 0;
}
