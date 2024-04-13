#include <iostream>
#include <vector>
#include <map>
using namespace std;

#define int int64_t

struct Node{
    map<int, Node*> children;
    int number = 1;
};

int64_t sum(Node* nd){
    int64_t ret = 0;
    for(const auto [u,v] : nd->children){
        ret += sum(v);
    }
    ret += (nd->number*(nd->number-1))/2;
    return ret;
}

signed main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    int n;
    cin >> n;
    Node* parent = new Node();

    ///cout << "PN: " << parent->number << endl;
    for(int i = 0; i < n; ++i){
        int sz;
        cin >> sz;
        Node* curNode = parent;
        ///cout << "PN: " << parent->number << endl;
        for(int j = 0; j < sz; ++j){
            int inp;
            cin >> inp;
            ///curNode->number += 1;
            ///cout << curNode->number << endl;
            ///cout << "PN: " << parent->number << endl;
            if (curNode->children.find(inp) == curNode->children.end()){
                curNode->children[inp] = new Node();
            }else{
                curNode->children[inp]->number += 1;
            }
            curNode = curNode->children[inp];
            ///if (curNode.children.find())
        }
    }

    int64_t ret = 0;
    for(const auto [u,v] : parent->children){
        ///cout << u << " ";
        ret += sum(v);
    }
    cout << ret << endl;
    ///cout << "PN: " << parent->number << endl;
    ///cout << parent->number << endl;
    return 0;
}
