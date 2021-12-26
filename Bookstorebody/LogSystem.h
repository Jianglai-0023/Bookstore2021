
#ifndef BOOKSTORE_LOGSYSTEM_H
#define BOOKSTORE_LOGSYSTEM_H
#include<iostream>
#include"file.h"
#include"blocklist.h"
#include<iomanip>
class Finance{
public:
    double money_;
    Finance(double money);
    Finance();
};
class LogSystem{
private:
    File<Finance> file_finance_data;
public:
    LogSystem();

    void ShowFinance(int time = -1);

    void AddFinance(double money);

    void remove();
};

#endif //BOOKSTORE_LOGSYSTEM_H
