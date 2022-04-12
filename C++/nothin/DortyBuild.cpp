/*
---------------------
This File was Build Automatically by DortyBuild v 1.3.
For More Information ask:
Discord: �����#9030 
---Original---Code---

#include <iostream>
#include "../DortyLibs/DortyGraph.h"
#include "../DortyLibs/DortyBuild.h"
#include "../DortyLibs/BetterVector.h"
#include "../DortyLibs/Cython.h"
#include "../DortyLibs/algo.h"
#include "../DortyLibs/OperatorBigInt.h"
#include <fstream>
#include "../DortyLibs/NewtonsSQRT.h"
using namespace std;

int main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    AppBuild();
    BigInt a = 1000;
    BigInt b = 999;
    BigInt c,d;


    cin >> a;

    b = a;
    //a._sqrt();
    a = sqrt(a);


    cout << a; //endl << d;

    a *= a;
    b._subtract(a);
    cout << endl << b;


    ///cout << a << endl;

    //cout << r << endl;


    ///cout << counter << endl;
    return 0;
}


*/
#include <iostream>
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;



///==========
///Реализация "Идеального" Графа через определение "Дуг", как динамический массив Сетов. Реализация может быть медленной, при ОГРОМНОМ количестве точек (1 миллион+)
///Автор: Александр Кулешов (aka Dorty_Schmorty aka DortyTheGreat aka Тесла).
///Начало создания: 04.09.2021, последнее изменение было сделано в 29.09.2021
///==========

class Node{
public:
    /// Значение Верщины (например, цена за посещение вершины)
    long long value;
    /// При Вызове поисков по графу в эту переменную заносим растояние от стартовой точки до этой.
    long long SearchedDistance;

    /// Нужна для востановления пути. Или для поиска непересекающихся вершин в графе (aka Поиск количества компонент связности)
    /// 0 - вершину не посещали при поиске
    /// 1 - Вершина есть источник поиска (из неё искали)
    /// 2 - Вершина есть близлизжайщий сосед к источнику
    /// 3 - Вершина есть близлизжайщий сосед через ещё одну вершину (ЗАМЕТЬТЕ, что хоть и вершина может быть соседом с источником, но может иметь значение 3,
    /// если путь в источник длиннее, чем путь в другого соседа, а потом источник (aka distance(THIS-> 2 -> 1) < distance(THIS -> 1) ))
    /// 4 - Вершина есть близлизжайщий сосед через ещё 2 вершины
    /// 5 - Вершина есть близлизжайщий сосед через ещё 3 вершины, 6 через 4, 7 через 5, 8 через 6 ... и т.д.
    long long used;

    /// Доп. Значение
    long long custom_data;


};

class Arc{
public:
    /// Значение дуги (например, расстояние)
    long long value;

    /// т.к. оригинально Дуга храниться в массиве из сэтов "Arcs", то
    /// Arcs[0] = [(311, 5),(43, 4)] - Дуга из точки "0" в точку "5". Длина дуги = 311, Дуга из точки "0" в точку "4". Длина дуги = 43
    /// Место назначения этой дуги
    long long direction;


    bool operator<(const Arc& other) const {
        return (direction < other.direction);



    }

};

/// Сортирует арки по значениям, а не направлению (нужно, например для непересек. множетсв)
class Arc_Sorted{
    public:

    /// Откуда
    long long origin;
    /// Значение дуги (например, расстояние)
    long long value;
    /// Место назначения этой дуги
    /// т.к. оригинально Дуга храниться в массиве из сэтов "Arcs", то
    /// Arcs[0] = [(311, 5),(43, 4)] - Дуга из точки "0" в точку "5". Длина дуги = 311, Дуга из точки "0" в точку "4". Длина дуги = 43
    /// Место назначения этой дуги
    long long direction;
    bool operator<(const Arc_Sorted& other) const {


        if (value != other.value)
            return value < other.value;

        if (origin == other.origin)
            return direction < other.direction;

        return origin < other.origin;

    }
};

class Graph{
public:
    long long OutPutFormat=0; /// В некоторых задачах просят выводить начиная с единицы
    long long Size; /// Количество вершин
    Node * Nodes; /// Точки aka vertices aka vertex aka Вершина
    set<Arc> * Arcs; /// Дуги aka направленные рёбра aka

    const long long pseudo_inf = 10000000000;

    Graph& operator= (Graph another){

        Size = another.Size;
        Nodes = another.Nodes;
        Arcs = another.Arcs;
        OutPutFormat = another.OutPutFormat;



        return *this;

    }

    void init(long long size_){
        /// Иннициализирует Граф с количеством Нод(точек) size_ (также известно, как n). Использовать, если создаёте свой ввод графа
        Size = size_;
        Arcs = new set<Arc> [Size];
        Nodes = new Node [Size];


        for(long long i = 0; i < Size; i++ ){
            Nodes[i].SearchedDistance=pseudo_inf;
            Nodes[i].used = 0 ;
            Nodes[i].value = 0;
        }
    }

    void InsertNewArc(long long start_point,long long value, long long direction){
        /// Добавляет арку в Граф. Перед использованием следует написать GRAPH.init(n), затем можно использовать эту функцию для создания своего кастомного ввода
        Arc A1 = {value,direction};

        Arcs[start_point].insert(A1);
    }

    void ReadAsSquareMatrix(int sz){
        /// Читает Граф, как двумерную матрицу. Читает n, затем n^2 чисел - матрица смежности. Если 0 - нет соединеня, если не 0 - даёт расстояние {INPUT} в Арку

        init(sz);

        long long req; // 1 - есть вход, 0 - нет
        for(long long i = 0; i < Size; i++){
            for(long long j = 0; j < Size; j++){
                cin >> req;
                if(req > 0){
                    InsertNewArc(i,req,j);
                }
            }
        }
    }

    void ReadAsSquareMatrix(){
        /// Читает Граф, как двумерную матрицу. Читает n, затем n^2 чисел - матрица смежности. Если 0 - нет соединеня, если не 0 - даёт расстояние {INPUT} в Арку


        cin >> Size;

        ReadAsSquareMatrix(Size);
    }

    void ReadAsODArcList(bool directed, int format){
        /// Читает Граф, как ... One Distanced(длина=1) Arc List (a -> b, если directed==1, a <-> b, если directed==0)
        /// format = 1, если граф задаётся рёбрами, как 1 .. n, а не 0 .. n-1

        cin >> Size;

        init(Size);
        int m;
        cin >> m;

        int from, to;

        for(long long counter = 0; counter < m; counter++){

                cin >> from >> to;
                from -= format;
                to -= format;
                InsertNewArc(from,1,to);
                if(!directed){
                    InsertNewArc(to,1,from);
                }

        }
    }

