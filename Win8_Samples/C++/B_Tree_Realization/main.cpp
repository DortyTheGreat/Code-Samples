#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

///Реализация B-Древа с Кнут-Ордер 3.
///
///
///

const int idSpace = 10;
const int rowSpace = 10;
const int dataSpace = 2000; ///Место на всё ()

const int CellSize = dataSpace*2 + idSpace*2 + rowSpace*4 + rowSpace;
template <typename T>
  std::string NumberToString ( T Number )
  {
     std::ostringstream ss;
     ss << Number;
     return ss.str();
  }

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

class Cell{
public:
    string id1="-1",id2="-1";
    long long b1_row = -1,b2_row = -1,b3_row = -1,b4_row = -1; /// b - от слова baby
    long long parent_row = -1;

    string data1="default_data1",data2 = "default_data2";

    string GetString(){
        string temp = fillSpaces(id1,idSpace) + fillSpaces(id2,idSpace) + fillSpaces(NumberToString(b1_row),rowSpace) + fillSpaces(NumberToString(b2_row),rowSpace) + \
        fillSpaces(NumberToString(b3_row),rowSpace) + fillSpaces(NumberToString(b4_row),rowSpace) + fillSpaces(NumberToString(parent_row),rowSpace) + fillSpaces(data1,dataSpace) + fillSpaces(data2,dataSpace-2);



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
        UtilFILESTREAM.seekg(0);

    }

    int GetSizeOfFile(){
        // get length of file:
        DataBaseFILESTREAM.seekg (0, DataBaseFILESTREAM.end);
        int length = DataBaseFILESTREAM.tellg();
        DataBaseFILESTREAM.seekg (0, DataBaseFILESTREAM.beg);


        return length  / (CellSize);
    }

    void UpdateRootRowInfo(long long root_row_){
        UtilFILESTREAM.seekp(0);
        UtilFILESTREAM << fillSpaces(NumberToString(root_row_),rowSpace);
        cout << "HERE - {" << fillSpaces(NumberToString(root_row_),rowSpace) << "}"<< endl;
        root_row = root_row_;
    }

    void insert_here(Cell ic, int row){
        DataBaseFILESTREAM.seekp((CellSize) * row);
        DataBaseFILESTREAM << ic.GetString() << endl;
    }

    void modify_string_here(string info, int row,int spacesSkip){
        DataBaseFILESTREAM.seekp((CellSize) * row + spacesSkip);
        DataBaseFILESTREAM << info;
    }

    Cell get_this_cell(int row, bool DoReadData){
        DataBaseFILESTREAM.seekg((CellSize) * row);
        Cell temp;
        DataBaseFILESTREAM >> temp.id1;
        DataBaseFILESTREAM >> temp.id2;
        DataBaseFILESTREAM >> temp.b1_row;
        DataBaseFILESTREAM >> temp.b2_row;
        DataBaseFILESTREAM >> temp.b3_row;
        DataBaseFILESTREAM >> temp.b4_row;
        DataBaseFILESTREAM >> temp.parent_row;

        if (DoReadData){
            DataBaseFILESTREAM >> temp.data1;
            DataBaseFILESTREAM >> temp.data2;
        }
        //getline(DataBaseFILESTREAM,temp.data);
        //DataBaseFILESTREAM >> temp;
        return temp;
    }

    int findElement(string id){
        /// Возвращает номер строки, на котором содержится ячейка элемента. Если элемента не существует возвращает отрицательное-1 значение ячейки ближе всего к которой находится наш элемент\\
        Т.е. Например, если функция возвращает -3, то ноды нет и её следует привязать к ноде находящейся на 2ой строчке.\\
        Если значение 4 - то нода есть, находится на 4ой строчке.\\
        ВАЖНО! Нумерация строк идёт с нуля, а не единицы

        int this_row = root_row;
        int last_row = -1;

        Cell this_cell;

        while(this_row != -1){
            last_row = this_row;
            this_cell = get_this_cell(this_row,0);

            if (this_cell.id1 == id){return this_row;}
            if (this_cell.id2 == id){return this_row;}

            if (StringCompare(id,this_cell.id1) ){
                ///Наше меньше чем первое
                this_row = this_cell.b1_row;continue;
            }
            if (this_cell.id2 == "-1"){
                this_row = this_cell.b2_row;continue;
            }

            if (StringCompare(id,this_cell.id2) ){
                ///Наше меньше чем второе
                this_row = this_cell.b2_row;continue;
            }

            this_row = this_cell.b3_row;

        }

        return ((-1) * last_row - 1);
    }


