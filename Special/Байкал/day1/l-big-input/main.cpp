#include <iostream>

using namespace std;

int main()
{
    int n = 0;
    cin >> n;
    int arr[100];

    for(int i = 0; i < 100; ++i){
        arr[i] = 0;
    }

    int c;
    for(int i = 0; i < n; ++i){
        scanf("%d", &c);
        ++arr[c];
    }

    for(int i = 0; i < 100; ++i){
        for(int j = 0; j < arr[i]; ++j){
            printf("%d", i);
            printf("%s", " ");
        }
    }

    return 0;
}
