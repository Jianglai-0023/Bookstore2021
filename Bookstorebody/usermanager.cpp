#include"usermanager.h"

User::User(string id, string name, string password, int p){
     strcpy(ID_,id.c_str());
    strcpy(name_,name.c_str());
    strcpy(password_,password.c_str());
    priority_ = p;
};
