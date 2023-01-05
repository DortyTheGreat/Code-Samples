#include <iostream>
#include <map>

using namespace std;

struct Node;

map<int, Node* > mp;

struct Node{
    Node* l = nullptr;
    Node* r = nullptr;

    Node* p = nullptr;

    int num;

    Node(int val){
        num = val;
    }

    void feed(int n){
        mp[num] = this;
        if (n >= num*2){
            l = new Node(num*2);
            l->p = this;
            l->feed(n);
        }

        if (n >= num*2+1){
            r = new Node(num*2+1);
            r->p = this;
            r->feed(n);
        }

    }

    void print(){
        if (l != nullptr) l->print();
        cout << num << " ";
        if (r != nullptr) r->print();
    }


    void perform(){



        if (p == nullptr){return;} /// корень

        if (p->l == nullptr){
            /// Правый
            swap(p->l,this->l);
            swap(num,p->num);

            if (this->l != nullptr) this->l->p = this;
            if (p->l != nullptr) p->l->p = p;

            mp[num] = this;
            mp[p->num] = p;
            return;
        }

        if (p->l->num == num ){
            /// Я левый ребёнок
            swap(p->r,this->r);

            if (this->r != nullptr) this->r->p = this;
            if (p->r != nullptr) p->r->p = p;

            swap(num,p->num);

            mp[num] = this;
            mp[p->num] = p;

        }else{

            /// Я правый ребёнок

            swap(p->l,this->l);
            swap(num,p->num);

            if (this->l != nullptr) this->l->p = this;
            if (p->l != nullptr) p->l->p = p;

            mp[num] = this;
            mp[p->num] = p;

        }

    }

};
#include <map>
int main()
{
    int n,q;
    cin >> n >> q;

    Node root(1);



    root.feed(n);
    //root.print();
    //cout << endl;
    ///root.l->r->perform();


    for(int i = 0;i < q; ++i){
        int t;
        cin >> t;
        mp[t]->perform();
        //cout << endl;
        //root.print();
        //cout << endl;
    }

    root.print();


    return 0;
}