    set<Arc>::iterator GetThisArcIterator(long long start_point, long long direction){
        /// Возвращает иттератор Арки по заданным начальной и конечной точки (использование -> получить расстояние Арки от Ноды до Ноды)
        Arc A1 = {1,direction};
        return Arcs[start_point].find(A1);
    }

    Arc GetThisArc(long long start_point, long long direction){
        /// Возвращает Арку по заданным начальной и конечной точки (использование -> получить расстояние Арки от Ноды до Ноды)
        return *GetThisArcIterator(start_point, direction);
    }

    bool IsThereArc(long long start_point, long long direction){
        /// Возвращает true или false в зависимости от того, существует ли Арка от start_point до direction
        return GetThisArcIterator(start_point,direction) != Arcs[start_point].end();
    }

    bool isOriented(){
        /// Узнаёт ориентирован ли граф

        for(long long cou = 0; cou < Size; cou++){
            for (Arc i : Arcs[cou]){
                if (!IsThereArc(i.direction,cou)){
                    return 1;
                }
            }
        }
        return 0;
    }

    bool DoesContainLoop(){
        for(long long cou = 0; cou < Size; cou++){
            if (IsThereArc(cou,cou)){return 1;}
        }
        return 0;
    }

    void DisorientGraph(){
        /// Дезориентирует Граф, добавляя лишнии Арки, чтобы сделать Ориентированным
        for(long long cou = 0; cou < Size; cou++){


            for (Arc i : Arcs[cou]){
                if (!IsThereArc(i.direction,cou)){
                    InsertNewArc(i.direction,i.value,cou);
                }
            }
        }
    }

    void Requr_BFS(long long Uses, long long distanto,long long dot){
        /// Зарезервированная функция для Мульти-Дейкстры
        if( distanto > Nodes[dot].SearchedDistance ){return;}

        if (distanto == Nodes[dot].SearchedDistance){
            Uses = max(Uses,Nodes[dot].used);
        }

        Nodes[dot].used = Uses;
        Nodes[dot].SearchedDistance = distanto;

        for (Arc i : Arcs[dot]){

            Requr_BFS(Uses+1,distanto+i.value,i.direction);
        }



    }

    void Dijkstra_Search(long long start_point){
        /// Зпускает Мульти-Поиск по графу (по сути тот же Дейкстра-Поиск)
        for(long long i=0;i<Size;i++){
            Nodes[i].SearchedDistance=pseudo_inf;
            Nodes[i].custom_data=0;
            Nodes[i].used = 0; ///-> ломает последовательные запуски

        }
        Nodes[start_point].SearchedDistance = 999;
        Requr_BFS(1,0,start_point);
    }


    void Quick_Search(int start_point, bool update_nodes){

        if (update_nodes){
            for(long long i=0;i<Size;i++){
                Nodes[i].SearchedDistance=pseudo_inf;
                Nodes[i].custom_data=0;
                Nodes[i].used = 0; ///-> п╩п╬п╪п╟п╣я┌ п©п╬я│п╩п╣п╢п╬п╡п╟я┌п╣п╩я▄п╫я▀п╣ п╥п╟п©я┐я│п╨п╦
            }
        }

        set<pair<long long, int>> itteratable; /// dist, index
        itteratable.insert(make_pair(0,start_point));

        Nodes[start_point].SearchedDistance = 0;
        Nodes[start_point].used = 1;

        for (int i = 0; i < Size; i++){
            itteratable.insert({ Nodes[i].SearchedDistance, i });
        }

        while(!itteratable.empty()){
            pair<long long,int> first_itter = *(itteratable.begin());

            long long first_ = first_itter.first;
            long long second_ = first_itter.second;

            itteratable.erase(itteratable.begin());

            for(Arc that : Arcs[second_]){

                long long dist = first_+that.value;

                if ((Nodes[that.direction].SearchedDistance > dist) && (itteratable.find({ Nodes[that.direction].SearchedDistance, that.direction }) != itteratable.end()) ){
                    itteratable.erase(itteratable.find({ Nodes[that.direction].SearchedDistance, that.direction }));

                    Nodes[that.direction].SearchedDistance = dist;
                    Nodes[that.direction].used = Nodes[first_itter.second].used+1;

                    itteratable.insert({Nodes[that.direction].SearchedDistance,that.direction});
                }
            }
        }
    }



    // FireStation

    set<long long> Requr_BFS_fire(long long Uses, long long distanto,long long dot){
        set<long long> return_value;

        if( distanto >= Nodes[dot].SearchedDistance ){
                set<long long> nulled;

                return nulled;}

        Nodes[dot].used = Uses;
        Nodes[dot].SearchedDistance = distanto;
        bool flag = 1;



        for (Arc i : Arcs[dot]){
            flag = 0;
            set<long long> that = Requr_BFS_fire(Uses+1,distanto+i.value,i.direction);
            return_value.insert(that.begin(),that.end());

        }

        if (flag == 1){
            return_value.insert(dot);
        }

        return return_value;



    }

    set<long long> Dijkstra_Search_fire(long long start_point){

        for(long long i=0;i<Size;i++){
            Nodes[i].SearchedDistance=pseudo_inf;
            ///Nodes[i].used=0;
        }
        return Requr_BFS_fire(1,0,start_point);
    }


    //FireStation

    void gSort(long long i, vector<long long>& res, long long c,long long &flag) {
        ///graph -> рёбра, color -> Node.value, res - ХЗ
        if (Nodes[i].value == 1 && flag == 0) {
            flag = 1;
            return;
        }
        if (Nodes[i].value) return;

        Nodes[i].value = 1;



        for (Arc that_arc : Arcs[i]) {

            gSort(that_arc.direction, res, c,flag);
        }
        res.push_back(i);

        Nodes[i].value = c;
    }

    pair<vector<long long>,long long> StartTopSort(){

        for(long long i =0;i<Size;i++){
            Nodes[i].value = 0;
        }
        vector<long long> result;
        long long flag = 0;
        for (long long i = 0; i < Size; i++) {
            if (!Nodes[i].value) {
                gSort(i, result, i + 1,flag);
            }
        }
        return make_pair( result,flag);

    }

    void ReverseGraph(){
        Graph temp;
        temp.init(Size);

        for(long long cou = 0; cou < Size; cou++){


            for (Arc i : Arcs[cou]){

                temp.InsertNewArc(i.direction,i.value,cou);

            }
        }

        Arcs = temp.Arcs;
    }

