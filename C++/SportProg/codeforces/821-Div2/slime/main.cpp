#include <iostream>

using namespace std;

int main()
{
    bool Board[120][120];
    bool new_Board[120][120];
    bool rot[120][120];
    for(int i = 0;i<120;++i){
        for(int j = 0;j<120;++j){
            Board[i][j] = 0;
            rot[i][j] = 0; /// 0 - вправо, 1 влево
        }
    }

    Board[0][0] = 1;


    for(long long t = 0; t < 1000; ++t){
        if (t % 100 == 0){
            cout << "t = " << t << endl;

            for(int i = 0;i<120;++i){
                for(int j = 0;j<120;++j){
                    cout << Board[i][j];
                }
                cout << endl;
            }
            cout << endl;
        }

        for(int i = 0;i<120;++i){
            for(int j = 0;j<120;++j){
                new_Board[i][j] = 0;
            }
        }


        for(int i = 0;i<120;++i){
            for(int j = 0;j<120;++j){
                if (Board[i][j]){

                    int n_i = i,n_j = j;
                    if (rot[i][j] == 0){
                        n_j+= 1;
                    }else{
                        n_i += 1;
                    }

                    rot[i][j] ^= 1;
                    if (n_i < 120 && n_j < 120){
                        new_Board[n_i][n_j] = 1;
                    }
                }
            }

        }

        for(int i = 0;i<120;++i){
            for(int j = 0;j<120;++j){
                Board[i][j] = new_Board[i][j];
            }
        }

        Board[0][0] = 1;

    }


    cout << "Hello world!" << endl;
    return 0;
}
