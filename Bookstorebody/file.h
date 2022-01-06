#ifndef BOOKSTORE_FILE_H
#define BOOKSTORE_FILE_H
#include<fstream>
#include<cstring>
#include<iostream>
//#include"usermanager.h"
using namespace std;
template<class T, int n = 1>
class File{
private:
    fstream file;
    const string file_name_;
    int sizeofInt = sizeof(int);
    int sizeofT = sizeof(T);
public:

    File(string file_name):file_name_(file_name){
        Initialize();
    };
~File(){
    file.close();
}
void remove(){
//    file.close();
//    file.open(file_name_,ios::out);
//    file.close();
//    file.open(file_name_);
}
    void Initialize(){
        file.open(file_name_,ios::out|ios::in|ios::binary);
        if (!file.good()) {
            file.open(file_name_, ios::out);
            file.close();
            file.open(file_name_,ios::out|ios::in|ios::binary);
            WriteInfo(0);
        }
//        file.close();

    }

    void Read(T &value, int index){
        file.close();
        file.open(file_name_,ios::out|ios::in|ios::binary);
//        file.open(file_name_);
        file.seekg(index);
        file.read(reinterpret_cast<char *>(&value),sizeof(T));
//        file.close();
    };
    //write:include new and change, need check;
    void Write(T &value,int index){
        file.close();
        file.open(file_name_,ios::out|ios::in|ios::binary);
        file.seekg(index);
        file.write(reinterpret_cast<char *>(&value),sizeof(T));

    };
    int Add(T &value){
//        cout << file.fail() << "here"<< endl;
        file.close();
//        file.open(file_name_,ios::binary);
        file.open(file_name_,ios::in|ios::out|ios::binary);
        file.clear();
//        cout << file.fail() << "HI"<< endl;
        int tmp;
        int index;
//        cout << file.fail() << "##" << endl;
        ReadInfo(tmp);
//        cout << file.fail() << "!!" << endl;
//        index = tmp * sizeof(T) + sizeofInt;
//        cout << tmp << "$tmp$ " << index << " " << sizeofT << "%sizeofT%" << endl;

//        file.open(file_name_);

        file.seekp(0,ios::end);
//        cout << file.fail() << "**" << endl;
        index = file.tellp();
//        cout << file.fail() << "@@" << endl;
//        cout << file.fail() << "%%" << endl;
        file.write(reinterpret_cast<char *>(&value),sizeof(T));
        ++tmp;
//        file.close();
        WriteInfo(tmp);
        return index;
    }

   void  ReadInfo(int &tmp){
//        file.open(file_name_);
//       cout << file.fail() << "((" << endl;
        file.seekg(0);
//       cout << file.fail() << "~~" << endl;
//       cout << tmp << "TMP" << endl;
//       cout << sizeofInt << endl;
        file.read(reinterpret_cast<char *>(&tmp),sizeofInt);
//       cout << file.fail() << "??" << endl;
//        file.close();
    };

    void WriteInfo(int tmp){
//        file.open(file_name_);

        file.seekg(0);

        file.write(reinterpret_cast<char *>(&tmp),sizeofInt);
//        file.close();
    };

};
#endif //BOOKSTORE_FILE_H
