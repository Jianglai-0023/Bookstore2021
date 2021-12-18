#ifndef BOOKSTORE_COMMAND_H
#define BOOKSTORE_COMMAND_H

#include<vector>
#include<cstring>
#include"file.h"
#include"lubang.h"
#include"usermanager.h"
#include"Booksystem.h"
using namespace std;
//class Book_error {
//public:
//    Book_error();
//
//    const char *what() const { return message; }
//
//private:
//    const char *message;
//};


//class UserSelect{
//public:
//
//    UserSelect();
//
//    UserSelect(string id);
//
//    ~UserSelect();
////private:
//    char ID[31];
//
//    int index_user;
//
//    int priority;
//
//    char isbn[21];
//
//    int index_book;
//
//    bool bookselected_ = false;
//
//};


class CommandManager{
private:
//    vector<class UserSelect> user_select;

    vector<string> command_words;

    Usersystem usersystem;

    BookSystem booksystem;

    Lubang lubang_check;

    //priority{0,1,3,7}
    //begin as 0;
    int priority_now = 0;

public:


    void Run(string command);

    void DealString(string c);

//    string SplitString(string &before, string after, int devidedbykey = 0);

    bool CheckPriority(string com);

    int stringToint(string q);

    int stringTodouble(string q);
//    bool CheckSentence(const vector<string> sentence);

    CommandManager();


    void Exit();
};
//bool Input(string command);





#endif //BOOKSTORE_COMMAND_H