    Graph Get_Condensated_Graph(){

            /// В custom_data находится старое "имя-индекс" ноды

            ///ВНИМАНИЕ!
            ///НА ДАННЫЙ МОМЕНТ ГРАФ, ПРИ КОНДЕНСАЦИИ ЗАБЫВАЕТ ПРО ТАКИЕ ЗНАЧЕНИЕ, как distance у Арок, а также почти все даные с точек стираются
            ///

          Graph G2;

          G2 = *this;

          G2.ReverseGraph();

          pair<vector<long long>,long long> ABOOBA = StartTopSort();
          vector<long long> res = ABOOBA.first;
            long long flag_temp = ABOOBA.second;

          reverse(res.begin(), res.end());

          vector<long long> _res;


            for(long long i =0;i<Size;i++){
                G2.Nodes[i].value = 0;
            }

          for(auto val: res) {
            //cout << val << endl;
            G2.gSort(val, _res, val + 1,flag_temp);
          }
          long long counter = 0;
          set<pair<long long, long long>> diff_col;
          for (long long i = 0; i < Size; ++i) {
            for (auto counter_: G2.Arcs[i]) {
                long long v = counter_.direction;
              //cout << i << " " << v << " "  << inv_color[i] << " " << inv_color[v] << endl;
              if (G2.Nodes[i].value != G2.Nodes[v].value) {
                counter++;
                diff_col.emplace(G2.Nodes[v].value, G2.Nodes[i].value);
              }
            }
          }

          //cout << "counter: " << counter;

          Graph Condensated_Graph;
          Condensated_Graph.init(Size);
            long long * Achiles_array = new long long [Size];long long achiles_cou = 0;

            const long long PLACEHOLDER = -10;
            for(long long i =0;i<Size;i++){
                Achiles_array[i] = PLACEHOLDER;
            }

            for (auto pseudo_arc : diff_col){
                    //cout << "WARN" << endl;
                long long first = pseudo_arc.first - 1;
                long long second = pseudo_arc.second - 1;

                if (Achiles_array[first] == PLACEHOLDER){
                    Achiles_array[first] = achiles_cou;
                    achiles_cou++;
                }

                if (Achiles_array[second] == PLACEHOLDER){
                    Achiles_array[second] = achiles_cou;
                    achiles_cou++;
                }

                first = Achiles_array[first];
                second = Achiles_array[second];

                Condensated_Graph.InsertNewArc(first,1,second);/// ААААА, почему теперь у всего длина 1 ???

                //cout << first << " " << second << endl;
            }

            long long add_cou = 0;

            for(long long i =0;i<Size;i++){

                //cout << i<< " " << (Nodes[i].value-1) << endl;
                if ( ((i) == (Nodes[i].value-1)) ){
                    if (Achiles_array[i] == PLACEHOLDER){




                        Condensated_Graph.Nodes[achiles_cou+add_cou].custom_data = i;
                        add_cou++;

                        //Condensated_Graph.Nodes[i].custom_data = 10000;
                        //cout << i << " <-i " << 3 << endl;
                    }
                }
            }

            Condensated_Graph.Size = add_cou + achiles_cou;


            /// Обратное Ахилесовое действие, для восстановление "старых имён" нод. Можно ускорить. Можно удалить, если не нужно помнить старые имена
            for(long long i =0;i<achiles_cou;i++){
                    long long find_index = -1;
                    for(long long j =0;j<Size;j++){
                        if (Achiles_array[j] == i){
                            find_index = j;
                            break;
                        }
                    }
                Condensated_Graph.Nodes[i].custom_data = find_index;
            }
            //cout << "BRUS" << Condensated_Graph.Nodes[1].custom_data << endl;

          return Condensated_Graph;
    }

    /// Система непересекающихся множеств


    long long get_root(long long v, long long *p){
        /// Долговато передовать массив как аргумент в функцию, следует потом ускорить (хотя Хевав и Госунов сказали, что быстро)
        if(p[v] == v)
        return v;

        p[v] = get_root(p[v],p);
        return p[v];

    }

    bool is_connected(long long a, long long b,long long *p){
        return (get_root(a,p) == get_root(b,p));
    }

    void connect(long long a, long long b,long long *p){
        a = get_root(a,p);
        b = get_root(b,p);
        if(Nodes[a].value < Nodes[b].value)
            p[a] = b;
        else if (Nodes[a].value > Nodes[b].value)
            p[b] = a;
        else{
            p[a] = b;
            Nodes[b].value++;
        }
    }

    Graph Get_MinOst_Graph(){
        /// работает только с неориентированным графом, возвращая неориентированный граф
        Graph G_minOst;
        G_minOst.init(Size);

        long long * p ; ///
        p = new long long[Size]; /// родитель в системе непересекающихся множеств.

        for(long long i =0;i<Size;i++){
            p[i] = i;
        }

        ///long long rank_[100000]; /// Nodes[i].value
        /// В G_minOst - rank_ инициализирован

        /// connect может вызываться только у G_minOst

        set<Arc_Sorted> All_Arcs;
        for(long long i =0;i<Size;i++){
            for(Arc that : Arcs[i]){
                Arc_Sorted temp;
                temp.value = that.value;
                temp.direction = that.direction;
                temp.origin = i;
                All_Arcs.insert(temp);
            }
        }

        for (Arc_Sorted that : All_Arcs){
            if (!G_minOst.is_connected(that.origin,that.direction,p)){

                 G_minOst.InsertNewArc(that.origin,that.value,that.direction);
                 G_minOst.InsertNewArc(that.direction,that.value,that.origin);

                 G_minOst.connect(that.origin, that.direction,p);
            }
        }


        return G_minOst;
    }


    void ItterateAllNode_sArcs(long long Node, bool WriteValue, bool WriteDirection, bool WriteEndl, string NullTxt){

        /// NullTxt - что выводить, если вершин нет
        long long Nulled = 1;
        for (Arc i : Arcs[Node]){
            if(WriteValue){
                cout << i.value << " ";
            }
            if(WriteDirection){
               cout << i.direction+OutPutFormat << " ";
            }
            if(WriteEndl){
                cout << endl;
            }
            Nulled = 0;
        }

        if(Nulled){
            cout << NullTxt;
            if(WriteEndl){
                cout << endl;
            }
        }

    }

    long long GetLongestBranch(long long midPoint){
        /// Получает Длину(как количество Арок) от точки midPoint в графе до самой дальней точки(как в неориентированном графе)
        DisorientGraph();
        Dijkstra_Search(midPoint);

        long long longest = -1;
        long long INDEX = -1;
        for(long long i =0;i<Size;i++){
                long long that = Nodes[i].used-1;
                if (that > longest){
                    longest = that;
                    INDEX = i;
                }

        }
        return longest;
    }

