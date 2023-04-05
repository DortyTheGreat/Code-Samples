#include <iostream>
#include <string>
using namespace std;

int days_in_year(int month, bool vis){

    if((month==2) && vis){
        return 29;
    }
    else if(month==2){
        return 28;
    }
    else if(month==1 || month==3 || month==5 || month==7 || month==8 || month==10 || month==12){
        return 31;
    }
    else if(month==4 || month==6 || month==9 || month==11){
        return 30;
    }
}

int main()
{
    string a;
    getline(cin,a);
    int state = 0;
    int last_seen = 0;

    bool vis = 0;

    int month__ = -1;

    for(int i = 0;i<a.size(); ++i){
        if (a[i] == '/'){



            if (state == 1){
                string month = a.substr(last_seen,i - last_seen);

                if (month.size() != 2){
                    cout << "False"; /// 2 символа
                    return 0;
                }

                for(int i = 0; i < 2; ++i){
                    if ( !(month[i]>= '0' && month[i]<= '9') ){
                        cout << "False"; /// только цифры
                        return 0;
                    }
                }

                int num = atoi( month.c_str() );

                if (num == 0 || num >= 13){
                    cout << "False"; /// неверный месяц
                    return 0;
                }

                month__ = num;

                last_seen = i+1;
                state++;
                ///cout << "{" <<month <<"}";
            }

            if (state == 0){
                string year = a.substr(last_seen,i - last_seen);

                if (year.size() != 4){
                    cout << "False"; /// 4 символа
                    return 0;
                }

                for(int i = 0; i < 4; ++i){
                    if ( !(year[i]>= '0' && year[i]<= '9') ){
                        cout << "False"; /// только цифры
                        return 0;
                    }
                }

                int num = atoi( year.c_str() );

                if (num % 400 == 0){
                    vis = 1;
                }else{
                    if (num % 4 ==0 && num % 100 != 0){
                        vis = 1;
                    }else{
                        vis = 0;
                    }
                }

                last_seen = i +1;
                state++;
                ///cout << "{" <<year <<"}";
            }



        }
    }



    string day = a.substr(last_seen,a.size() - last_seen);

    if (day.size() != 2){
        cout << "False"; /// 2 символа
        return 0;
    }

    for(int i = 0; i < 2; ++i){
        if ( !(day[i]>= '0' && day[i]<= '9') ){
            cout << "False"; /// только цифры
            return 0;
        }
    }

    int num = atoi( day.c_str() );

    if (num == 0 || num > days_in_year(month__,vis)){
        cout << "False"; /// только цифры
        return 0;
    }

    cout << "True";

    ///cout << "{" <<day <<"}";
}
