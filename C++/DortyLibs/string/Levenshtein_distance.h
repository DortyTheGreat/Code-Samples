int LevenshteinDistance(const std::string& s, const std::string& t){


    const int n = s.size() + 1;
    const int m = t.size() + 1;
    int d[n][m];

    for(int i = 0;i < n;++i){
        for(int j = 0;j < m;++j){
            d[i][j] = 0;
        }
    }


    for(int i = 0;i < n;++i){
        d[i][0] = i;
    }


    for(int i = 0;i < m;++i){
        d[0][i] = i;
    }

    for(int i = 1;i < n;++i){
        for(int j = 1;j < m;++j){
            d[i][j] = std::min(d[i-1][j],d[i][j-1]) + 1;
            d[i][j] = std::min(d[i][j], d[i-1][j-1] + ((s[i-1] == t[j-1])? 0 : 1) );
        }
    }


    return d[n - 1][m - 1];
}