    long long GetDiameter(long long midPoint){
        /// Получает Длину(как количество Арок) Диаметра в графе(как в неориентированном графе)
        DisorientGraph();
        Dijkstra_Search(midPoint);

        long long longest = -1;
        long long INDEX = -1;
        for(long long i =0;i<Size;i++){
                long long that = Nodes[i].used-1;
                if (that > longest){
                    longest = that;
                    INDEX = i;
                }

        }



        Dijkstra_Search(INDEX);

        long long longestPAIR = -1;

        for(long long i =0;i<Size;i++){
                long long that = Nodes[i].used-1;
                if (that > longestPAIR){
                   longestPAIR = that;
                }

        }

        return longestPAIR;
    }

    long long count_component_svyaz(){
        long long cou = 0;

        for(long long i =0;i<Size;i++){
            Nodes[i].used = 0;
        }

        for(long long i =0;i<Size;i++){
            if (Nodes[i].used == 0){
                cou++;
                Dijkstra_Search(i);
                //cout << "SEARCHING... " << i << endl;
            }
        }

        return cou;
    }


};





#include <vector>


template <typename T>
ostream& operator<<(ostream &in, const vector<T> &vect) {
    int n = vect.size();



    for(int i =0;i<n;i++){

        in << vect[i] << " " ;

    }

    return in;
}

template <typename T>
istream& operator>>(istream& in, vector<T> &vect) {
    int size_;
    in >> size_;

    vect.resize(size_);

    for(int i = 0;i<size_;i++){
        in >> vect[i];
    }

    return in;
}

template <typename T>
void operator += (vector<T> &vect,T number) {
    vect.push_back(number);
}

template <typename T>
vector<T> get_all_sub_strings(T &vect){

    vector<T> ret;

    int sz = vect.size();

    for(int l = 0;l<sz;l++){
        for(int r = l+1;r<sz+1;r++){
            T obj;
            for(int cou = l;cou < r;cou ++){
                obj += vect[cou];
            }
            ret.push_back(obj);

        }
    }

    return ret;
}


/// ifdef iostream
template <typename T>
void read(vector<T> &vc, int sz){
    vc.resize(sz);
    for(int i =0;i<sz;++i){
        cin >> vc[i];
    }
}

template <typename T>
T sum(vector<T> &vect){
    T ret = 0;
    int sz = vect.size();
    for(int l = 0;l<sz;l++){
        ret += vect[l];
    }
    return ret;
}

template <typename T>
T min(vector<T> &vect){
    T ret = vect[0];
    int sz = vect.size();
    for(int i = 0;i<sz;i++){
        ret = min(ret,vect[i]);
    }
    return ret;
}

template <typename T>
T max(vector<T> &vect){
    T ret = vect[0];
    int sz = vect.size();
    for(int i = 0;i<sz;i++){
        ret = max(ret,vect[i]);
    }
    return ret;
}

template <typename T>
vector<T> list(basic_string<T> str){
    vector<T> ret;
    ret.resize(str.size());
    for(size_t i = 0;i<str.size();i++){
        ret[i] = str[i];
    }
    return ret;
}

template <typename T>
inline T first(vector<T> &vect){
    return vect[0];
}

template <typename T>
inline T last(vector<T> &vect){
    return vect[vect.size() - 1];
}


#include <vector>

void YesNo(bool arg){
    if (arg){
        cout << "YES" << endl;
    }else{
        cout << "NO" << endl;
    }
}

void NoYes(bool arg){
    if (arg){
        cout << "NO" << endl;
    }else{
        cout << "YES" << endl;
    }
}

string input(){
    string returner;
    cin >> returner;
    return returner;
}

template <typename T>
T input(T ab){
    T returner;
    cin >> returner;
    return returner;
}

long long to_int(string str){
    long long mask = 1;
    size_t start_index = 0;
    long long returner = 0;
    if (str[0] == '-'){
        mask = -1;
        start_index = 1;
    }

    for(size_t i =start_index;i<str.size();i++){
        returner *= 10;
        returner += (str[i] - '0');
    }
    return returner * mask;
}

long long intput(){
    return to_int(input());
}

template <typename T, typename F>
void print(T a, F b){
    cout << a << " " << b << endl;
}

template <typename T>
T max(const vector<T> &vect){
    if (vect.size() < 1){
        return -1;
    }
    T max_ = vect[0];
    for (auto i : vect){
        max_ = max(max_,i);
    }
    return max_;
}

template <typename T>
T indexOf(const vector<T> &vect, T element){
    size_t size_ = vect.size();
    for (int i =0;i<size_;++i){
        if (vect[i] == element){
            return i;
        }
    }
    return -1;
}

template <typename T>
vector<T> slice(const vector<T> &vect, size_t elements){

    vector<T> returner;

    size_t size_ = min(vect.size(),elements);

    for (int i =0;i<size_;++i){
        returner.push_back(vect[i]);
    }
    return returner;
}

void print(string data){
    cout << data << endl;
}






template <typename T>
vector<T> NOP(vector<T> A, vector<T> B){

     int n = A.size();
     int m = B.size();

    vector<vector<T> > F(n + 1, vector<T>(m + 1));

     for (int i =1;i<=n;i++){
        for (int j =1;j<=m;j++){
            if (A[i-1] == B[j-1]){
                F[i][j] = F[i - 1][j - 1] + 1;
            }else{
                F[i][j] = max(F[i - 1][j], F[i][j - 1]);
            }
        }
     }


     vector<T> Ans;
     int i = n;
     int j = m;
     while (i > 0 && j > 0){
        if (A[i - 1] == B[j - 1]){
            Ans.push_back(A[i - 1]);
            i -= 1;
            j -= 1;
        }else{
        if (F[i - 1][j] == F[i][j]){
            i--;

        }else{
            j--;
        }
        }
     }
     reverse(Ans.begin(),Ans.end());

    return Ans;
}



vector<long long> vector_generator(int n, int a1, int k, int b, int m){
    vector<long long> ret(n);
    ret[0] = a1;

    for(int i = 1;i<n;++i){
        ret[i] = (k*ret[i-1] + b) % m;
    }
    return ret;
}




/// ����� ������� ... https://neerc.ifmo.ru/wiki/index.php?title=%D0%91%D1%8B%D1%81%D1%82%D1%80%D1%8B%D0%B9_%D0%BF%D0%BE%D0%B8%D1%81%D0%BA_%D0%BD%D0%B0%D0%B8%D0%B1%D0%BE%D0%BB%D1%8C%D1%88%D0%B5%D0%B9_%D0%B2%D0%BE%D0%B7%D1%80%D0%B0%D1%81%D1%82%D0%B0%D1%8E%D1%89%D0%B5%D0%B9_%D0%BF%D0%BE%D0%B4%D0%BF%D0%BE%D1%81%D0%BB%D0%B5%D0%B4%D0%BE%D0%B2%D0%B0%D1%82%D0%B5%D0%BB%D1%8C%D0%BD%D0%BE%D1%81%D1%82%D0%B8

