//
// Created by 蒋lai on 2021/12/16.
//

#ifndef BOOKSTORE_LUBANG_H
#define BOOKSTORE_LUBANG_H
#include<vector>
#include<cstring>
#include<iostream>

using namespace std;

class Book_error {
public:
    Book_error();

    Book_error(string s);

    string what() const { return message; }

private:
    string message;
};

class Lubang{

public:
    bool checkSentence(const vector<string> sentence);
    /* n == 0 ID,Passwd,
     * n == 1 UserName,ISBN
     * n == 2 priority,quantity;
     * n == 3 bookname,author
     * n == 4 price,total-cost
     * n == 5 keyword
     * */
    bool checkWord(const char c, int n);

    string ReturnLeft(string s);

    string ReturnRight(string s);

    void ReturnKeyWord(string s, std::vector<string> &word);

    double StringTodouble(string q);
};
#endif //BOOKSTORE_LUBANG_H
