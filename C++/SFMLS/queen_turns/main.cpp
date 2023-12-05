#include <iostream>
#include <vector>


using namespace std;

void print_board(const vector<vector<int>>& vc, int n){
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            cout << vc[i][j] << " ";
        }
        cout << "\n";
    }
}

bool change_board(vector<vector<int>>& vc, int n){
    int px=0,py=0;
    while ( (vc[px][py] ^= 1) == 0 ){
        if (++py == n){
            py = 0;
            if (++px == n){
                return 0;
            }
        }
    }

    return 1;
}

int get_score(const vector<vector<int>>& vc, int n){
    int total_score = 0;

    vector<int> x_offset = {0,0,1,-1,1,-1,1,-1};
    vector<int> y_offset = {1,-1,0,0,1,-1,-1,1};

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            if (!vc[i][j]) continue;

            for(int dir = 0; dir < 8; ++dir){
                for(int n_i=i + x_offset[dir], n_j = j+y_offset[dir]; n_i < n && n_i > -1 && n_j < n && n_j > -1; n_j += y_offset[dir], n_i += x_offset[dir]){
                    if (vc[n_i][n_j]) break;
                    ++total_score;
                }
            }

        }
    }
    return total_score;
}

int Q(int n){
    vector<vector<int>> board(n, vector<int>(n));

    int max_turns = 0;

    while(change_board(board,n)){

        int score = get_score(board,n);
        if (score > max_turns){
            print_board(board,n);
            cout << score << endl << endl;
            max_turns = score;
        }

    }

    return max_turns;
}

int main()
{
    for(int i = 1; i < 6; ++i){
        cout << Q(i) << " ";
    }
    cout << Q(3);

    return 0;
}
