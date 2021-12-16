#ifndef BOOKSTORE_FILE_H
#define BOOKSTORE_FILE_H
#include<fstream>
using namespace std;
template<class T, int n = 1>
class File{
public:
    File(string filename);

    void Read(T &value, int index);
    //write:include new and change, need check;
    int Write(T &value);

    void ReadInfo(int &tmp);

    void WriteInfo(int tmp);

private:
    fstream file_data;
};
#endif //BOOKSTORE_FILE_H
