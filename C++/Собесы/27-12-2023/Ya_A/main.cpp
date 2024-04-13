#include <iostream>

using namespace std;

int64_t days_in_month(int month){
    switch (month) {
      case 2:
        return 28;
      ///case 1, 3, 5, 7, 8, 10, 12:
      case 1:
      case 3:
      case 5:
      case 7:
      case 8:
      case 10:
      case 12:

        return 31;
      default:
        return 30;
    }
}

int main()
{
    int64_t y1, m1, d1, h1, min1, s1;
    int64_t y2, m2, d2, h2, min2, s2;

    cin >> y1 >> m1 >> d1 >> h1 >> min1 >> s1;
    cin >> y2 >> m2 >> d2 >> h2 >> min2 >> s2;

    int64_t sec_d = s2 - s1 + min2*60 - min1*60;

    sec_d += h2*3600 - h1*3600;
    sec_d += d2*3600*24 - d1*3600*24;
    int64_t day_d = 0;

    while(m1 != m2){
        day_d += days_in_month(m1);
        m1 += 1;
        if (m1 == 13){
            m1 = 1;
            y1++;
        }
    }

    sec_d += day_d*3600*24;

    sec_d += y2*3600*24*365 - y1*3600*24*365;

    cout << sec_d/(3600*24) << " " << sec_d%(3600*24);
    return 0;
}
