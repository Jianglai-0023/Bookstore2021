#include"blocklist.h"
#include<cstring>
#include<fstream>
#include<algorithm>
#include<cstring>
using namespace::std;

fstream fileIndex;

int addNums = 0;
int sizeofBlock = sizeof(UllBlock);
int blockNum = 1;
Ull::Ull(const std::string &arg):file_name(arg){};
inline int Ull:: nextBlock(const int &offset){

};

inline void Ull::delBlock(const int &offset){

};

void Ull::mergeBlock(const int &offset1, const int &offset2){

};

void Ull::splitBlock(const int &offset){

};

void Ull::addNode(const UllNode &node){
    //分块操作
    fileIndex.open("books.index");
    if(fileIndex.eof()){//第一个block
        UllBlock block;
        block.array[block.num] = node;
        block.num += 1;
        sort(block.array,block.array + block.num);//维护数组有序
        fileIndex.write(reinterpret_cast<char *>(&block),sizeofBlock);
    }
    else if()
fileIndex.close();
};

void Ull::findNode(const std::string &key, std::vector<int> &array){
       fileIndex.open("books.index");
};
UllNode::UllNode(const int &arg1, const std::string &arg2){
    position = arg1;
    strcpy(str,arg2.c_str());
}
bool UllNode::operator<(const UllNode &x) const{
        if(this->str != x.str) return !(strcmp(this->str,x.str));
        return this->position < x.position;
};
int Ull::deleteNode(const UllNode &node){

};