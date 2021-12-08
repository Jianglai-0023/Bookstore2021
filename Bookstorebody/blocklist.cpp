#include"blocklist.h"
#include<cstring>
#include<fstream>
#include<algorithm>
#include<cstring>

using namespace ::std;

fstream fileIndex;

int addNums = 0;
int sizeofBlock = sizeof(UllBlock);
int totalblock = 0;

Ull::Ull(const std::string &arg) : file_name(arg) {
    fileIndex.open(file_name);
};
Ull::~Ull(){
    fileIndex.close();
}
inline int Ull::nextBlock(const int &offset) {

};

inline void Ull::delBlock(const int &offset) {

};

void Ull::mergeBlock(const int &offset1, const int &offset2) {

};

void Ull::splitBlock(const int &offset) {//文件已打开
    UllBlock block, newblock;
    UllNode node;
fileIndex.seekg(offset);//移动指针到指定位置
fileIndex.read(reinterpret_cast<char *>(&block), sizeofBlock);
int nums = block.num / 2;
   for(int i = nums; i < block.num; ++i){//复制过程
    newblock.array[i - nums] = block.array[i];
    block.array[i] = node;
   }
    //修改元素数量
   newblock.num = block.num - nums;
   block.num = nums;
   //改变节点
   newblock.nxt = block.nxt;
   newblock.pre = offset;
   fileIndex.seekg(0,ios::end);
   block.nxt =fileIndex.tellg();/*//todo*/
   //写入两个block
   fileIndex.seekg(offset);
   fileIndex.write(reinterpret_cast<char *>(&block), sizeofBlock);
   fileIndex.seekg(0,ios::end);
   fileIndex.write(reinterpret_cast<char *>(&newblock), sizeofBlock);
};

void Ull::addNode(const UllNode &node) {
    //分块操作
//    fileIndex.open("books.index");
    UllBlock block;
    UllBlock block1, block2;
    if (totalblock == 0) {//第一个block
        block.pre = 0;
        block.array[block.num] = node;
        ++totalblock;
        ++block.num;
        sort(block.array, block.array + block.num);//维护数组有序
        fileIndex.write(reinterpret_cast<char *>(&block), sizeofBlock);
    } else if(totalblock == 1) {//只有一个block
        fileIndex.read(reinterpret_cast<char *>(&block), sizeofBlock);
        block.array[block.num] = node;
        ++block.num;
        sort(block.array, block.array + block.num);
        fileIndex.write(reinterpret_cast<char *>(&block), sizeofBlock);
        if(block.num > BLOCK_SPLIT_THRESHOLD){
            splitBlock(1);
        }
    }else{//遍历链表头
        //特判：node比第一个链表头小
        fileIndex.seekg(0);
        fileIndex.read(reinterpret_cast<char *>(&block1), sizeofBlock);
        if(node < block1.array[0]){
            block1.array[block.num] = node;
            ++block1.num;
        }
        //正常遍历
        else {
            fileIndex.seekg(0);
            for (int i = 0; i < totalblock - 1; ++i) {
                fileIndex.read(reinterpret_cast<char *>(&block1), sizeofBlock);
                int index = block1.nxt;
                fileIndex.seekg(index);
                fileIndex.read(reinterpret_cast<char *>(&block2), sizeofBlock);
                if (node > block1.array[0] && node < block2.array[0]){
                    block1.array[block1.num] = node;
                    ++block1.num;
                    fileIndex.seekg(block2.pre);
                    fileIndex.write(reinterpret_cast<char *>(&block1), sizeofBlock);
                    if(block1.num > BLOCK_SPLIT_THRESHOLD){
                        splitBlock(block2.pre);
                    }
                    break;
                }
                else if(i != totalblock - 2){
                    fileIndex.seekg(block2.nxt);
                }
                else{//特判：只能插入最后一个block
                    block2.array[block2.num] = node;
                    ++block2.num;
                    fileIndex.seekg(block1.nxt);
                    fileIndex.write(reinterpret_cast<char *>(&block2), sizeofBlock);
                    if(block2.num > BLOCK_SPLIT_THRESHOLD){
                        splitBlock(block1.nxt);
                    }
                }
            }
        }
    }
};

void Ull::findNode(const std::string &key, std::vector<int> &array) {
    UllBlock block;
    fileIndex.read(reinterpret_cast<char *>(&block),sizeofBlock);
//    while(!(block.array[0] < key && block.array[block.num - 1] > node))

};

UllNode::UllNode(const int &arg1, const std::string &arg2) {
    position = arg1;
    strcpy(str, arg2.c_str());
}

bool UllNode::operator<(const UllNode &x) const {
    if (this->str != x.str) {
        if (strcmp(this->str, x.str) < 0) {
            return true;
        }
        return false;
    }
    return this->position < x.position;
};

bool UllNode::operator>(const UllNode &x) const {
    if (this->str != x.str) {
        if (strcmp(this->str, x.str) < 0) {
            return false;
        }
        return true;
    }
    return this->position > x.position;
};

int Ull::deleteNode(const UllNode &node) {
fileIndex.seekg(0);
for(int i = 0; i < totalblock - 2; ++i){
    
}
};

