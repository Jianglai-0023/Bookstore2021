#include <string>
#include"Command.h"

UserSelect::UserSelect(string id) {
    strcpy(ID,id.c_str());
}

UserSelect::UserSelect() {}

UserSelect::~UserSelect() {}

void CommandManager::Run(string command){
    string word;
    for(int i = 0; i < command.length(); ++i){
        if(command[i] != ' '){
          word += command[i];
        }
    }
};