/// from wiki https://ru.wikipedia.org/wiki/%D0%97%D0%B0%D0%B4%D0%B0%D1%87%D0%B0_%D0%BF%D0%BE%D0%B8%D1%81%D0%BA%D0%B0_%D0%BD%D0%B0%D0%B8%D0%B1%D0%BE%D0%BB%D1%8C%D1%88%D0%B5%D0%B9_%D1%83%D0%B2%D0%B5%D0%BB%D0%B8%D1%87%D0%B8%D0%B2%D0%B0%D1%8E%D1%89%D0%B5%D0%B9%D1%81%D1%8F_%D0%BF%D0%BE%D0%B4%D0%BF%D0%BE%D1%81%D0%BB%D0%B5%D0%B4%D0%BE%D0%B2%D0%B0%D1%82%D0%B5%D0%BB%D1%8C%D0%BD%D0%BE%D1%81%D1%82%D0%B8
template <typename T>
vector<T> NVP(vector<T> A){

    int N = A.size();

    /*
    int n = A.size();

    vector<int> d;
    d.resize(n+1);
    d[0] = -100000;
    for (int i=1; i<=n; ++i)
        d[i] = 1000000;

    for (int i=0; i<n; i++) {
        int j = int (upper_bound (d.begin(), d.end(), A[i]) - d.begin());
        if (d[j-1] < A[i] && A[i] < d[j])
            d[j] = A[i];
    }

    return d;
    */


    vector<T> P(N);
    vector<T> M(N + 1);
    int L = 0;
    for (int i=0; i< N;i++){
      int lo = 1;
      int hi = L;
      while (lo <= hi){
        int mid = ((lo+hi + 1)/2);
        if (A[M[mid]] < A[i]){
          lo = mid+1;
        }else{
          hi = mid-1;
        }
      }
      int newL = lo;
      P[i] = M[newL-1];
      M[newL] = i;
      if (newL > L){
        L = newL;
      }
    }
    vector<T> S(L);
    int k = M[L];
    for (int i= L-1;i>-1;i--){
      S[i] = A[k];
      k = P[k];
    }
    return S;

}




#include <vector>
/// REF : http://web.mit.edu/~ecprice/acm/acm08/notebook.html#file12

/// USAGE :
/// v and u - are vector<int>
/// FFT::convolution(v, u);

#include <vector>

#include <cmath>
#include <iostream>
using namespace std;

#define VI vector<long long>
#define int long long
#define double long double

double PI = acos(0) * 2;

class complex
{
public:
	double a, b;
	complex() {a = 0.0; b = 0.0;}
	complex(double na, double nb) {a = na; b = nb;}
	const complex operator+(const complex &c) const
		{return complex(a + c.a, b + c.b);}
	const complex operator-(const complex &c) const
		{return complex(a - c.a, b - c.b);}
	const complex operator*(const complex &c) const
		{return complex(a*c.a - b*c.b, a*c.b + b*c.a);}
	double magnitude() {return sqrt(a*a+b*b);}
	void print() {printf("(%.3f %.3f)\n", a, b);}
};

class FFT
{
public:
	vector<complex> data;
	vector<complex> roots;
	VI rev;
	int s, n;

	void setSize(int ns)
	{
		s = ns;
		n = (1 << s);
		int i, j;
		rev = VI(n);
		data = vector<complex> (n);
		roots = vector<complex> (n+1);
		for (i = 0; i < n; i++)
			for (j = 0; j < s; j++)
				if ((i & (1 << j)) != 0)
					rev[i] += (1 << (s-j-1));
		roots[0] = complex(1, 0);
		complex mult = complex(cos(2*PI/n), sin(2*PI/n));
		for (i = 1; i <= n; i++)
			roots[i] = roots[i-1] * mult;
	}

	void bitReverse(vector<complex> &array)
	{
		vector<complex> temp(n);
		int i;
		for (i = 0; i < n; i++)
			temp[i] = array[rev[i]];
		for (i = 0; i < n; i++)
			array[i] = temp[i];
	}

	void transform(bool inverse = false)
	{
		bitReverse(data);
		int i, j, k;
		for (i = 1; i <= s; i++) {
			int m = (1 << i), md2 = m / 2;
			int start = 0, increment = (1 << (s-i));
			if (inverse) {
				start = n;
				increment *= -1;
			}
			complex t, u;
			for (k = 0; k < n; k += m) {
				int index = start;
				for (j = k; j < md2+k; j++) {
					t = roots[index] * data[j+md2];
					index += increment;
					data[j+md2] = data[j] - t;
					data[j] = data[j] + t;
				}
			}
		}
		if (inverse)
			for (i = 0; i < n; i++) {
				data[i].a /= n;
				data[i].b /= n;
			}
	}
    template <typename T>
	static VI convolution(const vector<T> &a, const vector<T> &b)
	{
		int alen = a.size(), blen = b.size();
		int resn = alen + blen - 1;	// size of the resulting array
		int s = 0, i;
		while ((1 << s) < resn) s++;	// n = 2^s
		int n = 1 << s;	// round up the the nearest power of two

		FFT pga, pgb;
		pga.setSize(s);	// fill and transform first array
		for (i = 0; i < alen; i++) pga.data[i] = complex(a[i], 0);
		for (i = alen; i < n; i++)	pga.data[i] = complex(0, 0);
		pga.transform();

		pgb.setSize(s);	// fill and transform second array
		for (i = 0; i < blen; i++)	pgb.data[i] = complex(b[i], 0);
		for (i = blen; i < n; i++)	pgb.data[i] = complex(0, 0);
		pgb.transform();

		for (i = 0; i < n; i++)	pga.data[i] = pga.data[i] * pgb.data[i];
		pga.transform(true);	// inverse transform
		VI result = VI (resn);	// round to nearest integer
		for (i = 0; i < resn; i++)	result[i] = (int) (pga.data[i].a + 0.5);

		int actualSize = resn - 1;	// find proper size of array
		while (result[actualSize] == 0)
			actualSize--;
		if (actualSize < 0) actualSize = 0;
		result.resize(actualSize+1);
		return result;
	}
};




#undef VI




#define debug_delenie false

#define int long long

#define char_zero '0'

int intlog(double base, double x) {
    return (int)(log(x) / log(base));
}
/// 9 223 372 036 854 775 807
/// 2147483647
const int INT_MAXI = 9223372036854775807;

