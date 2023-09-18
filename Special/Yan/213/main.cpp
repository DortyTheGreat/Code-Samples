#include <iostream>

using namespace std;

struct BoreNode{
    BoreNode* childs[30];

    bool hasEnd = false;

    BoreNode(){
        for(int i = 0; i < 30; ++i){
            childs[i] = nullptr;
        }
        hasEnd = false;
    }

};

int main()
{
    int n;
    cin >> n;

    BoreNode* root = new BoreNode();
    BoreNode* temp;

    int answer = 0;

    for(int i = 0;i < n; ++i){
        string s;
        cin >> s;
        temp = root;
        bool not_found = false;
        int index = -1;
        for(int j = 0; j < s.size(); ++j){
            //cout << j << endl;
            if (temp->childs[s[j]-'a' ] == nullptr ){

                temp->childs[s[j]-'a' ] = new BoreNode();
                not_found = true; /// такого слова в словаре не было
            }else{
                int connections = 0;

                for(int c = 0; c < 30; ++c){
                    if (temp->childs[c] != nullptr) ++connections;
                }
                if (temp->hasEnd) ++connections;

                //cout << "con:" << connections << endl;
                if (connections == 1){
                    if (index == -1){
                        index = j;
                    }else{
                        /// не обновляй индекс
                    }
                }else{
                    index = -1;
                }
            }


            temp = temp->childs[s[j]-'a'];


            if (j == s.size() - 1){
                temp->hasEnd = true;



                if (!not_found){
                    int connections = 0;

                    for(int c = 0; c < 30; ++c){
                        if (temp->childs[c] != nullptr) ++connections;
                    }
                    if (temp->hasEnd) ++connections;

                    //cout << "con:" << connections << endl;
                    if (connections == 1){
                        if (index == -1){
                            index = j+1;
                        }else{
                            /// не обновляй индекс
                        }
                    }else{
                        index = -1;
                    }
                }





                /// TO-DO
            }
        }

        if (not_found){
            answer += s.size();
            //cout << s.size() << endl;
        }else{
            if (index == -1){
                //cout << s.size() << endl;
                answer += s.size();
            }else{
                if (index == 0){
                    answer += 1;
                    //cout << 1 << endl;
                }else{
                    answer += index;
                    //cout << index << endl;
                }

            }

        }

    }

    cout << answer << endl;
    return 0;
}
