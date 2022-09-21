#include <cmath>

void Print_With_Probel(int arg){

for(int i=0;i<3 - std::log(arg)/std::log(10);i++){
    cout << " ";
}
cout << "  ";
cout << arg;
}

class Matrix{
public:
    int Data[100][100];
    int size_,size__;
    void get_data(){
    cin >> size_ >> size__;
    for(int i=0;i<size_;i++){
        for(int j=0;j<size__;j++){
            cin >> Data[i][j];
        }
    }
    }
    void get_data(int arg){
    cin >> size_;size__ = size_;
    for(int i=0;i<size_;i++){
        for(int j=0;j<size__;j++){
            cin >> Data[i][j];
        }
    }
    }

    void get_data(int arg,int arg2){
    cin >> size_;cin >> size__;

    }

    int get_summ(){
        int ans=0;
    for(int i=0;i<size_;i++){
        for(int j=0;j<size__;j++){
            ans+= Data[i][j];
        }
    }
    return ans;
    }
    int find_elem(int arg){
       int ans=0;
    for(int i=0;i<size_;i++){
        for(int j=0;j<size__;j++){
            if(arg == Data[i][j]){ans++;}
        }
    }
    return ans;
    }

    void MinAndMax(){
    int min_=Data[0][0],max_=Data[0][0];
    int min_index[2]={0,0}, max_index[2]={0,0};
    for(int i=0;i<size_;i++){
        for(int j=0;j<size__;j++){
            if(Data[i][j] > max_){
                max_=Data[i][j];
                max_index[0]=i;max_index[1]=j;
            }

            if(Data[i][j] < min_){
                min_=Data[i][j];
                min_index[0]=i;min_index[1]=j;
            }

        }
    }
    for(int i = 0;i<size__;i++){
            int yes = 0;
        for(int j=0;j<size_;j++){
            if( Data[j][i] == max_ ){
                yes = 1;
    break;
            }
        }
        if(yes){
            for(int j=0;j<size_;j++){
                cout << Data[j][i] << " ";
            }
        }

    }
    }

    void Triangel(){
    for(int i = 0;i<size_;i++){
        for(int j=0;j<size__;j++){
            if(j > i){Data[i][j] = 0;}
        }

    }
    }

    void Print(){
    for(int i = 0;i<size_;i++){
        for(int j=0;j<size__;j++){
            cout << Data[i][j] << " ";
        }
        cout << endl;
    }
    }

    void IsSimmetry(){
        int da=1;
    for(int i = 0;i<size_;i++){
        for(int j=0;j<size__;j++){
            if(Data[i][j] != Data[j][i]){
                da=0;
            }
        }

    }
    if(da){
        cout << "YES";
    }else{
    cout << "NO";
    }
    }

    void Fillchess(){
    for(int i = 0;i<size_;i++){
        for(int j=0;j<size__;j++){
           Data[i][j] = abs(i-j);
        }

    }
    }
    void RitterPrint(){
    for(int i = 0;i<size_;i++){
        for(int j=0;j<size__;j++){
            Print_With_Probel(Data[i][j]);
        }
        cout << endl;
    }
    }

    void Fill_Zmey(){
    for(int i = 0;i<size_;i++){
        for(int j=0;j<size__;j++){
                if(j%2){
                    Data[i][j] = (j+1)*size_ -i ;
                }else{
                Data[i][j] = i+1 + size_*j;
                }
           //Data[i][j] = abs(i-j);
        }

    }
    }
    void Rotate(){
        int container[100][100];
        for(int i=0;i<size_;i++){
            for(int j=0;j<size__;j++){
                container[i][j] =  Data[size__ -j -1][i];
            }
            //cout << endl;
        }

        for(int i=0;i<size_;i++){
            for(int j=0;j<size__;j++){
                Data[i][j] =  container[i][j];
            }
            //cout << endl;
        }
    }

    int* operator[] (const int index) // для неконстантных объектов: может использоваться как для присваивания значений элементам, так и для их просмотра
    {
        return Data[index];
    }

    void fill_with_int(int num){
        for(int i=0;i<size_;i++){
            for(int j=0;j<size__;j++){
                Data[i][j] = num;
            }
            //cout << endl;
        }
    }



};
