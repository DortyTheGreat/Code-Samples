#pragma comment(linker, "/STACK:3677721616")

#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <stack>


#define fin cin

using namespace std;

const int size_ = 100005; /// 100000

///---Объявление переменных для "изменных правил игры", например, крестики-нолики с именчивым размером поля

int k;

///---




/// Уникальное имя состояния "Чёрная Дыра". О состоянии нет информации.
const int secret_number = -1337;


/// Реализация Псевдо-Идеальной Мат. Игры.
/// У любого начального состояния игры существует некоторой "идельный исход". Исход - есть число (например, можно сделать так, что 1 - победа, 2 - поражение, 0 - ничья, или типо того)
/// Состояния имеют "ходы", именно благодаря ходам и определяются "идельные исходы". Состояние - тоже есть натуральное число.

/// Массив, который хранит в себе "идеальные состояния"
int Calculated[size_];


/// Информация о возможных мат. ходах, т.е. например в arci[1] содержиться информация о 1ом(2ой по человечески) состоянии, т.е. если arci[1] = {3,5,7} - означает, что находясь в позиции 1 можно попасть в позицию 3, 5 или 7
vector<int> arci[size_];

/// arci, но перевёрнут. aka arci[1] = {3,5,7} => rev_arci[3] = {1 ...}, rev_arci[5] = { 1....}, rev_arci[7] = {1...}
vector<int> rev_arci[size_];

/// Системная переменная-счётчик. Не трогать
int curr[size_];


/// Набор "конечных состояний" для определённого состояния. Т.е. used[3] = {1,2} <=> из позиции 3 можно получить либо исход и, либо исход 2 (победа ил поражение, например)

set<int> used[size_];


/// З.Ы. если used[??] = {1,2} - это типо скилл интенсив ход, ты решаешь сам свою судьбу, used[??] = {1} - нет разницы как ходить - все исходы одни и те же (1)



/// Какой есть идеальный исход, если знаем исходы других ходов. (Все исходы есть в used[pos])
int what_is_my_perfect_outcome(int pos){
    /// Исходы -> used[pos]
    int returner = 0;

    while(used[pos].find(returner) != used[pos].end()){
        returner++;
    }

    return returner;
}


short dodje_stack_of(int start_pos){
    stack<int> asks;
    asks.push(start_pos);

    while(!asks.empty()){
        int pos = asks.top();



        int n = arci[pos].size();


        if (n > curr[pos]){
            asks.push(arci[pos][curr[pos]]);

            curr[pos]++;
            continue;
        }else{
            int returner = what_is_my_perfect_outcome(pos);


            if (Calculated[pos] != secret_number){
                asks.pop();
                continue;
            }

            Calculated[pos] = returner;



            int n2 = rev_arci[pos].size();

            for(int i =0;i<n2;i++){
                used[rev_arci[pos][i]].insert(returner);
                ///curr[]
                ///cout << pos << " sent " << returner << " to " << rev_arci[pos][i]    << endl;
            }



        }




    }

    return Calculated[start_pos];

}


int main()
{
    //ifstream fin("input.txt");



    /// Можно и не сизе, а просто n.
    for(int i =0;i<size_;i++){
        curr[i] = 0;
    }

    for(int i =0;i<size_;i++){
        Calculated[i] = secret_number;
    }



    ///---ВВОД НАЧАЛЬНЫХ ДАННЫХ
    int n,m;
    fin >> n >> m >> k;



    for(int i =0;i<m;i++){
        int a,b;



        arci[a-1].push_back(b-1);
        rev_arci[b-1].push_back(a-1);

    }


    ///--- ВВОД Н.Д.


    for(int i =0;i<n;i++){
        cout << dodje_stack_of(i) << endl;
    }

    // << "Hello world!" << endl;
    return 0;
}

