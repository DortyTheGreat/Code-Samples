#include <iostream>
#include <algorithm>
using namespace std;


/**

��������� � ������� ���������
������. �� �� �������� ��-�� �� ���������� ����������, ����� ���:

https://neerc.ifmo.ru/wiki/index.php?title=%D0%9D%D0%B5%D1%81%D0%BE%D0%B3%D0%BB%D0%B0%D1%81%D0%BE%D0%B2%D0%B0%D0%BD%D0%BD%D1%8B%D0%B5_%D0%BF%D0%BE%D0%B4%D0%B4%D0%B5%D1%80%D0%B5%D0%B2%D1%8C%D1%8F._%D0%A0%D0%B5%D0%B0%D0%BB%D0%B8%D0%B7%D0%B0%D1%86%D0%B8%D1%8F_%D0%BC%D0%B0%D1%81%D1%81%D0%BE%D0%B2%D0%BE%D0%B3%D0%BE_%D0%BE%D0%B1%D0%BD%D0%BE%D0%B2%D0%BB%D0%B5%D0%BD%D0%B8%D1%8F

*/



template<typename T, const T NEUTRAL_UPDATE = -1001 * 1001 * 1001, const T NEUTRAL_GET = 0>
struct DO{

    int size;

    struct node {
        T value; // ������� � ������� ��� ����� ���������� ��������
        T delayed; // ���������� �������� (������� ����� ��������� �� �������)
        node() : value(NEUTRAL_GET), delayed(NEUTRAL_UPDATE) {}
    };
    node* tree;

    /**

    min -> value
    add -> delayed

    */

    DO(int _size) : size(_size){
        tree = new node[(size+3) * 4];
    }

    // 0 - ������, ����� ��� - v * 2 + 1, ������ - v * 2 + 2


    T update_function(T val, T updater){
        return max(val, updater);
    }

    T get_function(T val1, T val2){
        return val1 + val2;
    }


    // �������� �������� � ������� v � ������ ���������� ��������
    T get(int v) {
        return update_function(tree[v].value, tree[v].delayed);
    }


    void push(int v) {



        tree[v * 2 + 1].delayed = update_function(tree[v * 2 + 1].delayed, tree[v].delayed);
        tree[v * 2 + 2].delayed = update_function(tree[v * 2 + 2].delayed, tree[v].delayed);

        tree[v].delayed = NEUTRAL_UPDATE;
    }

    // ��������� x �� �������
    // v - �������
    // [tl, tr) - ������� ������� �� (������ ������� �� ����������)
    // [l, r) - ������� ������� (������ ������� �� ����������)
    // x - ��, ��� ����� ��������� �� �������
    void update(int v, int tl, int tr, int l, int r, T x) {
        // ������� ������ ������ �� �������� � ������� �������, ������ �� ������
        if (r <= tl || tr <= l) return;

        // ������� ������ ��������� �������� � ������� �������
        if (l <= tl && tr <= r) {
            // ������, ��� �����-������ ����� � ���� ������� ����� ����� ��������� x
            tree[v].delayed = update_function(tree[v].delayed,x);
            return;
        }

        // ���� �� ������ ����, ������ ������� ������ ������������ � �������� �������, � ����� ���������� � �����.
        // �� ��������, � ������� ������� ���� ���������� ��������, ������� ����� ��������� � �����, ������� ������� push
        push(v);

        // ���������� � �����
        int tm = tl + (tr - tl) / 2;
        update(v * 2 + 1, tl, tm, l, r, x);
        update(v * 2 + 2, tm, tr, l, r, x);

        // � ����� ������� ����� ��� ���������� ��������, ������ ��� ���� ������� push, ������� ����� ������
        // ����������� min �� �����. ��� ��� � ����� ����� ���� ���������� ��������, �� ������� �������� � ���, ��������� get
        tree[v].value = get_function(get(v * 2 + 1), get(v * 2 + 2));
    }

    // �������� ������� �� �������
    // v - �������
    // [tl, tr) - ������� ������� �� (������ ������� �� ����������)
    // [l, r) - ������� ������� (������ ������� �� ����������)
    T get(int v, int tl, int tr, int l, int r) {
        // ������� ������ ������ �� �������� � ������� �������, ������ �� ������
        if (r <= tl || tr <= l) {
            return NEUTRAL_GET;
        }

        // ������� ������ ��������� �������� � ������� �������
        if (l <= tl && tr <= r) {
            // ������ ������� � ������ ���������� ��������
            return get(v);
        }

        // ���� �� ������ ����, ������ ������� ������ ������������ � �������� �������, � ����� ���������� � �����.
        // �� ��������, � ������� ������� ���� ���������� ��������, ������� ����� ��������� � �����, ������� ������� push
        push(v);

        // �������� ������ �� ����� � ����� ������� �� ���
        int tm = tl + (tr - tl) / 2;
        T a = get(v * 2 + 1, tl, tm, l, r);
        T b = get(v * 2 + 2, tm, tr, l, r);


        tree[v].value = get_function( get(2*v + 1), get(2*v + 2));

        return get_function(a, b);
    }


    /// [l;r]
    void UF_update(int l, int r, T val){
        update(0,0,size,l,r+1, val);
    }

    /// [l;r]
    T UF_get(int l, int r){
        return get(0,0,size,l,r+1);
    }
};


void solve() {
    int n, m;
    cin >> n >> m;

    DO<int> my_do(n);

    int l, r, x;

    string req;

    while (m--) {
        cin >> req;
        if (req == "^") {
            cin >> l >> r;
            --l;
            --r;
            int value;
            cin >> value;

            ///cout << summ << endl;

            my_do.UF_update(l,r,value);
        }
        if (req == "?") {
            cin >> l >> r;
            --l;
            --r;

            int64_t num = my_do.UF_get(l,r);;
            int64_t den = r-l+1;

            int64_t g = __gcd(num,den);

            num /= g;
            den /= g;
            if (den == 1)
                cout << num << '\n';
            else
                cout << num << "/" << den << '\n';
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.setf(ios_base::boolalpha);
    solve();

    int WTFF;
    cin >> WTFF >> WTFF;
}



