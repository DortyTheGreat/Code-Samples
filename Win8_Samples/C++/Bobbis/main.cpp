/*
Даны $N$ целых чисел $X_1$, $X_2$, ..., $X_N$. Требуется вычеркнуть из них минимальное количество чисел так, чтобы оставшиеся шли в порядке возрастания.

Входные данные
В первой строке находится число $N$. В следующей строке - $N$ чисел через пробел. 1 <= $N$ <= 10 000, 1 <= $X_i$ <= 60 000.

Выходные данные
В первой строке выводится количество невычеркнутых чисел, во второй - сами невычеркнутые числа через пробел в исходном порядке. Если вариантов несколько, вывести любой.
*/




#include <iostream>
using namespace std;

int main()
{
    int m=8;
    int orriginal[10000];

    string kk;
    cin >> kk;


    m = kk.size();
    for(int i=0;i<m;i++){
        orriginal[i] = int(kk[i]);

    }
    int pointers[10000];
int tempt=0;
int maxi=-1, index=0;
    for(int i=m-1;i>-1;i--){
    tempt=0;
    for(int j=i;j<m;j++){
         if(pointers[j] > tempt && orriginal[i] < orriginal[j] ){
            tempt=pointers[j];
         }
    }
    tempt++;
    pointers[i]= tempt;
    if(maxi < tempt){maxi=tempt;index= i;}
    }

    cout << 26 - maxi << endl;
    for(int i=index;i<m;i++){
        if(pointers[i] == maxi){
            //cout << orriginal[i] << " ";maxi-=1;
        }
    }
}
