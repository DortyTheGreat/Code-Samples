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


        if (value == other.value)
            if (origin == other.origin)
                return direction < other.direction;
            else
                return origin < other.origin;
        return value < other.value;
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

    void ReadAsSquareMatrix(){
        /// Читает Граф, как двумерную матрицу. Читает n, затем n^2 чисел - матрица смежности. Если 0 - нет соединеня, если не 0 - даёт расстояние {INPUT} в Арку


        cin >> Size;

        init(Size);

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




