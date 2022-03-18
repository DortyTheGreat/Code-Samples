#include <iostream>

using namespace std;
int solve_10(int n){
    int ans=0;
    for(int cou_10=0;cou_10<=n;cou_10+=10){
            for(int cou_5=0;cou_5<=n-cou_10;cou_5+=5){
                for(int cou_2=0;cou_2<=n-cou_10-cou_5;cou_2+=2){
                    int cou_1 = n-cou_10-cou_5-cou_2;
                        ans++;
                        //cout << cou_10 << " " << cou_5 << " " << cou_2 << " " << cou_1 << endl;

                }
            }
        }
        return ans;

}
int main()
{
    int n;
    cin >> n;




    cout << solve_10(n);
}
