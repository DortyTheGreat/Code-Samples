#include <iostream>
#include <cmath>
using namespace std;

typedef   uint64_t    u64;
typedef   int64_t    i64;
/// 10 -> 317
int main()
{
    i64 x0, x1, x2;
    i64 y0, y1, y2;

    cin >> x0 >> y0;
    cin >> x1 >> y1;
    cin >> x2 >> y2;

    cout << abs((x1 - x0)*(y2 - y0) - (x2 - x0)*(y1 - y0));

    return 0;
}
