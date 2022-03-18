
///

#include <bits/stdc++.h>

using namespace std;

const int Plus_Big_Int = 2e9;
const int Neg_Big_Int = -2e9;

int n, l, r;
set<pair<int, int>> Daata;
void merge(int l2, int r2) {

  auto left_it = Daata.upper_bound({l2, Neg_Big_Int});
  if (left_it != Daata.begin()) {
    pair<int, int> current_left = *(left_it);
    left_it--;
    pair<int, int> left = *(left_it);
    if (current_left != left) {
      if (left.second + 1 == current_left.first) {

        Daata.erase(left);
        Daata.erase(current_left);
        Daata.emplace(left.first, current_left.second);

      }
    }
  }


  auto right_it = Daata.upper_bound({r2, Plus_Big_Int});
  if (right_it != Daata.end()) {
    pair<int, int> right = *right_it;

    if (right_it != Daata.begin()) {
        right_it--;
            pair<int, int> current_right = *right_it;
                if (current_right != right) {
                    if (right.first - 1 == current_right.second) {

                      Daata.erase(right);
                      Daata.erase(current_right);
                      Daata.emplace(current_right.first, right.second);

                    }
              }
    }
  }
}

void add(int pos) {
  auto tt = Daata.upper_bound({pos, Plus_Big_Int});
  pair<int, int> t;
  int is_in = 0;
  int new_l, new_r;
  if (tt != Daata.end() && tt != Daata.begin()) {

    tt--; /// 1,2,3
    t = *tt;
    is_in = (t.first <= pos && t.second >= pos);

  }

  if (!is_in) {
    Daata.emplace(pos, pos);
    new_l = pos, new_r = pos;
  }
  else {
    int _l = t.first, _r = t.second;
    int new_pos = _r - (pos - _l);
    new_l = _l - 1, new_r = _r + 1;

    Daata.erase(t);
    Daata.emplace(new_l, new_pos - 1);
    Daata.emplace(new_pos + 1, new_r);
  }

  merge(new_l, new_r);


}

void ask(int pos) {
  pair<int, int> t = *(--Daata.upper_bound({pos, Plus_Big_Int})); /// here

  cout << (t.first <= pos && t.second >= pos) << endl;
}

int main() {
  Daata.emplace(Neg_Big_Int, Neg_Big_Int);
  Daata.emplace(Plus_Big_Int, Plus_Big_Int);

  cin >> n >> l >> r;

  for (int i = 0; i < n; ++i) {
    char req;
    int pos;
    cin >> req >> pos;
    if (req == '+'){
        add(pos);
    }else{
        ask(pos);
    }
  }

  return 0;
}
