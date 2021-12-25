#ifndef BOOKSTORE_FILE_H
#define BOOKSTORE_FILE_H
#include<fstream>
using namespace std;
template<class T, int n = 1>
class File{
private:
    fstream file;
    const string file_name_;
    int sizeofInt = sizeof(int);
public:

    File(string file_name):file_name_(file_name){
        Initialize();
    };
~File(){
    file.close();
}
    void Initialize(){
//        file.open(file_name_);
//        if (!file.good()) {
            file.open(file_name_, ios::out);
            file.close();
            file.open(file_name_);

//        }
//        file.close();
        WriteInfo(0);
    }

    void Read(T &value, int index){
//        file.open(file_name_);
        file.seekg(index);
        file.read(reinterpret_cast<char *>(&value),sizeof(T));
//        file.close();
    };
    //write:include new and change, need check;
    void Write(T &value,int index){
//        file.open(file_name_);
        file.seekg(index);
        file.write(reinterpret_cast<char *>(&value),sizeof(T));
//        file.close();
    };
    int Add(T &value){
        int tmp;
        int index;
        ReadInfo(tmp);
        index = tmp * sizeof(T) + sizeofInt;
//        file.open(file_name_);
        file.seekg(index);
        file.write(reinterpret_cast<char *>(&value),sizeof(T));
        ++tmp;
//        file.close();
        WriteInfo(tmp);
        return index;
    }

   void  ReadInfo(int &tmp){
//        file.open(file_name_);
        file.seekg(0);
        file.read(reinterpret_cast<char *>(&tmp),sizeofInt);
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
