#include <iostream>
#include <cmath>
using namespace std;

void Print_With_Probel(int arg){

for(int i=0;i<3 - std::log(arg)/std::log(10);i++){
    cout << " ";
}
cout << "  ";
cout << arg;
}

int summCifr(int arg){
int ans=0;

while(arg!=0){
    ans+=arg%10;
    arg/=10;
}
return ans;
}
bool Uslovie(int K,int R,int arg){
if(arg > pow(10,K-1) && arg < pow(10,K) && (summCifr(arg)%R == 0) ){
    return 1;
}else{
return 0;
}
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

    int third(int K,int R){
       int ans=0;
    for(int i=0;i<size_;i++){
        for(int j=0;j<size__;j++){
            if(Uslovie(K,R,Data[i][j])){ans++;}
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

long long customPow(int seed){
    long long exp = 4;
    long long ans = 1;
    for(int i =0;i<seed;i++){
        ans *= exp;
    }

    return ans;
}

int main()
{

    Matrix MyMatrix;
    MyMatrix.get_data(1);

    int Daddy = (MyMatrix.size_+1)/2;

    int ans_min_rotates = -1;
    int ans_index_stolb = -1;
    int ans_max_summ = -1000000;

    int ans_matrix[10][10];

    for(int itteration = 0;itteration < customPow(Daddy);itteration++){

            int rotations_all = 0;

            Matrix copieble_matrix;

            copieble_matrix = MyMatrix;

        for(int mask_cou = 0; mask_cou < Daddy; mask_cou++ ){

            Matrix mask;
            mask.size_ = mask.size__ = MyMatrix.size_;

            mask.fill_with_int(-10000);

            for(int i =0;i<MyMatrix.size_;i++){
                if (i >= mask_cou && i <= (MyMatrix.size_ - 1 - mask_cou)){
                    mask[i][mask_cou] = copieble_matrix[i][mask_cou];
                    mask[mask_cou][i] = copieble_matrix[mask_cou][i];



                    mask[i][MyMatrix.size_ - mask_cou - 1] = copieble_matrix[i][MyMatrix.size_ - mask_cou - 1];
                    mask[MyMatrix.size_ - mask_cou - 1][i] = copieble_matrix[MyMatrix.size_ - mask_cou - 1][i];
                }
            }

            int rotats =  itteration/( (long long)(powl(4,mask_cou)) ) % 4;

            rotations_all += rotats;

            for(int perform_rotations = 0;perform_rotations < rotats;perform_rotations++){
                mask.Rotate();
            }

            for(int i =0;i<10;i++){
                for(int j = 0;j<10;j++){
                    if ( mask[i][j] != -10000){
                        copieble_matrix[i][j] = mask[i][j];
                    }
                }
            }

        }


        for(int i = 0;i<MyMatrix.size_;i++){
            int summ = 0;
            for(int j = 0;j<MyMatrix.size_;j++){
                summ += copieble_matrix.Data[j][i];
            }

            if (summ > ans_max_summ){
                ans_max_summ = summ;
                ans_index_stolb = i;
                ans_min_rotates = rotations_all;

                for(int i =0;i<MyMatrix.size_;i++){
                    for(int j =0;j<MyMatrix.size_;j++){
                        ans_matrix[i][j] = copieble_matrix.Data[i][j];
                    }
                }

            }else{
                if (summ == ans_max_summ){
                    if (rotations_all < ans_min_rotates){
                       ans_max_summ = summ;
                        ans_index_stolb = i;
                        ans_min_rotates = rotations_all;

                        for(int i =0;i<MyMatrix.size_;i++){
                            for(int j =0;j<MyMatrix.size_;j++){
                                ans_matrix[i][j] = copieble_matrix[i][j];
                            }
                        }

                    }
                }
            }

           /// cout << endl;
        }
    }

    cout << ans_min_rotates <<" " << ans_index_stolb+1 << " " << ans_max_summ << endl;

   for(int i =0;i<MyMatrix.size_;i++){
        for(int j =0;j<MyMatrix.size_;j++){
            cout << ans_matrix[i][j] << " ";
        }
        cout << endl;
    }

}