    int AddElemToCell(string id, string data, int cell_row){
        /// Возвращает row родителя для макс. элемента

        if (cell_row == -1) {
            /// Увеличение размера древа -> его не должно происходить, можно убрать сравнитель
            cout << "ERROR. PROGRAMM SHOULDN't BE THERE" << endl;

        }

        Cell inserted_cell = get_this_cell(cell_row,1);

        if (inserted_cell.id1 == "-1"){
            /// Исключение: новый элемент - первый во всём древе

        }

        if (inserted_cell.id2 == "-1"){
            ///Есть место -> пихаем
            inserted_cell.id2 = id;
            inserted_cell.data2 = data;

            if (StringCompare(inserted_cell.id2 , inserted_cell.id1)){
                swap(inserted_cell.id1,inserted_cell.id2);
                swap(inserted_cell.data1,inserted_cell.data2);
            } /// Всегда в cell значения упорядочены

            insert_here(inserted_cell,cell_row);
            return cell_row;
        }

        string id2 = inserted_cell.id1;
        string id3 = inserted_cell.id2;

        string data2 = inserted_cell.data1;
        string data3 = inserted_cell.data2;

        string min_,min_data;
        string max_,max_data;
        string mid_,mid_data;

        if (StringCompare(id, id2) && StringCompare(id,  id3)){
            min_ = id;min_data=data;
            if (StringCompare(id2 , id3)){
                mid_ = id2;mid_data=data2;
                max_ = id3;max_data = data3;
            }else{
                mid_ = id3; mid_data = data3;
                max_ = id2; mid_data = data2;
            }
        }else{
            if (StringCompare(id2 , id)){
                min_ = id2; min_data = data2;
                if (StringCompare(id , id3)){
                    mid_ = id; mid_data = data;
                    max_ = id3; max_data = data3;
                }else{
                    mid_ = id3; mid_data = data3;
                    max_ = id; max_data = data;
                }
            }else{
                min_ = id3; min_data = data3;
                if (StringCompare(id , id2)){
                    mid_ = id; mid_data = data;
                    max_ = id2; max_data = data2;
                }else{
                    mid_ = id2; mid_data = data2;
                    max_ = id; max_data = data;
                }
            }
        } ///Убрать бы этот парсер...


        Cell Big_Cell;

        Big_Cell.b1_row = inserted_cell.b3_row;
        Big_Cell.b2_row = inserted_cell.b4_row;

        inserted_cell.data1 = min_data;
        inserted_cell.id1 = min_;

        inserted_cell.id2 = "-1";
        inserted_cell.data2 = "default_data2";

        inserted_cell.b3_row = -1;
        inserted_cell.b4_row = -1;

        insert_here(inserted_cell,cell_row);





        Big_Cell.data1 = max_data;
        Big_Cell.id1 = max_;

        Big_Cell.parent_row = -2; /// Без разницы, всё равно другая клетка "напомнит".

        if (inserted_cell.parent_row != -1){
            Big_Cell.parent_row = inserted_cell.parent_row;
        }


        int Big_Cell_Row = GetSizeOfFile();
        if (Big_Cell.b1_row != -1){
            /// Сюда детям inserted_cell.b3_row и b4 нужно сказать, что новый родитель - BigCell
            modify_string_here(fillSpaces(NumberToString(Big_Cell_Row),rowSpace),Big_Cell.b1_row,idSpace*2 + rowSpace*4);
        }

        if (Big_Cell.b2_row != -1){
            /// Сюда детям inserted_cell.b3_row и b4 нужно сказать, что новый родитель - BigCell
            modify_string_here(fillSpaces(NumberToString(Big_Cell_Row),rowSpace),Big_Cell.b2_row,idSpace*2 + rowSpace*4);
        }

        insert_here(Big_Cell,Big_Cell_Row);


        /// К parent'у из parent_row надо добавить ребёнка BigCell
        if (inserted_cell.parent_row != -1){ /// В ЭТОЙ СТРОЧКЕ ПРОИСХОДИТ ЧТЕНИЕ ВСЕЙ СТРОКИ КЛЕТКИ, ПОКА НАДО ЧИТАТЬ ЛИШЬ 4 ЗНАЧЕНИЯ!
            Cell parent = get_this_cell(inserted_cell.parent_row,1);
            while(1){
                if (parent.b1_row == -1){parent.b1_row = Big_Cell_Row;break;}
                if (parent.b2_row == -1){parent.b2_row = Big_Cell_Row;break;}
                if (parent.b3_row == -1){parent.b3_row = Big_Cell_Row;break;}
                if (parent.b4_row == -1){parent.b4_row = Big_Cell_Row;break;}
                break;
            }
            insert_here(parent,inserted_cell.parent_row);

            cout << inserted_cell.parent_row << " ++++" << endl;

            AddElemToCell(mid_,mid_data,inserted_cell.parent_row);


            cout << "Explosion! " <<min_ <<" " << mid_ << " " << max_ <<   endl;
            return cell_row;

        }else{
        ///Иной случай -> parent_row = -1 -> добавляем новую клетку
            int new_row = GetSizeOfFile();
                            // modify_string_here(fillSpaces(NumberToString(Big_Cell_Row),rowSpace),Big_Cell.b1_row,idSpace*2 + rowSpace*4);
            UpdateRootRowInfo(new_row);
            cout << "NEW ROOT AT:" << new_row << endl;
            Cell new_root_cell;
            new_root_cell.data1 = mid_data;
            new_root_cell.id1 = mid_;

            new_root_cell.b1_row = cell_row;
            new_root_cell.b2_row = Big_Cell_Row;

            insert_here(new_root_cell, new_row);

            modify_string_here(fillSpaces(NumberToString(new_row),rowSpace),cell_row,idSpace*2 + rowSpace*4);
            modify_string_here(fillSpaces(NumberToString(new_row),rowSpace),Big_Cell_Row,idSpace*2 + rowSpace*4);

            return new_row;
        }

    }

