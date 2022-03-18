#include <iostream>
#include <fstream>
using namespace std;

void print_arr(int a[100][100],int n,int m, string meta){
cout << meta << endl;
for(int i = 1;i<n+1;i++){
    for(int j = 1;j < m+1; j++){
        cout << a[j][i] << " ";
    }
    cout << endl;
}
cout << endl;
}

int main()
{
    ifstream fin("input.txt");
    int n,m; //размеры города
    // n - ввысь
    // m - вширину
    int TRAV; // кол-во траволаторов
    int reqs;
    int y1,x1,y2,x2;

    int LEFT_RIGHT = m-1;
    int UP_DOWN = n-1;

    int u[100][100];
    int d[100][100];
    int l[100][100];
    int r[100][100];

    for(int i =0;i<100;i++){
        for(int j = 0;j<100;j++){
            u[i][j] = 0;
            d[i][j] = 0;
            l[i][j] = 0;
            r[i][j] = 0;
        }
    }

    /*

    Up:
    x + 1
    y

    Right:
    x
    y+1

    */

    fin >> n >> m >> TRAV;
    fin >> reqs;
    for(int i=0;i<reqs;i++){
        fin >> y1 >> x1 >> y2 >> x2;

        int VERT = 1;
        int HOR = 1;
        /*
        Up - (-1)
        Down - (1)

        Right - (-1)
        Left - (1)
        */

        if(y1 > y2){VERT = 1;}
        if(y1 < y2){VERT = -1;}
        if(y1 == y2){VERT = 0;}

        if(x1 > x2){HOR = 1;}
        if(x1 < x2){HOR = -1;}
        if(x1 == x2){HOR = 0;}

        int dX = abs(x1 - x2);
        int dY = abs(y1 - y2);
        cout << "DEBUG : " << dX << " " << dY << endl;;
        /* UP-DOWN */
        for(int i = 0; i<dX+1;i++){
            for(int j = 0; j<dY;j++){
                if(VERT == 1){d[min(x1,x2) + i][min(y1,y2) + j]+=1;}
                if(VERT == -1){u[min(x1,x2) + i][min(y1,y2) + j]+=1;}


            }
        }

        for(int i = 0; i<dX;i++){
            for(int j = 0; j<dY+1;j++){
                if(HOR == 1){l[min(x1,x2) + i][min(y1,y2) + j]+=1;}
                if(HOR == -1){r[min(x1,x2) + i][min(y1,y2) + j]+=1;}
            }
        }

         print_arr(u,n,m,"down");
    print_arr(d,n,m,"up");
    print_arr(l,n,m,"left");
    print_arr(r,n,m,"right");
    cout << endl << endl;
        /* UP-DOWN */

    }
         print_arr(u,n,m,"down");
    print_arr(d,n,m,"up");
    print_arr(l,n,m,"left");
    print_arr(r,n,m,"right");

}
