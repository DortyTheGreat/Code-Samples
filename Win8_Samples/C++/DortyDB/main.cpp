#include <iostream>

#include <fstream>

using namespace std;

const int CellSize = 5000 - 2;


class InfoCell{
public:
    string id, data;


    string GetString(){
        string temp = id + " " + data;

        while(temp.size() != CellSize){
            temp += " ";
        }
        return temp;

    }

};


class DataBase{
public:

    fstream DataBaseFILESTREAM;
    int rows = -1; /// сколько строк в файле


    int GetSizeOfFile(){
        // get length of file:
        DataBaseFILESTREAM.seekg (0, DataBaseFILESTREAM.end);
        int length = DataBaseFILESTREAM.tellg();
        DataBaseFILESTREAM.seekg (0, DataBaseFILESTREAM.beg);

        rows = length / (CellSize + 2);
        return length;
    }

    void init(){
        DataBaseFILESTREAM.open ("DataBase.txt", fstream::in | fstream::out);
        GetSizeOfFile();
    }



    void push_element(InfoCell ic){
        DataBaseFILESTREAM << ic.GetString() << endl;
    }

    void insert_here(InfoCell ic, int row){
        DataBaseFILESTREAM.seekp((CellSize+2) * row);
        DataBaseFILESTREAM << ic.GetString() << endl;
    }

    void create_new(InfoCell ic, int row){

        DataBaseFILESTREAM.seekp((CellSize+2) * 1);
        DataBaseFILESTREAM <<"123";
    }



    string get_this_string(int row){
        DataBaseFILESTREAM.seekg((CellSize+2) * row);
        string temp;
        getline(DataBaseFILESTREAM,temp);
        //DataBaseFILESTREAM >> temp;
        return temp;
    }

    string get_this_string_id(int row){
        DataBaseFILESTREAM.seekg((CellSize+2) * row);
        string temp;
        DataBaseFILESTREAM >> temp;
        //DataBaseFILESTREAM >> temp;
        return temp;
    }

    int findElement(string id){

        int f_row = 0;
        int l_row = rows - 1;


        while (l_row - f_row > 1){

            int mid_row = (f_row + l_row ) / 2;

            string mid_ID = get_this_string_id(mid_row);

            if (mid_ID > id){
                l_row = mid_row;
            }else{
                f_row = mid_row;
            }

            cout << mid_row << " " << mid_ID  << " " <<f_row << " " <<l_row << endl;

        }


        if (get_this_string_id(l_row) == id){return l_row;}
        if (get_this_string_id(f_row) == id){return f_row;}

        return -1;

    }

    void smarter_insert(InfoCell ic){
            int Finder = findElement(ic.id);
        if (Finder == -1){
            //Нет элемента - нужно вставить в нужное место. А не в конец
            insert_here(ic,rows);
            rows++;
        }else{
            insert_here(ic,Finder);
        }



    }




};

int main()
{

    string T1 = "42";
    string T2 = "124";



    cout << (T1 < T2) << endl;
    DataBase DB;

    DB.init();




    cout << DB.rows << endl;
    cout << DB.get_this_string(0) << endl;

    cout << DB.get_this_string_id(1) << endl;

    //DataBase << "GAYS!" << endl;


    InfoCell ic;
    ic.id = "125";
    ic.data = "Info about_abobus Dorty Schmorty";
    //DB.push_element(ic);

    DB.findElement("122");

    ///DB.insert_here(ic,DB.findElement("123"));

    DB.create_new(ic,1);

    ///DB.smarter_insert(ic);





    /*
    string Carret;
    while(!DataBase.eof()){
        getline(DataBase,Carret);
        cout << Carret << endl;
    }


    */


    cout << "Hello world!" << endl;
    return 0;
}
