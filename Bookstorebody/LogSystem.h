
#ifndef BOOKSTORE_LOGSYSTEM_H
#define BOOKSTORE_LOGSYSTEM_H
#include<iostream>
#include"file.h"
#include"blocklist.h"
#include<iomanip>
class Finance{
public:
    double money_;
    char isbn_[21];
    Finance(double money,string isbn);
    Finance();
};
class Staff{
public:
    Staff(string ID, string command);
    Staff();
    char  ID_[31];
    char command_[10];
};
class LogSystem{
private:
    File<Finance> file_finance_data;
    File<Staff> file_staff_data;
    Blocklist file_staff_index;
public:
    LogSystem();

    void ShowFinance(int time = -1);

    void AddFinance(double money,string isbn);

    void AddLog(string command,string staff = "");

    void ReportFinance();

    void ReportMe(string ID);

    void ReportEmployee();

    void Report();


};

#endif //BOOKSTORE_LOGSYSTEM_H
