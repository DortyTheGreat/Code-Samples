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

    /// special optimization for n=6
    if (vc[5][5] || vc[4][5] || vc[3][5] || vc[2][5] || vc[1][5] || vc[5][4] || vc[5][3] || vc[5][2]
         || vc[5][1] || vc[4][4] || vc[3][4] || vc[4][3] ) return -1; /// ��� �� ������������ �����, �����


    int total_score = 0;

    vector<int> x_offset = {0,1,1};
    vector<int> y_offset = {1,1,0};

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            if (!vc[i][j]) continue;

            if (i == 0 && j == 0) total_score -= 3; /// corner penalty

            else if (i == 0 || j == 0) total_score -= 4; /// wall penalty

            else total_score -= 5; /// general penalty

            for(int dir = 0; dir < 3; ++dir){
                for(int n_i=i + x_offset[dir], n_j = j+y_offset[dir]; n_i < n && n_i > -1 && n_j < n && n_j > -1; n_j += y_offset[dir], n_i += x_offset[dir]){
                    if (vc[n_i][n_j]) break;
                    ++total_score;
                }
            }

        }
    }
    return total_score;
}

vector<int64_t> combo(int64_t n, int64_t k)
{
    int64_t ret = 0;
    vector<int64_t> boards;
    int64_t combo = (1ull << k) - 1;       // k bit sets
    while (combo < 1ull<<n ) {
        ret++;
        ///pretty_print(c, combo);
        ///std::bitset<64> bs(combo);
        ///cout << bs << endl;
        boards.push_back(combo);
        int64_t x = combo & -combo;
        int64_t y = combo + x;
        int64_t z = (combo & ~y);
        combo = z / x;
        combo >>= 1;
        combo |= y;
    }
    return boards;
}

vector<vector<int>> int_to_board(int64_t b, int n){
    vector<vector<int>> ret(n, vector<int>(n));

    for (int i = 0; i < n*n; ++i) {
        ret[i/n][i%n] = ((b >> i) & 1);
    }
    return ret;
}

int Q(int n){
    vector<vector<int>> board(n, vector<int>(n));

    int max_turns = 0;

    for(int queens = 1; queens <= 2*n - 1; ++queens){
        cout << "looking at " << queens << " queens" << endl;
        vector<int64_t> boards = combo(n*n,queens);
        for(const int64_t& b : boards){
            board = int_to_board(b, n);
            ///print_board(board,n);
            ///cout << endl;

            int score = get_score(board,n);
            if (score > max_turns){
                print_board(board,n);
                cout << score << endl << endl;
                max_turns = score;
            }
        }

    }

    return max_turns;
}

/**

������� �������� ��� n >= 6.

8*(n-2)^2



upper_bound, ������������� � ���������� ������ ����:

(n-12)*5*8*4 +
+ 8*(n-12)^2 +
+ 4 * ANS_FROM_PROGRAM +
+ 4 * START_POINTS
===

(n-12)*5*8*4 +
+ 8*(n-12)^2 +
+ 4 * 32
+ 4 * (3 + 10*4 + 25*5)

===

upper_bound from prog
8 n^2 - 32 n + 32


��������
8 n^2 - 32 n + 32


��������������, �.�. upper_bound == �������� ���������, �� ��� n >= 14 �������� �����
===
*/


int main()
{
    cout << Q(6);

    return 0;
}
