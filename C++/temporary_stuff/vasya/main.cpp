#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;
    int arr[100][4];
    bool mask[100];
    for(int i = 0;i<n;i++){
        mask[i] = 1;
        cin >> arr[i][0] >> arr[i][1] >> arr[i][2] >> arr[i][3];
    }

    for(int i = 0;i<n;++i){
        for(int j = 0;j<n;++j){
            if (arr[i][0] < arr[j][0] && arr[i][1] < arr[j][1] && arr[i][2] < arr[j][2]){
                mask[i] = 0;
                ///cout << i << " " << j << endl;
            }
        }
    }
    int price = 10000000;
    int index = -1;
    for(int i = 0;i<n;++i){
        if (mask[i] == 0) continue;
        if (price > arr[i][3]){
            price = arr[i][3];
            index = i;
        }
    }

    cout << index+1 << endl;
    return 0;
}
