#include <iostream>
#include "blocklist.h"
#include "Command.h"
#include<fstream>
#include<cstring>
#include<vector>
#include<algorithm>

using namespace std;

class Book_error {
public:
    Book_error() : message("Invalid") {}

    const char *what() const { return message; }

private:
    const char *message;
};

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