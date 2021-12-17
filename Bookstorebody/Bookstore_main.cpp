#include <iostream>
#include "blocklist.h"
#include "Command.h"
#include"file.h"
#include<fstream>
#include<cstring>
#include<vector>
#include<algorithm>

using namespace std;


int main() {
    string command;
    CommandManager commandManager;
    getline(cin, command);
    try {
    commandManager.Run(command);
    }
    catch (Book_error er) {
        er.what();
    }

}