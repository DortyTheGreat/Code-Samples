#include <iostream>
#include <vector>
using namespace std;
const long long SIZE_OF_ALL=300;
class Graph{
public:

    long long Data[SIZE_OF_ALL][SIZE_OF_ALL];
    long long size_;
    long long start_num=0;

    long long DEBUG_MODE=0;


    long long Populated_Distance[SIZE_OF_ALL]; // also known as 'dist'
    long long Amount_Of_Paths[SIZE_OF_ALL]; // This is used to find the back path, also
    //known as 'used'

    long long pseudo_inf=50000000000;
    void read_as_matrix(long long size__){
        long long req1;
    size_ = size__;
    for(long long i =start_num;i<start_num + size_;i++){
        for(long long j=start_num;j<start_num + size_;j++){

            cin >> req1;
            if(req1 > 0){Data[i][j] = req1;}else{Data[i][j]=pseudo_inf;}
        }

    }
    }

    void read_as_requests(){
    cin >> size_;
    for(long long i=0;i<size_;i++){
        for(long long j=0;j<size_;j++){
            Data[i][j]=pseudo_inf;
        }
    }
    long long Amount_Of_Requests,req1,req2,req3;
    cin >> Amount_Of_Requests;
    for(long long i=0;i<Amount_Of_Requests;i++){
        cin >> req1 >> req2 >> req3;
        Data[req1-1][req2-1] = req3;
        Data[req2-1][req1-1] = req3;
    }

    }




    void DEBUG_PRINT_POPULATE(){
    for(long long i=0;i<size_;i++){
        cout << Populated_Distance[i] << " ";
    }
    cout <<" : ";
    for(long long i=0;i<size_;i++){
        cout << Amount_Of_Paths[i] << " ";
    }
    cout << endl;
    }

    void DEBUG_PRINT_DATA(){
    for(long long i=0;i<size_;i++){
        for(long long j=0;j<size_;j++){
            cout << Data[i][j] << " ";
        }
        cout << endl;
    }
    }

    void Requr_BFS(long long Uses, long long distanto,long long dot){
    if( distanto >= Populated_Distance[dot] ){return;}



    Amount_Of_Paths[dot] = Uses;
    Populated_Distance[dot] = distanto;
    if(DEBUG_MODE){DEBUG_PRINT_POPULATE();}
    for(long long i=0;i<size_;i++){
        if( (Data[dot][i] != pseudo_inf) && (dot != i) ){
            Requr_BFS(Uses+1,distanto+Data[dot][i],i);
        }
    }

    }

    void RUN_DeikSTR_BFS(long long start_point){

    for(long long i=0;i<SIZE_OF_ALL;i++){
        Populated_Distance[i]=pseudo_inf;
        Amount_Of_Paths[i]=0;
    }
    Requr_BFS(0,0,start_point);
    }


    long long Get_The_Distance_To(long long dot_to){
    if(Populated_Distance[dot_to] != pseudo_inf ){
    return Populated_Distance[dot_to];
    }else{
    return -1;
    }

    }

    long long count_all(){
    long long ans=-10000;
    for(long long i=0;i<size_;i++){
    if(Populated_Distance[i] > ans){
     ans=Populated_Distance[i];
    }
    }
    return ans;
    }






};




int main()
{
    Graph a123;
    a123.read_as_requests();
    long long MINI=100000000;long long index=1;
    for(long long i=0;i<a123.size_;i++){
        a123.RUN_DeikSTR_BFS(i);
        long long temp = a123.count_all();
        if(temp < MINI ){

            MINI = temp;
            index = i+1;

        }

    }
    cout << index;



    return 0;
}

