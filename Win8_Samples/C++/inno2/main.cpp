#include <iostream>

using namespace std;

int main()
{
    const int size_ = 10000; /// 2*
    int n;
    cin >> n;
    int arr[size_];

    int n_arr[size_];int h= 0;

    int choose[size_];


    for(int i =0;i<size_;i++){
        choose[i] = 0;
    }

    cin >> arr[0];
    n_arr[h] = 0;h++;
    n_arr[h] = arr[0];h++;


    for(int i =1;i<n;i++){
        cin >> arr[i];
        if (arr[i] != arr[i-1]){
            n_arr[h] = arr[i];h++;
        }
    }

    n_arr[h] = 0;h++;

    for(int i =0;i<h;i++){
        cout << n_arr[i] << " ";
    }

    cout << endl;

    for(int i =1;i<h-1;i++){
        choose[n_arr[i]] += 1 + (n_arr[i-1] == n_arr[i+1]);
    }

    int maxi_ = 10000000;int index = -1;
    for(int i =0;i<n;i++){
            if ( (choose[i] < maxi_)&&(choose[i] != 0) ){
                maxi_ = choose[i];
                index = i;
            }
        cout << choose[i] << endl;
    }


    cout << h-maxi_-2 << " " << index;

    cout << endl;


    return 0;
}
