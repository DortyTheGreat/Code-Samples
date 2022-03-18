#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

///
/// Заброшено по причине неработоспособности дерева
///
///
const int idSpace = 1000;
const int rowSpace = 20;
const int depthSpace = 10;
const int CellSize = 5000; ///Место на всё
string fillSpaces(string str, int spaces){
    while(str.size() != (spaces)){
            str += " ";
        }
        return str;
}


bool StringCompare(string T1, string T2){
if (T1.size() != T2.size()){
    return T1.size() < T2.size();
}

return T1 < T2;
}

template <typename T>
  std::string NumberToString ( T Number )
  {
     std::ostringstream ss;
     ss << Number;
     return ss.str();
  }

class Node{
public:
    string id;
    string data;
    long long l_row=-1,r_row=-1, parent_row = -1;
    long long l_depth = 0, r_depth = 0;

    string GetString(){
        string temp = fillSpaces(id,idSpace) + fillSpaces(NumberToString(l_row),rowSpace) +fillSpaces(NumberToString(r_row),rowSpace) + \
            fillSpaces(NumberToString(parent_row),rowSpace) + fillSpaces(NumberToString(l_depth),depthSpace) + fillSpaces(NumberToString(r_depth),depthSpace) + data;

        temp = fillSpaces(temp,CellSize-2);
        return temp;

    }
};

class DataBase{
public:

    fstream DataBaseFILESTREAM;
    fstream UtilFILESTREAM;

    long long root_row = -1;

     void init(){

        DataBaseFILESTREAM.open ("DataBase.txt", fstream::in | fstream::out);
        UtilFILESTREAM.open("DataBaseUtil.txt", fstream::in | fstream::out);
        UtilFILESTREAM.seekg(0);
        UtilFILESTREAM >> root_row;
    }

    int GetSizeOfFile(){
        // get length of file:
        DataBaseFILESTREAM.seekg (0, DataBaseFILESTREAM.end);
        int length = DataBaseFILESTREAM.tellg();
        DataBaseFILESTREAM.seekg (0, DataBaseFILESTREAM.beg);


        return length  / (CellSize);
    }

    void insert_here(Node ic, int row){
        DataBaseFILESTREAM.seekp((CellSize) * row);
        DataBaseFILESTREAM << ic.GetString() << endl;
    }

    void modify_string_here(string info, int row,int spacesSkip){
        DataBaseFILESTREAM.seekp((CellSize) * row + spacesSkip);
        DataBaseFILESTREAM << info;
    }

    string get_this_string_id(int row){
        DataBaseFILESTREAM.seekg((CellSize) * row);
        string temp;
        getline(DataBaseFILESTREAM,temp);
        //DataBaseFILESTREAM >> temp;
        return temp;
    }

    Node get_this_node(int row, bool DoReadData){
        DataBaseFILESTREAM.seekg((CellSize) * row);
        Node temp;
        DataBaseFILESTREAM >> temp.id;
        DataBaseFILESTREAM >> temp.l_row;
        DataBaseFILESTREAM >> temp.r_row;
        DataBaseFILESTREAM >> temp.parent_row;
        DataBaseFILESTREAM >> temp.l_depth;
        DataBaseFILESTREAM >> temp.r_depth;
        if (DoReadData){
            DataBaseFILESTREAM >> temp.data;
        }
        //getline(DataBaseFILESTREAM,temp.data);
        //DataBaseFILESTREAM >> temp;
        return temp;
    }

    int IsThisRorLNode(int row_of_this_node){
        /// Возвращает 1, если r, ноль, если l. Возвращает -1, если это корень
        Node nd = get_this_node(row_of_this_node,0);

        if (nd.parent_row == -1){
            return -1;
        }

        Node parent_node = get_this_node(nd.parent_row,0);

        if (parent_node.l_row == row_of_this_node){
            return 0;
        }

        return 1;

        /// ВНИМАНИЕ! ЭТУ ФУНКЦИЮ НАДО УСКОРИТЬ! из ноды nd нужно только parent_row, а из ноды parent_row нужно только l_row
    }

