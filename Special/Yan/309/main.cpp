#include <iostream>
#include <vector>
using namespace std;

int values[100 * 1001];

int get_root(int v, int *p){
    if(p[v] == v)
    return v;

    return p[v] = get_root(p[v],p);


}

bool is_connected(int a, int b,int *p){
    return (get_root(a,p) == get_root(b,p));
}

void connect(int a, int b,int *p){
    a = get_root(a,p);
    b = get_root(b,p);
    if(values[a] < values[b])
        p[a] = b;
    else if (values[a] > values[b])
        p[b] = a;
    else{
        p[a] = b;
        values[b]++;
    }
}


int main()
{
    int n,m;
    cin >> n >> m;
    vector<pair<int,int> > arcs;

    for(int i = 0; i < 100 * 1001; ++i){
        values[i] = 0;
    }

    vector<bool > selected(m);

    for(int i = 0;i < m; ++i){
        selected[i] = 0;
    }

    vector<int > selected_order;

    for(int i = 0;i < m; ++i){
        int a,b;
        cin >> a >> b;
        a--;
        b--;
        arcs.push_back({a,b});
    }

    int q;
    cin >> q;

    for(int i = 0;i < q; ++i){
        int s;
        cin >> s;
        s--;
        selected[s] = true;
        selected_order.push_back(s);
    }

    int * p = new int[n];


    for(int i =0;i<n;i++){
        p[i] = i;
    }

    int svyaz = n;

    for(int i = 0;i < m; ++i){
        if (!selected[i]){
            if (!is_connected(arcs[i].first,arcs[i].second,p) ){
                connect(arcs[i].first,arcs[i].second,p);
                svyaz--;
            }
        }
    }

    vector<int> out;
    for(int i = q - 1;i > -1; --i){


        out.push_back(svyaz);


        if (!is_connected(arcs[selected_order[i]].first,arcs[selected_order[i]].second,p) ){
            connect(arcs[selected_order[i]].first,arcs[selected_order[i]].second,p);
            svyaz--;
        }


    }



    for(int i = out.size() - 1; i > -1; --i){
        cout << out[i] << ' ';
    }

    return 0;
}
