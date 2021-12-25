#include <string>
#include"Command.h"
#include "blocklist.h"
#include"usermanager.h"
#include"file.h"
#include "lubang.h"
#include"LogSystem.h"

//UserSelect::UserSelect(string id) {
//    //todo
//    strcpy(ID,id.c_str());
//}

UserSelect::UserSelect() {}

UserSelect::~UserSelect() {}

CommandManager::CommandManager() {}

void CommandManager::Exit() {
    exit(0);
}

bool CommandManager::CheckPriority(string com) {
    if (com == "su") {
        return true;
    }
    if (com == "logout") {
        if (priority_now < 1) return false;
        return true;
    } else if (com == "register") {
        return true;
    } else if (com == "passwd") {
        if (priority_now < 1) return false;
        return true;
    } else if (com == "useradd") {
        if (priority_now < 3) return false;
        return true;
    } else if (com == "delete") {
        if (priority_now < 7) return false;
        return true;
    }
        //Booksystem
    else if (com == "show") {
        if (priority_now < 1) return false;
        return true;
    } else if (com == "buy") {
        if (priority_now < 1) return false;
        return true;
    } else if (com == "select") {
        if (priority_now < 3) return false;
        return true;
    } else if (com == "modify") {
if(priority_now < 3) return false;
return true;
    } else if (com == "import") {
        if (priority_now < 3) return false;
        return true;
    }
        //LogSystem
    else if (com == "report") {
        if (priority_now < 3) return false;
        return true;
    } else if (com == "show") {
        if (priority_now < 7) return false;
        return true;
    } else if (com == "log") {
        if (priority_now < 7) return false;
        return true;
    }
}

void CommandManager::DealString(string command) {
    command_words.clear();
    string word;
    int i = 0;
    //deal with sentence
    while (command[i] != '\0') {
        if (command[i] != ' ') {
            word += command[i];
            ++i;
        } else {
            if (!word.empty()) {
                command_words.push_back(word);
                word.clear();
            }
            while (command[i] == ' ') {
                ++i;
            }
        }
    }
    if (!word.empty()) command_words.push_back(word);

    word.clear();
}

string CommandManager::ReturnRight(string s) {
    string right;
    right.clear();
    bool flag = false;
    for (int i = 0; i < s.length(); ++i) {
        if (s[i] == '='){
            flag = true;
            continue;
        }
        if (!flag) continue;
        else {
            right += s[i];
        }
    }
    return right;
}

string CommandManager::ReturnLeft(string s) {
    string left;
    left.clear();
    for (int i = 0; i < s.length(); ++i) {
        if (s[i] == '=') break;
        else {
            left += s[i];
        }
    }
    return left;
}


int CommandManager::StringToInt(string q) {
    int ans = 0;
    for (int i = 0; i < q.length(); ++i) {
        ans *= 10;
        ans += q[i] - '0';
    }
    return ans;
}

