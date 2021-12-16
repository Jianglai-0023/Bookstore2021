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
    File user("userbasic.dat");
    Blocklist index_user("index_id");
    getline(cin, command);
    try {
    commandManager.Run(command);
    }
    catch (Book_error er) {
        er.what();
    }

}