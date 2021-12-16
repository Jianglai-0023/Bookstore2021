#include <string>
#include"Command.h"
#include "blocklist.h"
#include"usermanager.h"
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
    Blocklist user("userbasic.dat");
    Blocklist index_user("index_id");
    user.AddNode()


}

void CommandManager::Run(string command){
    command_words.clear();
    string word;
    int i = 0;
    while(command[i] != '\0'){
        if(command[i] != ' '){
          word += command[i];
          ++i;
        }
        else{
            if(!word.empty()){
                word += '\0';
                command_words.push_back(word);
                word.clear();
            }
            while(command[i] == ' '){
                ++i;
            }
        }
    }
    //鲁棒性
    if(!command_words.size()) return;
    else{
        if(command_words[0] == "su"){

        }
    }
};
