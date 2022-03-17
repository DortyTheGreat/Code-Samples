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
        /// В Левую часть его!

        node->size_l++; /// Новый элемент слева! Увеличить счётчик
        insert(node->left, val, index);

        return;
    }

    if (index == node->size_l){
        /// О НЕТ! ЗА ЧТО МЕНЯ!!!!

        if (node->right == nullptr){
            Node* new_ = new Node(val);
            node->size_r = 1;
            node->right = new_;

            return ;
        }

        /// => слева от меня, с переподвязкой
        Node *extra = new Node(val);
        extra->size_r = 0;
        extra->size_l = node->size_l;

        extra->left = node->left;
        node->left = extra;


        node->size_l++;

        return;
    }

    /// В правую часть!

    if (node->right != nullptr){
        /// Есть правый, пусть сам разбирается!
        node->size_r++; /// Новый элемент справа! Увеличить счётчик (хотя он вроде и не нужен...)
        insert(node->right, val, index - node->size_l - 1);

        return;
    }


    /// Новый элемент добавляем справа (в пустое место)

    Node* new_ = new Node(val);
    node->size_r = 1;
    node->right = new_;


    return;

    if (node->right != nullptr){insert(node->right,val,index); return;}
    node->right = new Node(val);
}

int get(Node* node, int index){
    if (node->size_l > index){
        /// В Левой части ищем

        return get(node->left, index);

    }

    if (index == node->size_l){
        ///ЭТО Я!

        return node->value;
    }

    /// В правую часть!

    if (node->right != nullptr){
        /// Есть правый, пусть сам разбирается!

        return get(node->right, index - node->size_l - 1);
    }


    /// Эээээ.... Абобус... Сюда функция заходить не должна. Зашла - писька (ибо ищем по индексу, который выще, чем n)
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
