
#ifndef BOOKSTORE_LOGSYSTEM_H
#define BOOKSTORE_LOGSYSTEM_H
#include<iostream>
#include"file.h"
#include"blocklist.h"
class Finance{
public:
    float money_;
    Finance(float money);
    Finance();
};
class LogSystem{
private:
    File<Finance> file_finance_data;
public:
    LogSystem();

    void ShowFinance(int time = -1);

    void AddFinance(float money);
};

#endif //BOOKSTORE_LOGSYSTEM_H