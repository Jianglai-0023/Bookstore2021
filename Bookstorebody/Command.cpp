#include <string>
#include"Command.h"
#include "blocklist.h"
#include"usermanager.h"
#include"file.h"
#include "lubang.h"
Book_error::Book_error():message("Invalid"){};

UserSelect::UserSelect(string id) {
    //todo
    strcpy(ID,id.c_str());
}

UserSelect::UserSelect() {}

UserSelect::~UserSelect() {}

void CommandManager::Init() {
    //add root
    User root("root", "root", "sjtu", 7);
    //add root to file
    File user("userbasic.dat");
    Blocklist index_user("index_id");
    user.W

    BlockNode rootnode;
    index_user.AddNode();


}


bool CommandManager::CheckPriority(string com) {
    if(com == "su"){

    }
    else if(com == "logout"){
       if(priority_now < 1) return false;
       if(user_select.empty()) return false;
       return true;
    }
    else if(com == "register"){

    }
    else if(com == "passwd"){

    }
    else if(com == "useradd"){

    }
    else if(com == "delete"){
        if(priority_now != 7) return false;
        return true;
    }
        //Booksystem
    else if(com == "show"){

    }
    else if(com == "buy"){

    }
    else if(com == "select"){

    }
    else if(com == "modify"){

    }
    else if(com == "import"){

    }
        //LogSystem
    else if(com == "report"){

    }
    else if(com == "show"){

    }
    else if(com == "log"){

    }
}

void CommandManager::Run(string command){
    Lubang lubang_check;
    command_words.clear();
    string word;
    int i = 0;
    //deal with sentence
    while(command[i] != '\0'){
        if(command[i] != ' '){
          word += command[i];
          ++i;
        }
        else{
            if(!word.empty()){
                command_words.push_back(word);
                word.clear();
            }
            while(command[i] == ' '){
                ++i;
            }
        }
    }
    //all blank space
    if(!command_words.size()) return;
    //run
    else{
        //UserManager
        if(command_words[0] == "su"){

        }
        else if(command_words[0] == "logout"){
            if(!lubang_check.checkSentence(command_words)) throw Book_error();
            if (!CheckPriority(command_words[0])) throw Book_error();
            else {
                user_select.pop_back();
                priority_now = user_select[user_select.size() - 1].priority;
            }
        }
        else if(command_words[0] == "register"){

        }
        else if(command_words[0] == "passwd"){

        }
        else if(command_words[0] == "useradd"){

        }
        else if(command_words[0] == "delete"){
            //lubang
            if(user_select.size() != 2) throw Book_error();
            if (!CheckPriority(command_words[0])) throw Book_error();

        }
        //Booksystem
        else if(command_words[0] == "show"){

        }
        else if(command_words[0] == "buy"){

        }
        else if(command_words[0] == "select"){

        }
        else if(command_words[0] == "modify"){

        }
        else if(command_words[0] == "import"){

        }
        //LogSystem
        else if(command_words[0] == "report"){

        }
        else if(command_words[0] == "show"){

        }
        else if(command_words[0] == "log"){

        }
        //no matching function
        else throw Book_error();
    }
};
