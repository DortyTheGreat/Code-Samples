#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

/*

Класс Графа Был написан Александром Кулешовым (aka Тесла aka Дорти)
В 19.05.2021

*/

class Graph{
private:

    int color[10000]; /// Вспомогательный массив
    vector<pair<int,int>> Rebra[10000]; /// Информация о Ребрах (Индекс, Значение ребра)
    int Vershini[10000]; ///Информация о Вершинах

    int Itterator=0; /// Тот элемент, с которого начинается Нумерация Графа(1 или 0)
    int Amount_Of_Rebras = 0;

public:
    void dfs (int v) {
        if(color[v]){return;}
        color[v] = 1;
        for (int i=0; i<Rebra[v].size(); ++i)
            dfs(Rebra[v][i].first);
        color[v] = 2;
    }

    void FillColorWithZeros(){
    for(int i=0;i<10000;i++){color[i]=0;}
    }
    void SetItterator(int number){
    Itterator = number;
    }

    void Read_Rebra_As_Matrix(){
        cin >> Amount_Of_Rebras;
        for(int i=Itterator;i<Amount_Of_Rebras+Itterator;i++){
                for(int j=Itterator;j<Amount_Of_Rebras+Itterator;j++){
                    int rec;
                    cin >> rec;
                    if(rec != 0){
                        Rebra[i].push_back( make_pair(j,rec) );
                    }

                }
        }
    }

    int ConponentSvyaznosti(){
        dfs(1);
        int cou_=1;
        for(int i=Itterator;i<Amount_Of_Rebras+Itterator;i++){
                if(color[i] == 0){dfs(i);cou_++;}
        }
        return cou_;
    }
};


int flag=0;


int main(){
    Graph MyGraph;
    MyGraph.SetItterator(1);
    MyGraph.FillColorWithZeros();
    MyGraph.Read_Rebra_As_Matrix();

    if(MyGraph.ConponentSvyaznosti() == 1){
        cout << "YES";
        }else{
        cout << "NO";
        }




}
