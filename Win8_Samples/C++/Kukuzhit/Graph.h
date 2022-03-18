#include <iostream>
#include <set>
using namespace std;

#define int long long

///==========
///Реализация "Идеального" Графа через определение "Дуг", как динамический массив Сетов. Реализация может быть медленной, при ОГРОМНОМ количестве точек (1 миллион+)
///Автор: Александр Кулешов (aka Dorty_Schmorty aka DortyTheGreat aka Тесла).
///Начало создания: 04.09.2021, последнее изменение было сделано в 29.09.2021
///==========

class Node{
public:
    long long value; /// Значение Верщины (например, цена за посещение вершины)
    long long SearchedDistance; /// При Вызове поисков по графу в эту переменную заносим растояние от стартовой точки до этой.
    long long used; /// Нужна для востановления пути. Или для поиска непересекающихся вершин в графе (aka Поиск количества компонент связности)
    /// 0 - вершину не посещали при поиске
    /// 1 - Вершина есть источник поиска (из неё искали)
    /// 2 - Вершина есть близлизжайщий сосед к источнику
    /// 3 - Вершина есть близлизжайщий сосед через ещё одну вершину (ЗАМЕТЬТЕ, что хоть и вершина может быть соседом с источником, но может иметь значение 3,
    /// если путь в источник длиннее, чем путь в другого соседа, а потом источник (aka distance(THIS-> 2 -> 1) < distance(THIS -> 1) ))
    /// 4 - Вершина есть близлизжайщий сосед через ещё 2 вершины
    /// 5 - Вершина есть близлизжайщий сосед через ещё 3 вершины, 6 через 4, 7 через 5, 8 через 6 ... и т.д.
};

class Arc{
public:
    long long value; /// Значение дуги (например, расстояние)
    long long direction; /// Место назначения этой дуги
    /// т.к. оригинально Дуга храниться в массиве из сэтов "Arcs", то
    /// Arcs[0] = [(311, 5),(43, 4)] - Дуга из точки "0" в точку "5". Длина дуги = 311, Дуга из точки "0" в точку "4". Длина дуги = 43

    bool operator<(const Arc& other) const {
        return (direction < other.direction);
    }

};

class Graph{
public:
    int OutPutFormat=0; /// В некоторых задачах просят выводить начиная с единицы
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


        for(int i = 0; i < Size; i++ ){
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

        int req; // 1 - есть вход, 0 - нет
        for(int i = 0; i < Size; i++){
            for(int j = 0; j < Size; j++){
                cin >> req;
                if(req){
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
        for(int cou = 0; cou < Size; cou++){


            for (Arc i : Arcs[cou]){
                if (!IsThereArc(i.direction,cou)){
                    InsertNewArc(i.direction,i.value,cou);
                }
            }
        }
    }

    void Requr_BFS(int Uses, int distanto,int dot){
        /// Зарезервированная функция для Мульти-Дейкстры
        if( distanto >= Nodes[dot].SearchedDistance ){return;}

        Nodes[dot].used = Uses;
        Nodes[dot].SearchedDistance = distanto;

        for (Arc i : Arcs[dot]){

            Requr_BFS(Uses+1,distanto+i.value,i.direction);
        }



    }

    void Dijkstra_Search(int start_point){
        /// Зпускает Мульти-Поиск по графу (по сути тот же Дейкстра-Поиск)
        for(int i=0;i<Size;i++){
            Nodes[i].SearchedDistance=pseudo_inf;

        }
        Requr_BFS(1,0,start_point);
    }

    void gSort(int i, vector<int>& res, int c,int &flag) {
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

    pair<vector<int>,int> StartTopSort(){

        for(int i =0;i<Size;i++){
            Nodes[i].value = 0;
        }
        vector<int> result;
        int flag = 0;
        for (int i = 0; i < Size; i++) {
            if (!Nodes[i].value) {
                gSort(i, result, i + 1,flag);
            }
        }
        return make_pair( result,flag);

    }

    void ReverseGraph(){
        Graph temp;
        temp.init(Size);

        for(int cou = 0; cou < Size; cou++){


            for (Arc i : Arcs[cou]){

                temp.InsertNewArc(i.direction,i.value,cou);

            }
        }

        Arcs = temp.Arcs;
    }

    Graph Get_Condensated_Graph(){

            ///ВНИМАНИЕ!
            ///НА ДАННЫЙ МОМЕНТ ГРАФ, ПРИ КОНДЕНСАЦИИ ЗАБЫВАЕТ ПРО ТАКИЕ ЗНАЧЕНИЕ, как distance у Арок, а также почти все даные с точек стираются
            ///

          Graph G2;

          G2 = *this;

          G2.ReverseGraph();

          pair<vector<int>,int> ABOOBA = StartTopSort();
          vector<int> res = ABOOBA.first;
            int flag_temp = ABOOBA.second;

          reverse(res.begin(), res.end());

          vector<int> _res;


            for(int i =0;i<Size;i++){
                G2.Nodes[i].value = 0;
            }

          for(auto val: res) {
            //cout << val << endl;
            G2.gSort(val, _res, val + 1,flag_temp);
          }
          int counter = 0;
          set<pair<int, int>> diff_col;
          for (int i = 0; i < Size; ++i) {
            for (auto counter_: G2.Arcs[i]) {
                int v = counter_.direction;
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
            int * Achiles_array = new int [Size];int achiles_cou = 0;

            const int PLACEHOLDER = -10;
            for(int i =0;i<Size;i++){
                Achiles_array[i] = PLACEHOLDER;
            }

            for (auto pseudo_arc : diff_col){
                    //cout << "WARN" << endl;
                int first = pseudo_arc.first - 1;
                int second = pseudo_arc.second - 1;

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

            for(int i =0;i<Size;i++){

                //cout << i<< " " << (Nodes[i].value-1) << endl;
                if ( ((i) == (Nodes[i].value-1)) ){
                    if (Achiles_array[i] == PLACEHOLDER){
                        achiles_cou++;
                    }
                }
            }

            Condensated_Graph.Size = achiles_cou;

          return Condensated_Graph;
    }


    void ItterateAllNode_sArcs(long long Node, bool WriteValue, bool WriteDirection, bool WriteEndl, string NullTxt){

        /// NullTxt - что выводить, если вершин нет
        int Nulled = 1;
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

    long long GetLongestBranch(int midPoint){
        /// Получает Длину(как количество Арок) от точки midPoint в графе до самой дальней точки(как в неориентированном графе)
        DisorientGraph();
        Dijkstra_Search(midPoint);

        int longest = -1;
        int INDEX = -1;
        for(int i =0;i<Size;i++){
                int that = Nodes[i].used-1;
                if (that > longest){
                    longest = that;
                    INDEX = i;
                }

        }
        return longest;
    }

    long long GetDiameter(int midPoint){
        /// Получает Длину(как количество Арок) Диаметра в графе(как в неориентированном графе)
        DisorientGraph();
        Dijkstra_Search(midPoint);

        int longest = -1;
        int INDEX = -1;
        for(int i =0;i<Size;i++){
                int that = Nodes[i].used-1;
                if (that > longest){
                    longest = that;
                    INDEX = i;
                }

        }



        Dijkstra_Search(INDEX);

        int longestPAIR = -1;

        for(int i =0;i<Size;i++){
                int that = Nodes[i].used-1;
                if (that > longestPAIR){
                   longestPAIR = that;
                }

        }

        return longestPAIR;
    }

};