int inline intSqrt(int arg){
    return (int)(sqrt(arg));
}

char FromIntToChar(int a){

    if (a >= 0 && a <= 10){
        return (a + '0');
    }


    return (a - 10) + 'A';

}

int FromCharToInt(char a){
    if (a >= '0' && a <= '9'){
        return a - '0';
    }


    return (a - 'A')+10;

}

const int zero = 0;

#define default_base 10

#define container_stack 6 /// 6

#define total_base 1000000 /// 1000000

#define sqrt_of_total_base 1000 /// 1000

/// ���������� ������ ������� �����, ����� ������ ������������ �����.
class BigInt{
private:
    void _remove_leading_zeros();
    bool _is_negative = false;



public:
    /// 1234 === [4,3,2,1]
    vector<int> data;
    int Base = -1;

    int rsz = -1;

    void operator=(const BigInt &another){
        data = another.data;
        Base = another.Base;
    }

    BigInt(){data = {0};Base = total_base;}

    BigInt(long long num, int Base_ = total_base){
        Base = Base_;
        while(num != 0){
            data.push_back(num % Base_);
            num /= Base;
        }

        if (data.size() == 0){
            data.push_back(0);
        }
    }

    /// ��������� ��������� ���� ������������� ����� (0 => ������ ������, 1 => �����, 2 => ���� ������)
    short inline compare(const BigInt &another){
        if (another.data.size() != data.size()){
            return (data.size() > another.data.size()) << 1;
        }

        int sz = data.size();

        for (int i = 0;i<sz;i++){
            int p = sz - i - 1;
            if (data[p] != another.data[p]){
                return (data[p] > another.data[p]) << 1;
            }
        }

        return 1;
    }

    friend bool operator <(const BigInt&, const BigInt&);
    friend bool operator ==(const BigInt&, const BigInt&);
	friend bool operator !=(const BigInt&, const BigInt&);
	friend bool operator <=(const BigInt&, const BigInt&);
	friend bool operator >(const BigInt&, const BigInt&);
	friend bool operator >=(const BigInt&, const BigInt&);

    /// ��������� �������� ���� ������������� �����
    void inline _add(const BigInt &another){

        size_t extra_size = 1;

        size_t an_sz = another.data.size();

        if (an_sz > data.size()){
            extra_size = an_sz - data.size() + 1;
        }

        for(size_t i = 0;i < extra_size; i++){
            data.push_back(zero);
        }
        /// ��������� ��������� ������, ����� ���� ����� ��� ����� ��������� �����(aka �������)

        for(size_t i = 0; i < an_sz;i++){
            data[i] += another.data[i];
            if (data[i] >= Base){
                data[i] -= Base;
                data[i+1]++;
            }
        }

        while(data[an_sz] >= Base){
            data[an_sz] -= Base;
            an_sz++;
            data[an_sz]++;
        }



        _remove_leading_zeros();
    }

    void operator +=(const BigInt& right) {
        if (_is_negative == right._is_negative){
            _add(right);
        }else{
            _is_negative = !_is_negative;
            *this -= right;
        }
    }

    const BigInt operator +() const;
    const BigInt operator -() const;


    /// ������ �������� (� ������ ������ � �������)
    void operator-=(BigInt another){
        short comp_ = !(compare(another));
        if ( comp_){
            swap(another,*this);
            _is_negative = !_is_negative;
        }


        if ( (_is_negative == another._is_negative) ^ (comp_) ) {
            // ��������� �� �����
            _subtract(another);
        }else{
            // ������ �� �����.
            _add(another);
        }

    }



    /// ��������� ��������� ���� ������������� ����� (��������, ���� ������ ������ �������)
    void _subtract(const BigInt &another){

        size_t an_sz = another.data.size();

        for(size_t i = 0; i < an_sz;i++){
            data[i] -= another.data[i];
            if (data[i] < zero){
                data[i] += Base;
                data[i+1]--;
            }
        }

        while(data[an_sz] < 0){
            data[an_sz] += Base;
            an_sz++;
            data[an_sz]--;
        }



        _remove_leading_zeros();
    }

    /// ��������� ��������� ����� �� ���������( �����, ��� (Base-1)*number < INT_MAX )
    void inline _mult(const int number){

        if (number == 0){data = {0}; return;}

        size_t sz = data.size();
        for(size_t i = 0;i < sz; ++i ){
            data[i] *= number;
        }
        --sz;
        for(size_t i = 0;i < sz; ++i){
            data[i+1] += data[i] / Base;
            data[i] %= Base;
        }

        while (data[sz] >= Base){
            data.push_back(data[sz] / Base);
            data[sz] %= Base;
            ++sz;
        }

    }

    void operator *=(int);
    void operator /=(int);
    friend const BigInt operator *(const BigInt&, const BigInt&);
    friend const BigInt operator *(BigInt, int);
    friend const BigInt operator /(BigInt, BigInt);
    const BigInt operator /(int);
    void operator *=(const BigInt&);

    //BigInt& operator *=(const big_integer&);

    BigInt reqKar(int l, int r, BigInt& another){
        /*
        int n = MakeEqualLength(X, Y);

        if (n == 1) return std::to_string(std::stoi(Y) * std::stoi(X));

        int fh = n / 2;   // First half of string
        int sh = (n - fh); // Second half of string, ceil(n/2)

        // Find the first half and second half of first string.
        std::string X1 = X.substr(0, fh);    // high half
        std::string X0 = X.substr(fh, sh);   // low half

        // Find the first half and second half of second string
        std::string Y1 = Y.substr(0, fh);
        std::string Y0 = Y.substr(fh, sh);

        // Recursively calculate the three products of inputs of size n/2
        // Z0 = X0 * Y0
        std::string Z0 = MultiplyRecur(X0, Y0);
        // Z2 = X1 * Y1
        std::string Z2 = MultiplyRecur(X1, Y1);
        // Z1 = (X0 + X1)(Y0 + Y1) - Z0 - Z2
        std::string Z1 = MultiplyRecur(Add(X0, X1), Add(Y0, Y1));
        Z1 = Subtraction(Z1, Add(Z0, Z2));

        // return added string version
        // Z = Z2 * (10^(low half digits * 2)) + Z1 * (10^(low half digit)) + Z0
        return Add(Add(Shift(Z2, sh*2), Z0), Shift(Z1, sh));
        */
        return BigInt(12);
    }

    void _kar_mult(const BigInt& another, BigInt &write_to){



    }

    /// �������� ����� � ����������� �������
    void inline _pow(int pow_){

        BigInt cp = (*this);
        data = {1};
        for (; pow_; pow_ >>= 1) {
            if (pow_ & 1)
                (*this) *= cp;
            cp *= cp;
        }


    }