void CommandManager::Run(string command) {
    DealString(command);
    //all blank space
    if (!command_words.size()) return;
        //RUN
    else {
        //UserManager
        priority_now = usersystem.Tell_priority();
        if (command_words[0] == "su") {
            if (!lubang_check.checkSentence(command_words)) throw Book_error("su_checkSen");
            if (command_words.size() == 2) {
                usersystem.Su(command_words[1]);
            } else {
                usersystem.Su(command_words[1], command_words[2]);
            }

        } else if (command_words[0] == "logout") {
            if (!lubang_check.checkSentence(command_words)) throw Book_error("log_checksen");
            if (!CheckPriority(command_words[0])) throw Book_error("log_pri");
            else {
                usersystem.Logout();
            }
        } else if (command_words[0] == "register") {
            if (!lubang_check.checkSentence(command_words)) throw Book_error("register_checkSen");
            if (!CheckPriority(command_words[0])) throw Book_error("register_prio");
            else {
                usersystem.Register(command_words[1], command_words[2], command_words[3]);
            }
        } else if (command_words[0] == "passwd") {
            if (!lubang_check.checkSentence(command_words)) throw Book_error("passwd_checkSen");
            if (!CheckPriority(command_words[0])) throw Book_error("check_prio");
            else {
                if (command_words.size() == 4) {
                    usersystem.Passwd(command_words[1], command_words[3], command_words[2]);
                } else {
                    usersystem.Passwd(command_words[1], command_words[2]);
                }
            }
        } else if (command_words[0] == "useradd") {
            if (!lubang_check.checkSentence(command_words)) throw Book_error("useradd_checkSen");
            if (!CheckPriority(command_words[0])) throw Book_error("useradd_prio");
            else {
                usersystem.UserAdd(command_words[1], command_words[2], command_words[3], command_words[4]);
            }
        } else if (command_words[0] == "delete") {
            //lubang
            if (!lubang_check.checkSentence(command_words)) throw Book_error("delete_checkSen");
            if (!CheckPriority(command_words[0])) throw Book_error("selete_prio");
            else {
                usersystem.Delete(command_words[1]);
            }
        }
            //Booksystem
        else if (command_words[0] == "show") {
            if (!lubang_check.checkSentence(command_words)) throw Book_error("show_checkSen");
            if (!CheckPriority(command_words[0])) throw Book_error("show_prio");
            else {
                if (command_words.size() == 1) booksystem.showAll();
                else if (command_words[1][1] == 'I')booksystem.showISBN(ReturnRight(command_words[1]));
                else if (command_words[1][1] == 'n')booksystem.showName(ReturnRight(command_words[1]));
                else if (command_words[1][1] == 'a')booksystem.showAuthor(ReturnRight(command_words[1]));
                else if (command_words[1][1] == 'k')booksystem.showKeyword(ReturnRight(command_words[1]));

            }
        } else if (command_words[0] == "buy") {
            if (!lubang_check.checkSentence(command_words)) throw Book_error("buy_checkSen");
            if (!CheckPriority(command_words[0])) throw Book_error("buy_prio");
            else {
                int quantity;
                quantity = StringToInt(command_words[2]);
                booksystem.Buy(command_words[1], quantity);
            }

        } else if (command_words[0] == "select") {
            if (!lubang_check.checkSentence(command_words)) throw Book_error("select_checkSen");
            if (!CheckPriority(command_words[0])) throw Book_error("select_prio");
            else {
                int index = booksystem.Select(command_words[1]);
                usersystem.UserSelectBook(index);
            }

        } else if (command_words[0] == "modify") {
            //todo
            if (!lubang_check.checkSentence(command_words)) throw Book_error("modify_checkSen");
            if (!CheckPriority(command_words[0])) throw Book_error("modify_prio");
            else {
                if (usersystem.BookNow() == -1) throw Book_error("modify: no book is selected");
                booksystem.Modify(command_words,usersystem.BookNow());

            }
        } else if (command_words[0] == "import") {
            if (!lubang_check.checkSentence(command_words)) throw Book_error("import_checkSen");
            if (!CheckPriority(command_words[0])) throw Book_error("import_prio");
            else {
                if (usersystem.BookNow() == -1) throw Book_error("import: no book is selected");
                int quantity = StringToInt(command_words[1]);
                booksystem.Import(quantity, usersystem.BookNow());
            }
        }
            //LogSystem
        else if (command_words[0] == "report") {
            if (!lubang_check.checkSentence(command_words)) throw Book_error("report_checkSen");
            if (!CheckPriority(command_words[0])) throw Book_error("report_prio");
            if(command_words[1] == "finance" || command_words[1] == "employee"){
                if (priority_now < 7) throw Book_error("report_prio");
            }
        } else if (command_words[0] == "show") {
            if (!lubang_check.checkSentence(command_words)) throw Book_error("show_checkSen");
            if (!CheckPriority(command_words[0])) throw Book_error("show_prio");
            if(command_words.size() == 3){
                logsystem.ShowFinance(StringToInt(command_words[3]));
            }
            else{
                logsystem.ShowFinance();
            }


        } else if (command_words[0] == "log") {

        } else if (command_words[0] == "exit") {
            Exit();
        }
            //no matching function
        else throw Book_error("wrong_command");
    }
};
