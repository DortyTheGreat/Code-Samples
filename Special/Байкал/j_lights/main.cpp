#include <iostream>
#define int long long
using namespace std;

int mod = 1000000000 + 7;

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--){

        int useless;
        cin >> useless;

        string bin_seq;
        cin >> bin_seq;
        int first_light_on;
        int last_light_on;

        first_light_on = bin_seq.find("1");
        last_light_on = bin_seq.rfind("1");
        cout << first_light_on << " " << last_light_on << endl;
        if (first_light_on == -1){
            cout << 0 << endl;
            continue; /// Нет включённых фонарей, идти не надо
        }

        int ans = 0;

        for(int pos = 0; pos < bin_seq.size(); ++pos){
            int dist = 1001 * 1001 * 1001;




            dist = min(dist,abs(pos-first_light_on) + abs(first_light_on - last_light_on));
            dist = min(dist,abs(pos-last_light_on) + abs(first_light_on - last_light_on));

            if (pos == first_light_on || pos == last_light_on){dist += 2;}

            ans += (pos+1) * dist;
            ans %= mod;

            cout << ans << endl;
        }
        cout << ans << endl;

    }

    cout << endl;
    return 0;
}
