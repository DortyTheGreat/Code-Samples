#include <bits/stdc++.h>
using namespace std;

int seed = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 mt(seed);

int rnd(int a, int b) {
    return a + mt() % (b - a + 1);
}

int best = 40868;

int rounds = 1e8;
const double K = 0.000001;
double T = 5e7;

const int n = 312;
int g[n][n];
int p[n];


const int Ants = 100; /// ���������� �������� �������� �� ������� ��������
const double decay_ = 0.93; /// ����. ��������� ��������
const double Q = 3; /// ��������� �������� :shrug:
const double add_pher = 1;

double pheromone[n][n];
double inc_matrix[n][n];

inline bool with_probability(double x) {
    return ((double)mt() / INT_MAX) <= x;
}

int best_res = 100000000;

void solve() {
    ofstream fout("log.txt");
    freopen("usca312_dist.txt", "r", stdin);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> g[i][j];
            pheromone[i][j] = 1;
            inc_matrix[i][j] = 0;
        }
    }

    cout << "cinned" << endl;

    int visit_journey[n];
    bool visited[n];

    for(int ITTER = 0; ITTER < 100000; ++ITTER){



        for(int Ant = 0; Ant < Ants; ++Ant){
            ///cout << "ant " << Ant << endl;
            ///cout << "itter " << ITTER << endl;

            for(int i = 0;i < n;++i){visited[i] = false;}

            int next_node = 4;///rnd(0,n - 1); /// [0;n - 1]

            visit_journey[0] = next_node;
            visited[next_node] = true;

            int len = 0;

            for(int visits = 1; visits < n; ++visits){
                    ///cout << visited_indexes.size() << endl;
                double coef = ((double)(rnd(0,100000))) / 100000; /// [0;1] ��� �����
                double summ = 0;
                for(int next = 0; next < n; ++next){
                    if (visited[next]) continue;
                    ///cout << next << endl;
                    summ += (Q / g[next_node][next]) * pheromone[next_node][next];
                }
                ///cout << "summ " << summ << endl;
                summ *= coef;
                ///cout << "summ after" << summ << endl;
                double counter = 0;
                for(int next = 0; next < n; ++next){
                    if (visited[next]) continue;
                    counter += (Q / g[next_node][next]) * pheromone[next_node][next];
                    if ( counter > summ){
                            ///cout << "new" << endl;
                        len += g[next_node][next];
                        ///cout << next<<" "<<next_node << endl;
                        next_node = next;
                        visited[next_node] = true;
                        visit_journey[visits] = next_node;
                        break;
                    }
                }

                ///cout << "counter " << counter << endl;

            }
            if (len < best_res){
                best_res = len;
                cout << "I = " << ITTER << " , new best = " << best_res << endl;

                for(int i = 0;i<n;++i){
                    fout << visit_journey[i] << " ";
                    cout << visit_journey[i] << " ";
                }
                fout << endl;
                cout << endl;
            }


            for(int elem = 0; elem < n - 1; ++elem){
                inc_matrix[visit_journey[elem]][visit_journey[elem+1]] += add_pher / len;
            }

        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                pheromone[i][j] = pheromone[i][j] * decay_ + inc_matrix[i][j];
                inc_matrix[i][j] = 0;
            }
        }

        if (ITTER % 100 == 0){
            cout << "I = " << ITTER << " , best = " << best_res << endl;
        }




    }








}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);

    solve();
}
