#include"LogSystem.h"
#include"lubang.h"
LogSystem::LogSystem(): file_finance_data("finance_data") {}

Finance::Finance(float money):money_(money) {}
Finance::Finance(){};

void LogSystem::AddFinance(float money) {
    Finance f(money);
    file_finance_data.Add(f);
}

void LogSystem::ShowFinance(int time) {
    float input = 0, output = 0;
    if(time == -1){
        int tmp;
        file_finance_data.ReadInfo(tmp);
        int index = sizeof(int);
        for(int i = 0; i< tmp; ++i){
            Finance f;
            file_finance_data.Read(f,index);
            index += sizeof(Finance);
            if(f.money_ > 0) input += f.money_;
            else output += f.money_;
        }
    }
    if(time == 0){
        cout << endl;
    }
    else{
        int tmp;
        file_finance_data.ReadInfo(tmp);
        int index = sizeof(int) + (tmp - 1) * sizeof(Finance);
        if(tmp < time) throw Book_error("showfinance: timeout");
        for(int i = 0; i< time; ++i){
            Finance f;
            file_finance_data.Read(f,index);
            index -= sizeof(Finance);
            if(f.money_ > 0) input += f.money_;
            else output += f.money_;
        }
    }
    cout << '+' << ' ' << input << ' ' << '-' << ' ' << output << endl;
}