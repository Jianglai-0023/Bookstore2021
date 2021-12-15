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
    Blocklist blocklist("books.index");
    int value;
    int n;
//    freopen("1.in", "r",stdin);
//    freopen("1.out","w",stdout);
    cin >> n;
    for(int i = 0; i < n; ++i){
        cin >> command ;
        if(command == "insert"){
            cin >> index >> value;
            //维护索引文件
            BlockNode node(value,index);
            blocklist.AddNode(node);
        }
        else if(command == "find"){
            answer.clear();
            cin >> index;
            blocklist.FindNode(index,answer);
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
            BlockNode node(value,index);
            blocklist.DeleteNode(node);
        }
    }

}
