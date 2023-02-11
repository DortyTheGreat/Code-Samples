#include <iostream>

using namespace std;

#include <sstream> // this will allow you to use stringstream in your program

template<typename T>
int strToInt(T str){
    //extract the string from the str variable (input the string in the stream)
   stringstream ss;
   ss << str;

   // place the converted value to the int variable
   int num;
   ss >> num;
   return num;
}
#include <set>
int main()
{
    int t;
    cin >> t;
    set<int> nums;
    while(t--){
        int n;
        cin >> n;


        if (n % 2 == 0){
            cout << "No" << endl;
            continue;
        }

        cout << "Yes" << endl;
        n *= 2;
        cout << "1 " << n << endl;
        for(int i = 0; i < n/4; ++i){
            cout << 2+2*i << " " << n - n/4 - 1 - i << endl;
        }

        for(int i = 0; i < n/4; ++i){
            cout << 3+2*i << " " << n - i - 1 << endl;
        }




    }
    return 0;
}
