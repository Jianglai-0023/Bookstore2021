#include <iostream>
#include "blocklist.h"
#include<fstream>
#include<cstring>
#include<vector>
#include<algorithm>


std::vector<int> answer;
using namespace std;
int main(){
    string command, index;
    Ull ull("books.index");
    int value;
    int n;
    cin >> n;
    for(int i = 0; i < n; ++i){
        cin >> command ;
        if(command == "insert"){
            cin >> index >> value;
            //维护索引文件
            UllNode node(value,index);
            ull.addNode(node);
        }
        else if(command == "find"){
            answer.clear();
            cin >> index;
            ull.findNode(index,answer);
            if(!answer.size()) cout << "null" << endl;
            else{
                for(auto iter= answer.begin(); iter != answer.end(); ++iter){
                    cout << *iter << ' ';
                }
                cout << '\n';
            }

        }
        else if(command == "delete"){
            cin >> index >> value;
            UllNode node(value,index);
            ull.deleteNode(node);
        }
//        else if(command == "test"){
//            Test();
//        }

    }

}
