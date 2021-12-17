#ifndef BOOKSTORE_USERMANAGER_H
#define BOOKSTORE_USERMANAGER_H

#include<cstring>
#include<iostream>
#include"file.h"
#include"blocklist.h"
using namespace std;

class UserSelect{
public:

    UserSelect();

    UserSelect(string id);

    ~UserSelect();
//private:
    char ID[31];

    int index_user;

    int priority;

    char isbn[21];

    int index_book;

    bool bookselected_ = false;

};

class User{
public:
    char ID_[31];

    char name_[31];

    char password_[31];

    int priority_;
//public:
    User();

    User(string id, string name, string password, int p);

    User(string name, string password, int p);

};

class Usersystem{
private:
    vector<class UserSelect> user_select_;

    File<User> file_user_data;

    Blocklist file_user_index;

    vector<int> users_key;
public:

    Usersystem();

    void Su(string user_ID, string password = "");

    void Logout();

    void Register(string user_ID, string password, string user_name);

    void Passwd(string user_ID, string new_password, string old_password = "");

    void UserAdd(string user_ID, string password, string priority, string user_name);

    void Delete(string user_ID);

    int Tell_priority();
};
#endif //BOOKSTORE_USERMANAGER_H