    int findElement(string id){
        /// Возвращает номер строки, на котором содержится ячейка элемента. Если элемента не существует возвращает отрицательное-1 значение ячейки ближе всего к которой находится наш элемент\\
        Т.е. Например, если функция возвращает -3, то ноды нет и её следует привязать к ноде находящейся на 2ой строчке.\\
        Если значение 4 - то нода есть, находится на 4ой строчке.\\
        ВАЖНО! Нумерация строк идёт с нуля, а не единицы

        int this_row = root_row;
        int last_row = -1;

        while(this_row != -1){
                cout << "Searching...: "<< this_row << endl;
            Node RootNode  = get_this_node(this_row,0);
            last_row = this_row;

            if (id == RootNode.id){
                /// Нашли!
                return this_row;
            }

            if (StringCompare(id,RootNode.id)){
                /// Айди которое мы ищем лежит ниже(левее),
                this_row = RootNode.l_row; continue;
            }

            ///ПРАВЕЕ!
            this_row = RootNode.r_row; continue;


        }

        return ((-1) * last_row - 1);

    }

    void UpdateRootNodeInfo(long long root_row_){
        UtilFILESTREAM.seekp(0);
        UtilFILESTREAM << fillSpaces(NumberToString(root_row_),rowSpace);
        root_row = root_row_;
    }

    bool Throw_Over(Node current_parent_node, int current_parent_node_row, Node current_node,int LorR, int Depth){
        /// Пытается "перекинуть", если вышло, то возвращает 1, если не вышло, то возвращает 0
        /// Зарезервированно, используется в connect

        cout << "TH_DEPTH = " << Depth << endl;

        int Depth_A = -1;

        if (!LorR){
            ///Смотрим на r от current_node
            Depth_A = current_node.r_depth;
            cout << "Looking at R: " << Depth_A << endl;

        }else{
            Depth_A = current_node.l_depth;
            cout << "Looking at L: " << Depth_A << endl;
        }

        if (Depth_A != (Depth-1)){
            ///DO SOME STUFF
        }else{
            return 0;/// Условие не выполнилось
        }

        return 1; ///PLACEHOLDER

    }

