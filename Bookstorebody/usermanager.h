#ifndef BOOKSTORE_USERMANAGER_H
#define BOOKSTORE_USERMANAGER_H

#include<cstring>
#include<iostream>
using namespace std;
class User{
private:
    char ID_[31];

    char name_[31];

    char password_[31];

    int priority_;
public:
    User();

    User(string id, string name, string password, int p);

    User(string name, string password, int p);

};

















#endif //BOOKSTORE_USERMANAGER_H
