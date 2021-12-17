#include"usermanager.h"
#include"lubang.h"
User::User(string id, string name, string password, int p) {

    strcpy(ID_, id.c_str());

    strcpy(name_, name.c_str());

    strcpy(password_, password.c_str());

    priority_ = p;
};

Usersystem::Usersystem(): file_user_data("user_data"), file_user_index("user_index"){};

int Usersystem::Tell_priority() {
    return user_select_[user_select_.size() - 1].priority;
}
void Usersystem::Su(string user_ID, string password){
    /*lu bang
     * priority-passward
     * exist
     * 
     * */
    //find person
    User user_be_sued;
    UserSelect user_select;
    users_key.clear();
    file_user_index.FindNode(user_ID,users_key);
    if(users_key.empty()) throw Book_error();
    file_user_data.Read(user_be_sued,users_key[0]);
    //check passwd
    if(user_select_[user_select_.size() - 1].priority > user_be_sued.priority_){
        strcpy(user_select.ID,user_ID.c_str());
        user_select.priority = user_be_sued.priority_;
        user_select.index_user = users_key[0];
        user_select_.push_back(user_select);
    }
    else if(strcmp(user_be_sued.password_, password.c_str()) == 0){
        strcpy(user_select.ID,user_ID.c_str());
        user_select.priority = user_be_sued.priority_;
        user_select.index_user = users_key[0];
        user_select_.push_back(user_select);
    }
    else throw Book_error();
};

void Usersystem::Logout() {
    if(users_key.empty()) throw Book_error();
    users_key.pop_back();//priority now?//todo
}
void Usersystem::Register(string user_ID, string password, string user_name) {
    User user_register;
    int tmp;
    users_key.clear();
    file_user_index.FindNode(user_ID,users_key);
    if(!users_key.empty()) throw Book_error();
    user_register.priority_ = 1;
    strcpy(user_register.password_,password.c_str());
    strcpy(user_register.ID_,user_ID.c_str());
    strcpy(user_register.name_,user_name.c_str());
    file_user_data.Add(user_register);
}
void Usersystem::UserAdd(string user_ID, string password, string priority, string user_name) {
    int priority_now = Tell_priority();
    char p_new = priority[0];
//    strcpy(p,priority.c_str());
    if(priority_now <= p_new - '0') throw Book_error();
    else{
        UserSelect add_user;
        users_key.clear();
        file_user_index.FindNode(user_ID,users_key);
        if(users_key.empty()){
            User new_user;
            BlockNode new_user_index;
            strcpy(new_user.ID_,user_ID.c_str());
            strcpy(new_user.password_,password.c_str());
            new_user.priority_ = p_new - '0';
            strcpy(new_user.name_,user_name.c_str());
            new_user_index.position = file_user_data.Add(new_user);
            strcpy(new_user_index.str,user_ID.c_str());
            file_user_index.AddNode(new_user_index);
        }
        else throw Book_error();
    }
}
void Usersystem::Delete(string user_ID) {
    bool find = false;
    for(int i = 0; i < user_select_.size(); ++i){
       if(strcmp(user_select_[i].ID,user_ID.c_str()) == 0) find = true;
    }
    if(find) throw Book_error();
    users_key.clear();
    file_user_index.FindNode(user_ID,users_key);
    if(users_key.empty()) throw Book_error();
    BlockNode user_delete;
    strcpy(user_delete.str,user_ID.c_str());
    user_delete.position = users_key[0];
    file_user_index.DeleteNode(user_delete);
}


