#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <string>
#include <set>
#include <list>

using namespace std;

struct point {
    int x;
    int y;

    point(int _x, int _y) {
        x = _x;
        y = _y;
    }

    point& operator =(const point& other) {
        x = other.x;
        y = other.y;
        return *this;
    }

    bool operator ==(const point& other) {
        if (x != other.x) return false;
        if (y != other.y) return false;
        return true;
    }

    friend ostream& operator<<(ostream& output, point& p) {
        output << p.x << " " << p.y;
        return output;
    }
};

int BFS(point start, point target, int n, int m, vector<vector<int>> g) {
    list<point> q;
    q.push_front(start);
    vector<vector<int>> d(n, vector<int>(m));

    for (int i = 0; i < d.size(); i++) {
        for (int j = 0; j < d[i].size(); j++) {
            d[i][j] = -1;
        }
    }

    d[start.y][start.x] = 0;
    vector<point> neighbours = { point(0, -1) , point(1, 0) , point(0, 1) , point(-1, 0) };

    while (!q.empty()) {
        point v = q.front();
        q.pop_front();
        if (v == target) return d[target.y][target.x];

        for (auto n : neighbours) {
            point current = point(v.x + n.x, v.y + n.y);
            if (current.x > -1 && current.x < g[0].size())
                if (current.y > -1 && current.y < g.size()) {
                    if (!g[current.y][current.x]) {
                        q.push_back(current);
                        d[current.y][current.x] = d[v.y][v.x] + 1;
                        g[current.y][current.x] = 1;
                    }
                }
        }
    }

    return -1;
}

int main() {
    int n, m;
    cin >> n >> m;
    int startx, starty, endx, endy;
    cin >> startx >> starty >> endx >> endy;
    vector<vector<int>> arr(n, vector<int>(m));

    startx--;
    starty--;
    endx--;
    endy--;

    for (int i = 0; i < arr.size(); i++) {
        for (int j = 0; j < arr[i].size(); j++) {
            char t;
            cin >> t;
            arr[i][j] = (t == '.'? 0: 1);
        }
    }

    cout << BFS(point(starty, startx), point(endy, endx), n, m, arr);

ending:
    cout << endl;

    system("pause");
    return 0;
}