    void connect(Node nd){
        /// Принимает ноду(только с id и data и запихивает это всё в БД, определяя автоматически остальные параметры ноды), если нода уже была, то заменяет ноду

        long long foundROW = findElement(nd.id);

        cout << "Connecting " << nd.id << " .Found at: " << foundROW << endl;

        if (foundROW >= 0){
            ///нашли Элемент -> Заменяем его
            Node new_node = get_this_node(foundROW,0);
            new_node.data = nd.data;
            insert_here(new_node,foundROW);

            return;
        }


        DataBaseFILESTREAM.seekp(0,ios::end);

        if (root_row == -1){ /// Исключение (новая нода - первая, т.е. - корень)
            nd.parent_row = -1;
            DataBaseFILESTREAM << nd.GetString() << endl; ///Добавить ноду в конец файла

            UpdateRootNodeInfo(0);


            return;
            /// Т.к. это единственная нода, то ничего больше делать не надо
        }


        ///Приписать эту ноду к сыну другой ноды (родитель находится на строке (foundROW+1)*(-1) ), понять в l или r её записать как сына
        nd.parent_row = (foundROW+1)*(-1);
        DataBaseFILESTREAM << nd.GetString() << endl; ///Добавить ноду в конец файла

        Node parent_node = get_this_node(nd.parent_row,0);

        int new_row_place = GetSizeOfFile()- 1;

        if (StringCompare(nd.id,parent_node.id)){
            cout << "New Node is smaller (l - left)" << endl;


            modify_string_here(fillSpaces(NumberToString(new_row_place),rowSpace),nd.parent_row,idSpace);

        }else{


            cout << "New Node is bigger (r - right) ThisNode new row is: " <<new_row_place << endl;
            modify_string_here(fillSpaces(NumberToString(new_row_place),rowSpace),nd.parent_row,idSpace+rowSpace);
        }

        ///Изменить новые "глубины",

        int CURRENT_DEPTH = 0;

        int current_node_row = new_row_place;
        Node current_node = nd;
        int current_parent_node_row = nd.parent_row;
        Node current_parent_node;

        while (current_parent_node_row != -1){
            CURRENT_DEPTH++;
            current_parent_node = get_this_node(current_parent_node_row,0);

            ///

            cout << current_node_row << " " << current_parent_node_row << endl;

            int LorR = -1;

            if (current_parent_node.l_row == current_node_row){
                cout << "l" << endl; LorR = 0;

                if (current_parent_node.r_depth < CURRENT_DEPTH){
                    modify_string_here(fillSpaces(NumberToString(CURRENT_DEPTH),depthSpace),current_parent_node_row,idSpace+rowSpace*3);
                    current_parent_node.l_depth = CURRENT_DEPTH;
                }else{
                    break;
                }

            }else{
                cout << "r" << endl; LorR = 1;
                if (current_parent_node.r_depth < CURRENT_DEPTH){
                    modify_string_here(fillSpaces(NumberToString(CURRENT_DEPTH),depthSpace),current_parent_node_row,idSpace+rowSpace*3+depthSpace);
                    current_parent_node.r_depth = CURRENT_DEPTH;
                }else{
                    break;
                }
            }

            if (abs(current_parent_node.r_depth - current_parent_node.l_depth) >= 2){
                cout << "STARING THROWING" << endl;
                if (Throw_Over(current_parent_node,current_parent_node_row,current_node,LorR,CURRENT_DEPTH)){
                    break;
                }
                cout << "FAILED TO THROW" << endl;
            }

            ///


            current_node = current_parent_node;
            current_node_row = current_parent_node_row;

            current_parent_node_row = current_parent_node.parent_row;
        }




        /// В зависимости от новых "глубин" провести "перекидывание", если необходимо

    }



};

int main()
{

    string T1 = "23";
    string T2 = "123";
    fillSpaces(T1,3);
    cout << T1 << "}" << endl;
    cout << (T1 < T2) <<" " << StringCompare(T1,T2)  <<  endl;

    Node testNode,testNode2,testNode3,testNode4,testNode5;
    testNode.data = "Custom Data";
    testNode.id = "100";
    testNode.l_row = 1;
    testNode.r_row = 2;
    testNode.parent_row = -1;
    testNode.l_depth = 1;
    testNode.r_depth = 1;

    testNode2.data = "UNT-2";
    testNode2.id = "99";
    testNode2.l_row = -1;
    testNode2.r_row = -1;
    testNode2.parent_row = 0;
    testNode2.l_depth = 0;
    testNode2.r_depth = 0;

    testNode3.data = "CIS-3";
    testNode3.id = "103";
    testNode3.l_row = -1;
    testNode3.r_row = -1;
    testNode3.parent_row = 0;
    testNode3.l_depth = 0;
    testNode3.r_depth = 0;

    testNode4.data = "CIS-4";
    testNode4.id = "104";


    testNode5.data = "CIS-5";
    testNode5.id = "105";



    DataBase DB;

    DB.init();

    cout << "ROOT_ROW = " << DB.root_row << endl;

    cout << "BIBA: " << DB.IsThisRorLNode(1) << endl;

    DB.insert_here(testNode,0);
    DB.insert_here(testNode2,1);
    DB.insert_here(testNode3,2);

    //DB.modify_string_here("456",0,idSpace+rowSpace);


    //cout <<  "found: "<<DB.findElement("104") << endl;

    DB.connect(testNode4);
    DB.connect(testNode5);



    //cout << DB.get_this_string(2) << endl;

    //cout <<"(" <<  DB.get_this_node(2,1).GetString() << ")"  << endl;

    //cout << testNode.GetString();
    cout << "Hello world!" << endl;
    return 0;
}
