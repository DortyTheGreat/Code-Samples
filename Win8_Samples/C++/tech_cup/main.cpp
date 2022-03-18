#include <iostream>
#include <algorithm>

using namespace std;

int main()
{

    int t;
    cin >> t;

    vector<int> data;
    vector<int> n_data;

    for(int _itere = 0;_itere<t;_itere++){
            data.clear();
        int n;
        cin >>n;
        int k;
        cin>> k;
        k--;

        for(int i =0;i<n;i++){
            int temp = 0;
            cin >> temp;
            if(temp >= 0){
                data.push_back(temp);
            }else{
                n_data.push_back(abs(temp));
            }
        }

        sort(data.begin(),data.end());
        sort(n_data.begin(),n_data.end());


        long long answer = 0;

        for(int i =0;i<data.size();){
            int first = data[i];
            int second;
            if ((i+k) >= n){
                second = data[n-1];
            }else{
                second = data[i+k];
            }


            answer += abs(first);
            answer += second - first;
            i += (k+1);
            if (i >= (n)){
                break;
            }else{
                answer += max(abs(second),abs(first));
            }
        }


        for(int i =0;i<n_data.size();){
            int first = n_data[i];
            int second;
            if ((i+k) >= n){
                second = n_data[n-1];
            }else{
                second = n_data[i+k];
            }


            answer += abs(first);
            answer += second - first;
            i += (k+1);
            if (i >= (n)){
                break;
            }else{
                answer += max(abs(second),abs(first));
            }
        }

        cout << answer << endl;

    }




    return 0;
}
