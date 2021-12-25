#include"usermanager.h"
#include"lubang.h"

User::User(string id, string password, string priority, string name) {

    strcpy(ID_, id.c_str());

    strcpy(name_, name.c_str());

    strcpy(password_, password.c_str());

    char p = priority[0];

    priority_ = p - '0';
};

User::User(string id, string password, int priority, string name) {

    strcpy(ID_, id.c_str());

    strcpy(name_, name.c_str());

    strcpy(password_, password.c_str());

    priority_ = priority;
};

User::User() {}

Usersystem::Usersystem() : file_user_data("./user_data"), file_user_index("./user_index") {
    User root("root", "sjtu", 7, "root");
    BlockNode root_;
    strcpy(root_.str, "root");
    root_.position = file_user_data.Add(root);
    file_user_index.AddNode(root_);
    //debug
//    vector<int> debug;
//    file_user_index.FindNode("root", debug);
//    cout << "test root" << debug[0] << endl;
    file_user_data.Add(root);
};

int Usersystem::BookNow() {
    if (!user_select_[user_select_.size() - 1].bookselected_) return -1;
    return user_select_[user_select_.size() - 1].index_book;
}

int Usersystem::Tell_priority() {
    if (user_select_.empty()) return 0;
    return user_select_[user_select_.size() - 1].priority;
}

void Usersystem::Su(string user_ID, string password) {
    /*lu bang
     * priority-passward
     * exist
     * 
     * */
    //find person
    User user_be_sued;
    UserSelect user_select;
    users_key.clear();
    file_user_index.FindNode(user_ID, users_key);
    if (users_key.empty()) throw Book_error("su: user unexisted");
    file_user_data.Read(user_be_sued, users_key[0]);
    //check passwd
    if (Tell_priority() > user_be_sued.priority_) {
        strcpy(user_select.ID, user_ID.c_str());
        user_select.priority = user_be_sued.priority_;
        user_select.index_user = users_key[0];
        user_select_.push_back(user_select);
    } else if (strcmp(user_be_sued.password_, password.c_str()) == 0) {
        strcpy(user_select.ID, user_ID.c_str());
        user_select.priority = user_be_sued.priority_;
        user_select.index_user = users_key[0];
        user_select_.push_back(user_select);
    } else throw Book_error("su: wrong passwd");
};

void Usersystem::Logout() {
    if (user_select_.empty()) throw Book_error("logout: empty");
    user_select_.pop_back();//priority now?//todo
}

void Usersystem::Register(string user_ID, string password, string user_name) {
    users_key.clear();
    file_user_index.FindNode(user_ID, users_key);
    if (!users_key.empty()) throw Book_error("register: user repeated");
    User user_register(user_ID, password, 1, user_name);
    BlockNode usernode;
    usernode.position = file_user_data.Add(user_register);
    strcpy(usernode.str,user_ID.c_str());
    file_user_index.AddNode(usernode);
}

void Usersystem::Passwd(string user_ID, string new_password, string old_password) {
    users_key.clear();
    file_user_index.FindNode(user_ID, users_key);
    if (users_key.empty()) throw Book_error("passwd: no user find");
    User user_passwd;
    file_user_data.Read(user_passwd, users_key[0]);
    if (Tell_priority() == 7) {
        strcpy(user_passwd.password_, new_password.c_str());
        file_user_data.Write(user_passwd, users_key[0]);
    } else {
        if (old_password == "") throw Book_error("passwd: need old passwd");
        if (strcmp(user_passwd.password_, old_password.c_str()) == 0) {
            strcpy(user_passwd.password_, new_password.c_str());
            file_user_data.Write(user_passwd, users_key[0]);
        } else throw Book_error("passwd: wrong passwd");
    }
}

void Usersystem::UserAdd(string user_ID, string password, string priority, string user_name) {
    int priority_now = Tell_priority();
    char p_new = priority[0];
//    strcpy(p,priority.c_str());
//cout << p_new - '0' << "&&" << endl;
//cout << priority_now << "here" <<endl;
    if (priority_now <= p_new - '0') throw Book_error("useradd: low priority");
    else {
        UserSelect add_user;
        users_key.clear();
        file_user_index.FindNode(user_ID, users_key);
        if (users_key.empty()) {
            User new_user(user_ID, password, priority, user_name);
            BlockNode new_user_index;
            new_user_index.position = file_user_data.Add(new_user);
            strcpy(new_user_index.str, user_ID.c_str());
            file_user_index.AddNode(new_user_index);
        } else throw Book_error("useradd: user repeated");
    }
}

void Usersystem::Delete(string user_ID) {
    bool find = false;
    for (int i = 0; i < user_select_.size(); ++i) {
        if (strcmp(user_select_[i].ID, user_ID.c_str()) == 0) find = true;
    }
    if (find) throw Book_error("delete:user is online");
    users_key.clear();
    file_user_index.FindNode(user_ID, users_key);
    if (users_key.empty()) throw Book_error("delete: userID is empty");
    BlockNode user_delete;
    strcpy(user_delete.str, user_ID.c_str());
    user_delete.position = users_key[0];
    file_user_index.DeleteNode(user_delete);
}

void Usersystem::UserSelectBook(int book_index) {
    user_select_[user_select_.size() - 1].index_book = book_index;
    user_select_[user_select_.size() - 1].bookselected_ = true;
}