    /// �������� ����� � ����������� �������, �������� ����
    void inline _pow(int pow_,BigInt &write_to, int truncated_digits){

        BigInt cp = (*this);
        data = {1};
        for (; pow_; pow_ >>= 1) {
            if (pow_ & 1)
                (*this) *= cp;
            cp *= cp;



            if (cp.data.size() > truncated_digits){cp.data.resize(truncated_digits);cp._remove_leading_zeros();}
            if (data.size() > truncated_digits){data.resize(truncated_digits);_remove_leading_zeros();}
        }


    }

    /// ����� ����� �� ��������
    int inline _divide(int digit_, BigInt &to_write){
        to_write.data = {};
        to_write.Base = Base;
        int Carret = 0;
        int sz = data.size() - 1;
        for(int i = sz;i > -1; --i){
            Carret *= Base;
            Carret += data[i];
            to_write.data.push_back(Carret / digit_);
            Carret %= digit_;
        }



        reverse(to_write.data.begin(),to_write.data.end());

        to_write._remove_leading_zeros();

        return Carret;

    }

    void inline Interate(BigInt &b, int precision)
    {

        // 2 * X(i)
        BigInt minus_ = *this;
        minus_ *= minus_;
        minus_ *= b;

        minus_._ShiftR(precision);

        _mult(2);

        _subtract(minus_);
        /// this - 2*this*this*b*SHIFT_R

    }

    /// �� ������� ����� ����� � int ����� �� �����������


    const BigInt Reciprocal(int precision);

    void inline _DivUnrefined( BigInt &divisor, size_t precision, BigInt &write_to)
    {

        write_to = divisor.Reciprocal(precision) * (*this);
    }

    void inline _DivInt( BigInt &divisor, BigInt &write_to)
    {

        if ( (data[data.size() - 1] == 0) || (divisor.data.size() > data.size()) ){write_to = 0; return;}
        size_t precision = data.size() + 4;
        _DivUnrefined(divisor,precision,write_to);
        write_to._ShiftR(precision);
        if (write_to.data.size() == 0){
            write_to.data.push_back(0);
        }
    }

    void inline _DivIntRem( BigInt &divisor, BigInt &write_to, BigInt &rem_write_to)
    {
        _DivInt(divisor,write_to);
        rem_write_to = *this;
        BigInt minus_ = write_to;
        minus_ *= divisor;
        rem_write_to._subtract(minus_);
    }

    /// � ��������� �������, ���� ����� - ��� �� 1 ������, ��� ������ �������, �� ������� ����� ����� �� ���� ������
    /// �������� 24 -> 5, 48 -> 7, 35 -> 6
    /// safe_sqrt �������� �����
    void inline _sqrt()
    {
        if (data.size() == 1){*this = (intSqrt(data[0])); return;}
        BigInt copy_ = (*this);



        int sz = data.size();
        int rsz = (sz-1)*container_stack + intlog(default_base,data[sz - 1]) + 1;
        //cout << sz <<" rsz : " << rsz << endl;
        data.clear();



        data.push_back (intSqrt(data[sz-1]) * ((sz%2) ? 1 : sqrt_of_total_base) );

        _appendZeros((sz - 1) / 2 );

        ///cout << *this << endl;

        // Do the interation to fullfil the precision
        int end{  log2(sz) + 6 };

        //cout << *this << endl;

        BigInt smth;
        BigInt tmp;

        for (int i = 0; i < end; i++)
        {

            // x(i) * 10^precision + a * 10^(2*precision) / x(i)
            copy_._DivInt(*this, smth); /// double the precision here (of normal)


            _add(smth);
            tmp = *this;
            tmp._divide(2,*this);
            ///cout << "Cycle "<< i << " " << (*this) << endl;
        }





        ///_ShiftR(1);


    }



    void inline safe_sqrt(){

        BigInt orig = *this;

        _sqrt();

        BigInt cp = *this;
        cp *= cp;
        if ( orig < cp){
            *this -= 1;
        }
    }


    /// ���������� "��������" � write_to, ������� � ������� ��������

    /// ������
    /// write_to = [4,3,2,1](1234), this=[8,7,6,5](5678), length = 2

    /// => write_to = [4,3,2,1,6,5](561234)
    void _subInt(int length, BigInt &write_to){
        int sz = data.size();
        for(int i = 0;i<length;i++){
            write_to.data.push_back(data[i + sz -length]);
        }
    }

    /// ������� � ����� ����� length ����
    /// [5,4,3,2,1](12345) (length=3)-> [2,1](12)
    void inline _ShiftR(int length){

        data.erase(data.begin(), data.begin() + length);

    }

    /// [5,4,3,2,1](12345) (length=3)-> [0,0,0,5,4,3,2,1](12345000)
    /// ������� ��������. ������ ����� ������������
    void inline _appendZeros(int length){
        vector<int> v1(length);
        vector<int> tmp = data;
        data.clear();
        std::merge(v1.begin(), v1.end(), tmp.begin(), tmp.end(), std::back_inserter(data));
    }




    friend istream& operator>>(istream& in, BigInt &bi) {



        if (bi.Base == -1){
            bi.Base = total_base;
        }

        string stream_;
        in >> stream_;

        int sz = stream_.size();
        bi.rsz = sz;
        sz = (sz+container_stack-1)/container_stack; /// /= �� ceil
        bi.data.resize(sz);

        int Carret;

        for(int i = 0;i<sz;++i){
            Carret = 0;
            for(int j = 0; j < container_stack;++j){
                int index = bi.rsz - (i+1)*container_stack + j;
                if (index > -1){
                    Carret *= default_base;
                    Carret += FromCharToInt(stream_[index]);
                }
            }

            bi.data[i] = Carret;
        }

        bi._remove_leading_zeros();

        return in;

    }

    friend ostream& operator<<(ostream &in, const BigInt &bi) {

        if ( (bi.data.size() == 1) && (bi.data[0] == 0)){
            in << FromIntToChar(0);
            return in;
        }

        int sz = bi.data.size();
        if (bi._is_negative){in << '-';}
        int Carret;
        string buff = "";
        for(int i = 0;i<sz;++i){
            Carret = bi.data[i];
            for(int j = 0; j < container_stack;++j){
                buff += FromIntToChar(Carret % default_base);
                Carret /= default_base;
            }

        }

        while(buff.back() == char_zero){
            buff.pop_back();
        }

        reverse(buff.begin(),buff.end());

        in << buff;
        return in;
    }

    /*
    void Stabilize(){
        for(int i=SIZEE_-1;i>-1;i--){
            OneNumTransform(i);
        }
    }
    */

};

