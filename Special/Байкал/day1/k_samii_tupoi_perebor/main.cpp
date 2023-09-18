#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;
    int arr[100];
    for(int i = 0; i < n; ++i){
        cin >> arr[i];
    }
    int best_ans = 100000 * 30;
    for(int case_ = 0; case_ < 1 << n; case_++){
        int s_1 = 0;
        int s_2 = 0;
        for(int i = 0; i < n; ++i){
            if ((case_ >> i) & 1){
                s_1 += arr[i];
            }else{
                s_2 += arr[i];
            }

        }
        best_ans = min(best_ans, abs(s_1-s_2));

    }

    cout << best_ans;

    return 0;
}
