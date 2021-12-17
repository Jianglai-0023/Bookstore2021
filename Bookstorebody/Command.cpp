#include <string>
#include"Command.h"
#include "blocklist.h"
#include"usermanager.h"
#include"file.h"
#include "lubang.h"
//Book_error::Book_error():message("Invalid"){};

UserSelect::UserSelect(string id) {
    //todo
    strcpy(ID,id.c_str());
}

UserSelect::UserSelect() {}

UserSelect::~UserSelect() {}

CommandManager::CommandManager() {}


bool CommandManager::CheckPriority(string com) {
    if(com == "su"){
        return true;
    }
    if(com == "logout"){
       if(priority_now < 1) return false;
       return true;
    }
    else if(com == "register"){
       return true;
    }
    else if(com == "passwd"){
        if(priority_now < 1) return false;
        return true;
    }
    else if(com == "useradd"){
        if(priority_now < 3) return false;
        return true;
    }
    else if(com == "delete"){
        if(priority_now < 7) return false;
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
        priority_now = usersystem.Tell_priority();
        if(command_words[0] == "su"){
            if(!lubang_check.checkSentence(command_words)) throw Book_error();
            if(command_words.size() == 2){
                usersystem.Su(command_words[1]);
            }
            else {
                usersystem.Su(command_words[1],command_words[2]);
            }

        }
        else if(command_words[0] == "logout"){
            if(!lubang_check.checkSentence(command_words)) throw Book_error();
            if (!CheckPriority(command_words[0])) throw Book_error();
            else {
                usersystem.Logout();
            }
        }
        else if(command_words[0] == "register"){
            if(!lubang_check.checkSentence(command_words)) throw Book_error();
            if (!CheckPriority(command_words[0])) throw Book_error();
            else{
                usersystem.Register(command_words[1],command_words[2],command_words[3]);
            }
        }
        else if(command_words[0] == "passwd"){
            if(!lubang_check.checkSentence(command_words)) throw Book_error();
            if (!CheckPriority(command_words[0])) throw Book_error();
            else{
                if(command_words.size() == 4){
                    usersystem.Passwd(command_words[1],command_words[3],command_words[2]);
                }
                else{
                    usersystem.Passwd(command_words[1],command_words[2]);
                }
            }
        }
        else if(command_words[0] == "useradd"){
            if(!lubang_check.checkSentence(command_words)) throw Book_error();
            if (!CheckPriority(command_words[0])) throw Book_error();
            else{
               usersystem.UserAdd(command_words[1],command_words[2],command_words[3],command_words[4]);
            }
        }
        else if(command_words[0] == "delete"){
            //lubang
            if(!lubang_check.checkSentence(command_words)) throw Book_error();
            if (!CheckPriority(command_words[0])) throw Book_error();
            else{
                usersystem.Delete(command_words[1]);
            }

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
