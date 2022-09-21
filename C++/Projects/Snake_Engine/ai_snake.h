bool isIllegalMove(pair<int,int> n_head){
    if (n_head.first >= W || n_head.first < 0 || n_head.second >= H || n_head.second < 0){
        return true;
    }
    return (Field[n_head.first][n_head.second]); /// Если пусто -> Field[x][y] = 0 -> false (в ином случае true aka illegal)
}

bool isLegalMove(pair<int,int> n_head){
    if (n_head.first >= W || n_head.first < 0 || n_head.second >= H || n_head.second < 0){
        return false;
    }
    return !(Field[n_head.first][n_head.second]); /// Если пусто -> Field[x][y] = 0 -> false (в ином случае true aka illegal)
}



void bfs_alg(){

    gotoxy(0,H+3);
    queue<pair<int, int>> que;
    que.push(snake.back());
    vector<vector<int>> d(W, vector<int>(H));
    vector<vector<pair<int, int>>> p(W, vector<pair<int, int>>(H));
    const vector<pair<int, int>> neighs = {
        {0, 1},
        {0, -1},
        {-1, 0},
        {1, 0}
    };



    d[snake.back().first][snake.back().second] = 1;
    while(!que.empty()){
        pair<int, int> current_pos = que.front();
        que.pop();

        for (auto& neigh: neighs) {
            pair<int, int> t = { current_pos.first + neigh.first, current_pos.second + neigh.second };

            if (!isIllegalMove(t) && !d[t.first][t.second]) {
                d[t.first][t.second] = d[current_pos.first][current_pos.second] + 1;
                p[t.first][t.second] = current_pos;
                que.push(t);
            }
        }
    }


    vector<pair<int, int>> ans;
    for (pair<int, int> cur = apple; cur != snake.back(); cur = p[cur.first][cur.second]) ans.push_back(cur);
    reverse(ans.begin(), ans.end());
    cout << ans.size() << "    ";
    move(ans.front().first - snake.back().first, ans.front().second - snake.back().second);
}



void ai(){
    gotoxy(0,H+3);
    ///bfs_alg();
    int cou = 0;
    vector<pair<int, int>> kuda = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
    int nap = rand()%4;
    while (isIllegalMove({snake.back().first + kuda[nap].first, snake.back().second + kuda[nap].second})){
        if (cou > 16){
            isAlive = 0;
            return;
        }
        nap = rand()%4;
        cou++;
    }

    cout << cou;
    move(kuda[nap].first, kuda[nap].second);
}
