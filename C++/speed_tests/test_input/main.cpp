#include <iostream>

using namespace std;

struct Node{
    Node* left;
    Node* right;

    int value;

    int size_l = 0;
    int size_r = 0;

    Node(){
        left = nullptr;
        right = nullptr;
    }

    Node(int val){
        left = nullptr;
        right = nullptr;
        value = val;
    }

    void print(int deep){
        if (left != nullptr){left->print(deep+1);}

        cout << value << "(" << deep << ") ";

        if (right != nullptr){right->print(deep+1);}
    }



};

void insert(Node *node,int val, int index){

    if (node->size_l > index){
        /// � ����� ����� ���!

        node->size_l++; /// ����� ������� �����! ��������� �������
        insert(node->left, val, index);

        return;
    }

    if (index == node->size_l){
        /// � ���! �� ��� ����!!!!

        if (node->right == nullptr){
            Node* new_ = new Node(val);
            node->size_r = 1;
            node->right = new_;

            return ;
        }

        /// => ����� �� ����, � �������������
        Node *extra = new Node(val);
        extra->size_r = 0;
        extra->size_l = node->size_l;

        extra->left = node->left;
        node->left = extra;


        node->size_l++;

        return;
    }

    /// � ������ �����!

    if (node->right != nullptr){
        /// ���� ������, ����� ��� �����������!
        node->size_r++; /// ����� ������� ������! ��������� ������� (���� �� ����� � �� �����...)
        insert(node->right, val, index - node->size_l - 1);

        return;
    }


    /// ����� ������� ��������� ������ (� ������ �����)

    Node* new_ = new Node(val);
    node->size_r = 1;
    node->right = new_;


    return;

    if (node->right != nullptr){insert(node->right,val,index); return;}
    node->right = new Node(val);
}

int get(Node* node, int index){
    if (node->size_l > index){
        /// � ����� ����� ����

        return get(node->left, index);

    }

    if (index == node->size_l){
        ///��� �!

        return node->value;
    }

    /// � ������ �����!

    if (node->right != nullptr){
        /// ���� ������, ����� ��� �����������!

        return get(node->right, index - node->size_l - 1);
    }


    /// �����.... ������... ���� ������� �������� �� ������. ����� - ������ (��� ���� �� �������, ������� ����, ��� n)
    return -1;




}

int main()
{
    ios_base::sync_with_stdio(0);
    //cin.tie(0);

    int q;
    cin >> q;
    q--;
    char c;
    int idx, val;



    int a,b;

    cin >> c;
    cin >> a >> b;


    Node* head = new Node(b);
    //head->print();

    while (q--) {
        cin >> c;
        if (c == '+') {
            cin >> idx >> val;
            insert(head,val, idx);
            head->print(0);
            cout << '\n';
        }
        if (c == '?') {
            cin >> idx;
            cout << get(head,idx) << '\n';
        }
    }

    //cout << "Hello world!" << endl;
    return 0;
}