void get_sqrt(BigInt &take_from, BigInt &to_write){

    to_write = 0;
    int prefix = 2;
    int sz = take_from.data.size();

    int Carret = take_from.data.back();

    vector<int> reverse_ans;

    if (sz % 2 == 0){
        Carret *= take_from.Base;
        Carret += take_from.data[sz - 2];
        prefix++;
    }

    int iSqrt_ = intSqrt(Carret);
    reverse_ans.push_back(iSqrt_);
    Carret = Carret - iSqrt_*iSqrt_;


    cout << "Carret : "<< Carret << endl;


    for (int i = sz-prefix;i>=0;i-=2)
    {

        Carret *= take_from.Base;
        Carret += take_from.data[i];

        Carret *= take_from.Base;
        Carret += take_from.data[i - 1];


        iSqrt_ = intSqrt(Carret);
        cout << iSqrt_ << endl;
        cout << "Carret : "<< Carret << endl;
        reverse_ans.push_back(iSqrt_);
        Carret -= iSqrt_*iSqrt_;
        cout << "Carret : "<< Carret << endl;
    }



}


///

const BigInt operator +(BigInt left, const BigInt& right) {
    left += right;
    return left;
}

const BigInt operator -(BigInt left, const BigInt& right) {
    left -= right;
    return left;
}

void BigInt::operator *=(int number) {
    if (number == 0){data = {0}; return;}
    if (number < 0){_is_negative = !_is_negative; number = abs(number);}
    size_t sz = data.size();
    for(size_t i = 0;i < sz; ++i ){
        data[i] *= number;
    }
    --sz;
    for(size_t i = 0;i < sz; ++i){
        data[i+1] += data[i] / Base;
        data[i] %= Base;
    }

    while (data[sz] >= Base){
        data.push_back(data[sz] / Base);
        data[sz] %= Base;
        ++sz;
    }
}

const BigInt BigInt::operator / (int number) {
    BigInt write_to;
    write_to.data = {};
    write_to.Base = Base;
    int Carret = 0;
    int sz = data.size() - 1;
    for(int i = sz;i > -1; --i){
        Carret *= Base;
        Carret += data[i];
        write_to.data.push_back(Carret / number);
        Carret %= number;
    }



    reverse(write_to.data.begin(),write_to.data.end());

    write_to._remove_leading_zeros();

    return write_to;

    ///
    /// ������� <- return Carret;
}

const BigInt operator *(const BigInt& left, const BigInt& right) {
    BigInt ret;
    ret._is_negative = left._is_negative != right._is_negative;
    ret.Base = left.Base;
    ret.data = FFT::convolution(left.data, right.data);


    size_t sz = ret.data.size() - 1;
    for(size_t i = 0;i < sz; ++i ){
        ret.data[i + 1] += ret.data[i] / ret.Base;
        ret.data[i] %= ret.Base;
    }


    while (ret.data[sz] >= ret.Base){
        ret.data.push_back(ret.data[sz] / ret.Base);
        ret.data[sz] %= ret.Base;
        ++sz;
    }

    return ret;
}

// ��������� ������� ����� �� ���������
void BigInt::operator *=(const BigInt& value) {
    *this = (*this * value);
}

const BigInt operator /(BigInt left, BigInt right)
{

    if ( (left.data[left.data.size() - 1] == 0) || (right.data.size() > left.data.size()) ){return 0;}
    size_t precision = left.data.size() + 4;
    left._DivUnrefined(right,precision,left);
    left._ShiftR(precision);
    if (left.data.size() == 0){
        left.data.push_back(0);
    }
    return left;
}




const BigInt BigInt::Reciprocal(int precision)
{
    BigInt write_to;

    int mx_sz = intlog(Base, INT_MAXI);
    int sz = data.size();
    size_t len{ (sz > (mx_sz - 1)) ? (mx_sz) : sz };

    int divisor = 0;





    for(int i = 0;i<len;i++){
        divisor *= write_to.Base;
        divisor += data[sz - i - 1];
    }

    int dividend = 1;
    for(int i = 0;i<len;++i){
        dividend *= Base;
    }


    ///cout << dividend << endl << divisor << endl;
    // Extra condition for initial guess is: x(i) < 2R/b
    write_to = dividend / divisor;



    write_to._appendZeros(precision - sz);

    ///cout << "TestPut " << write_to << endl;

    // Do the interation to fullfil the precision
    int end{ (int)(std::log2(precision)) + 4 };
    for (int i = 0; i < end; i++)
    {
        write_to.Interate(*this, precision);
        ///cout << "InCycle " << write_to << endl;
    }

    return write_to;
}


// ���������, �������� �� ����� ������� ������ �������
bool operator <(const BigInt& left, const BigInt& right) {

    if (left._is_negative != right._is_negative){
        return left._is_negative;
    }

	if (left.data.size() != right.data.size()){
        return (left.data.size() < right.data.size()) ^ (left._is_negative);
    }

    int sz = left.data.size();

    for (int i = 0;i<sz;i++){
        int p = sz - i - 1;
        if (left.data[p] != right.data[p]){
            return (left.data[p] < right.data[p]) ^ (left._is_negative);
        }
    }

    // ����� �����
    return 0;
}

// ���������, �������� �� ����� ������� ������ �������
bool operator !=(const BigInt& left, const BigInt& right) {

    if (left._is_negative != right._is_negative){
        return 1;
    }

	if (left.data.size() != right.data.size()){
        return 1;
    }

    int sz = left.data.size();

    for (int i = 0;i<sz;i++){
        int p = sz - i - 1;
        if (left.data[p] != right.data[p]){
            return 1;
        }
    }

    // ����� �����
    return 0;
}


void BigInt::_remove_leading_zeros() {
	while (this->data.size() > 1 && this->data.back() == 0) {
		this->data.pop_back();
	}

	if (this->data.size() == 1 && this->data[0] == 0) this->_is_negative = false;
}


#undef int


#include <fstream>


template <typename T>
T sqrt(T n) {

  T x = 10;
  ///x = x.pow(a.length() / 2 + 1); <- initial guess
  T last = 0;
  int iter = 0;
  while (last != x) {
    last = x;
    x = (x + n / x) / 2;
    cout << last - x << endl;
    ++iter;
  }
  cout << iter << endl;
  return x;
}

using namespace std;

int main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");
     
    BigInt a = 1000;
    BigInt b = 999;
    BigInt c,d;


    cin >> a;

    b = a;
    //a._sqrt();
    a = sqrt(a);


    cout << a; //endl << d;

    a *= a;
    b._subtract(a);
    cout << endl << b;


    ///cout << a << endl;

    //cout << r << endl;


    ///cout << counter << endl;
    return 0;
}


