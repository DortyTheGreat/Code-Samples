#include <iostream>

using namespace std;

int main()
{
    int num = 1 + 10 + 26;
    int anum=0;

    for(int i=0;i<num;i++){
        for(int j=0;j<num;j++){
                for(int k=0;k<num;k++){

                if(!i || !j || !k){anum++;}


                }
        }
    }

    cout << anum;
}
