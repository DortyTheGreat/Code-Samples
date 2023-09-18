#include <iostream>

using namespace std;

bool arr[10000];
int find_biggest_index(int known_size){
    int cou_1 = 0; int index1 = -1;
    int cou_0 = 0; int index0 = -1;
    for(int i = 1; i <= known_size; ++i){
        if (arr[i] == 0){
            cou_0++;
            index0 = i;
        }else{
            cou_1++;
            index1 = i;
        }
    }

    if (cou_0 > cou_1){
        return index0;
    }else{
        return index1;
    }
}


int main()
{
    int n;
    cin >> n;

    /// Невозможно однозначно понять
    if (n % 2 == 1){
        cout << "! -1" << endl;
        return 0;
    }

    /// Предположим, что arr[1] = 1

    arr[1] = 1;




    for(int i = 0; i < n/2; ++i){

        int i1 = i*2 + 1;
        int i2 = i*2 + 2;

        cout << "? L " << i1 << " "<< i2 << endl;
        int resp;
        cin >> resp;



        ///arr[i2] = !(arr[i1] ^ resp);


        ///arr[i1] ^= resp;

    }



    for(int i = 1; i <=n; ++i){
        ///cout << arr[i];
    }

    cout << "! " << n/2 << endl;



    return 0;
}
