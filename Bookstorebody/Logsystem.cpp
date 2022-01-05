#include"LogSystem.h"
#include"lubang.h"
LogSystem::LogSystem(): file_finance_data("./rundata/finance_data"), file_staff_data("./rundata/staff_data"),
                        file_staff_index("./rundata/staff_index") {}
//LogSystem::LogSystem(): file_finance_data("finance_data"), file_staff_data("staff_data"),
//                        file_staff_index("staff_index") {}
Finance::Finance(double money,string book):money_(money) {
    strcpy(isbn_,book.c_str());
}
Finance::Finance(){};

void LogSystem::AddFinance(double money,string isbn) {
//    cout << "add finance" << money
    Finance f(money,isbn);
    file_finance_data.Add(f);
}

Staff::Staff(){}

void LogSystem::ShowFinance(int time) {
    double input = 0, output = 0;
    if(time == -1){
        int tmp;
        file_finance_data.ReadInfo(tmp);
        int index = sizeof(int);
        for(int i = 0; i< tmp; ++i){
            Finance f;
            file_finance_data.Read(f,index);
            index += sizeof(Finance);
//            cout << "ORZ show finance" << f.money_ << endl;
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
//        cout << tmp <<"&&&" <<endl;
//        cout << time << "%%%" << endl;
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
    cout << '+' << ' ' ;
    cout << setiosflags(std::ios::fixed) << setprecision(2) << input;
    cout << ' ' << '-' << ' ' ;
    if(output == 0) cout << "0.00"<< endl;
    else{
        output*=-1;
        cout << setiosflags(std::ios::fixed) << setprecision(2) << output << endl;
    }
}
 Staff::Staff(string ID,string command){
    strcpy(ID_,ID.c_str());
    strcpy(command_,command.c_str());
}
void LogSystem::AddLog(string staff, string command) {
    if(command == "") return;
    Staff newstaff(staff,command);
    int index = file_staff_data.Add(newstaff);
    BlockNode node(index,staff);
    file_staff_index.AddNode(node);
}

void LogSystem::ReportFinance() {
    cout << "📚Book\t" << "input/output📚" << '\n';
    cout << "---------------------------------\n";
    int tmp;
    file_finance_data.ReadInfo(tmp);
    int index = sizeof(int);
    for (int i = 0; i < tmp; ++i) {
        Finance f;
        file_finance_data.Read(f, index);
        index += sizeof(Finance);
        cout << f.isbn_ << '\t' << setiosflags(std::ios::fixed) << setprecision(2) << f.money_ << endl;
    }
    cout << "📚---------------------------------📚\n";
}

void LogSystem::Report() {
    cout << "📚Book\t" << "input/output📚" << '\n';
    cout << "---------------------------------\n";
    int tmp;
    file_finance_data.ReadInfo(tmp);
    int index = sizeof(int);
    for (int i = 0; i < tmp; ++i) {
        Finance f;
        file_finance_data.Read(f, index);
        index += sizeof(Finance);
        cout << f.isbn_ << '\t' << setiosflags(std::ios::fixed) << setprecision(2) << f.money_ << endl;
    }
    cout << "📚---------------------------------📚\n";
    cout << "🥸EMPLOYEE🥸" << endl;
    cout << "---------------------------------\n";
    file_staff_data.ReadInfo(tmp);
    index = sizeof(int);
    for (int i = 0; i < tmp; ++i) {
        Staff st;
        file_staff_data.Read(st, index);
        index += sizeof(Staff);
        cout << st.ID_ << '\t' << st.command_ << endl;
    }
    cout << "🥸---------------------------------🥸\n";
}
void LogSystem::ReportEmployee() {
    int tmp;
    cout << "🥸EMPLOYEE🥸" << endl;
    cout << "---------------------------------\n";
    file_staff_data.ReadInfo(tmp);
    int index = sizeof(int);
    for (int i = 0; i < tmp; ++i) {
        Staff st;
        file_staff_data.Read(st, index);
        index += sizeof(Staff);
        cout << st.ID_ << '\t' << st.command_ << endl;
    }
    cout << "🥸---------------------------------🥸\n";
}
void LogSystem::ReportMe(string ID) {
vector<int> key;
cout << "😎EMPLOYEE-ME😎" << endl;
cout << "---------------------------------\n";
file_staff_index.FindNode(ID,key);
for(int i = 0; i < key.size(); ++i){
    Staff sta;
file_staff_data.Read(sta,key[i]);
cout << sta.ID_ << '\t' << sta.command_ << endl;
}
cout << "😎---------------------------------😎\n";

}