     void connect(Cell nd){
        /// Принимает Cell(только с id1 и data1 и запихивает это всё в БД, определяя автоматически остальные параметры ноды), если нода уже была, то заменяет ноду

        long long foundROW = findElement(nd.id1);

        cout << "Connecting " << nd.id1 << " .Found at: " << foundROW << endl;

        if (foundROW >= 0){
            ///нашли Элемент -> Заменяем его
            Cell new_cell = get_this_cell(foundROW,1);

            if (new_cell.id1 == nd.id1){
                new_cell.data1 = nd.data1;
            }else{
                new_cell.data2 = nd.data1;
            }

            insert_here(new_cell,foundROW);

            return;
        }

        foundROW = (foundROW+1)*(-1);
        cout << "Element Wasn't in the database, should be added to " << foundROW << " <-this row cell" << endl;
        AddElemToCell(nd.id1,nd.data1,foundROW);


     }

};

int main()
{
    DataBase DB;
    DB.init();

    Cell testCell,TC2,TC3;
    testCell.id1 = "1";

    TC2.id1 = "2";
    TC2.data1 = "Really_important";

    TC3.id1 = "3";
    TC3.data1 = "Oh! Important!";

    DB.insert_here(testCell,0);

    for(int i = 2;i<32;i++){
        TC2.id1 = NumberToString(i);
        TC2.data1 = "Custom_Data_" + NumberToString(i);
        DB.connect(TC2);
    }

    //DB.connect(TC2);
    //DB.connect(TC3);

    cout << testCell.GetString() << endl;

    cout << DB.findElement("2");




    return 0;
}
