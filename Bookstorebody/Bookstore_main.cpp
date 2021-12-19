#include"lubang.h"
#include "blocklist.h"
#include "Command.h"
#include"file.h"
#include<fstream>
#include<cstring>
#include<vector>
#include<algorithm>
#include <iostream>

using namespace std;

int main() {
    string command;
    CommandManager commandManager;
    while (getline(cin, command)) {
        try {
            commandManager.Run(command);
        }
        catch (Book_error er) {
            cout << "Error:" << er.what() << endl;
        }
    };
}