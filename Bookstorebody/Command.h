#ifndef BOOKSTORE_COMMAND_H
#define BOOKSTORE_COMMAND_H

#include<vector>
#include<cstring>
using namespace std;


class UserSelect{
public:
    char ID[30];

    int index_user;

    int priority;

    char isbn[20];

    int index_book;

    bool bookselected_ = false;

    UserSelect();

    UserSelect(string id);

    ~UserSelect();
};


class CommandManager{
private:
    vector<class UserSelect> userselect;

    vector<string> command_words;

public:
    void Run(string command);

    string SplitString(string &before, string after, int devidedbykey = 0);

    bool CheckPriority(UserSelect);

    CommandManager();

    ~CommandManager();

    void Exit();
};
//bool Input(string command);





#endif //BOOKSTORE_COMMAND_H
