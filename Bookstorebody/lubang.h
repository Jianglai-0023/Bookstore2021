//
// Created by 蒋lai on 2021/12/16.
//

#ifndef BOOKSTORE_LUBANG_H
#define BOOKSTORE_LUBANG_H
#include<vector>
#include<cstring>
#include<iostream>

using namespace std;
class Lubang{

public:
    bool checkSentence(const vector<string> sentence);
    /* n == 0 ID,Passwd,
     * n == 1 UserName
     * n == 2 priority;
     * */
    bool checkWord(const char c, int n);
};
#endif //BOOKSTORE_LUBANG_H
