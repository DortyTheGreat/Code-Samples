#include <iostream>

using namespace std;
int Field[20][20];




/// x2 >= x1, y2 >= y1;;
int perebor(int x1, int y1, int x2, int y2, int k){

    int summ_ = 0;

    int fail = -10;
    int elem = (x2 - x1 + 1) * (y2 - y1 + 1);

    for(int x = x1;x<= x2;x++){
        for(int y = y1; y<= y2; y++){

            if (x != x1){
                if (Field[x-1][y] > Field[x][y]){
                    return fail;
                }
            }

            if (y != y1){
                if (Field[x][y-1] > Field[x][y]){
                    return fail;
                }
            }

            summ_ += Field[x][y];
        }
    }

    int nK = k * elem;

    if (summ_ > nK){
       return elem;
    }else{
        return fail;
    }



}

int main()
{
    int n,m,k;
    cin >> n >> m;
    cin >> k;
    for(int i =0;i<n;i++){
        for(int j =0;j<m;j++){
            cin >> Field[i][j];
        }
    }

    int secret_num = -5;

    int maxI_ = secret_num;

    int a1,a2,a3,a4;

    for(int x1 =0;x1<n;x1++){
        for(int y1 =0;y1<m;y1++){
            for(int x2 =x1;x2<n;x2++){
                for(int y2 =y1;y2<m;y2++){
                    int temp = perebor(x1,y1,x2,y2,k);
                    if (temp > maxI_){
                        maxI_ = temp;
                        a1 = x1;
                        a2 = y1;
                        a3 = x2;
                        a4 = y2;
                    }
                }
            }
        }
    }


    //cout << maxI_ << endl;
    if (maxI_ != secret_num){

    cout << a1+1 << " " << a2+1 << " " << a3+1 << " " << a4+1;
    }else{
    cout << "NO";
    }
    return 0;
}
