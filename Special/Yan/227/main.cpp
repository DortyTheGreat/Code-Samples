#include <iostream>

using namespace std;

int64_t books_left_after_n_weeks_passes(int64_t k, int64_t m, int64_t weeks, int64_t counter){
    m += weeks*5*k;
    m -= ((counter + (counter + weeks*7-1)) * weeks/2 * 7);
    return m;
}

int main()
{
    int64_t k,m,d;
    cin >> k >> m >> d;
    int64_t counter = 1;
    while ( d != 1){
        if (d <= 5)
            m += k;
        m -= counter;
        ++counter;
        if (m < 0){
            cout << counter - 2;
            return 0;
        }

        d++;
        if (d == 8){
            d = 1;
        }
    }

    int64_t l = 0;
    int64_t r = 1000 * 1000 * 300;

    while(r - l > 1){
        int64_t mid = (r+l) / 2;
        if (books_left_after_n_weeks_passes(k,m,mid,counter) >= 0 ){
            l = mid;
        }else{
            r = mid;
        }
    }

    //cout << l << " " << r;
    //cout << endl;
    //cout << books_left_after_n_weeks_passes(k,m,l,counter) << " " << books_left_after_n_weeks_passes(k,m,r,counter);
    //cout << endl;

    m = books_left_after_n_weeks_passes(k,m,l,counter);
    counter += l*7;


    while ( true){
        if (d <= 5)
            m += k;
        m -= counter;
        ++counter;
        if (m < 0){
            cout << counter - 2;
            return 0;
        }

        d++;
        if (d == 8){
            d = 1;
        }
    }


    return 0;
}
