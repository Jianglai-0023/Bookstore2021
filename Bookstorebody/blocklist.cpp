#include"blocklist.h"
#include<cstring>
#include<fstream>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace ::std;

fstream fileIndex;

int addNums = 0;
int sizeofBlock = sizeof(UllBlock);
int totalblock = 0;

Ull::Ull(const std::string &arg) : file_name(arg) {
    fileIndex.open(file_name);
};

Ull::~Ull() {
    fileIndex.close();
}

UllNode::UllNode(const int &arg1, const std::string &arg2) {
    position = arg1;
    strcpy(str, arg2.c_str());
}

UllNode::UllNode() {};



UllBlock::UllBlock() {};



void Ull::mergeBlock(const int &offset1, const int &offset2) {
    UllBlock block1, block2, newblock;
    fileIndex.seekg(offset1);
    fileIndex.read(reinterpret_cast<char *>(&block1), sizeofBlock);
    fileIndex.seekg(offset2);
    fileIndex.read(reinterpret_cast<char *>(&block2), sizeofBlock);
    for (int i = 0; i < block1.num + block2.num; ++i) {
        if (i <= block1.num - 1) {
            newblock.array[i] = block1.array[i];
        } else {
            newblock.array[i] = block2.array[i - block1.num];
        }
    }
    newblock.pre = block1.pre;
    newblock.nxt = block2.nxt;
    newblock.num = block1.num + block2.num;
    fileIndex.seekg(offset1);
    fileIndex.write(reinterpret_cast<char *>(&newblock), sizeofBlock);
};

void Ull::splitBlock(const int &offset) {//文件已打开
    UllBlock block, newblock;
    UllNode node;
    fileIndex.seekg(offset);//移动指针到指定位置
    fileIndex.read(reinterpret_cast<char *>(&block), sizeofBlock);
    int nums = block.num / 2;
    for (int i = nums; i < block.num; ++i) {//复制过程
        newblock.array[i - nums] = block.array[i];
        block.array[i] = node;
    }
    //修改元素数量
    newblock.num = block.num - nums;
    block.num = nums;
    //改变节点
    newblock.nxt = block.nxt;
    newblock.pre = offset;
    fileIndex.seekg(0, ios::end);
    block.nxt = fileIndex.tellg();/*//todo*/
    //写入两个block
    fileIndex.seekg(offset);
    fileIndex.write(reinterpret_cast<char *>(&block), sizeofBlock);
    fileIndex.seekg(0, ios::end);
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
    } else if (totalblock == 1) {//只有一个block
        fileIndex.read(reinterpret_cast<char *>(&block), sizeofBlock);
        block.array[block.num] = node;
        ++block.num;
        sort(block.array, block.array + block.num);
        fileIndex.write(reinterpret_cast<char *>(&block), sizeofBlock);
        if (block.num > BLOCK_SPLIT_THRESHOLD) {
            splitBlock(1);
        }
    } else {//遍历链表头
        //特判：node比第一个链表头小
        fileIndex.seekg(0);
        fileIndex.read(reinterpret_cast<char *>(&block1), sizeofBlock);
        if (node < block1.array[0]) {
            block1.array[block.num] = node;
            ++block1.num;
            sort(block1.array, block1.array + block1.num);
            fileIndex.seekg(0);
            fileIndex.write(reinterpret_cast<char *>(&block1), sizeofBlock);
        }
            //正常遍历
        else {
            fileIndex.seekg(0);
            for (int i = 0; i < totalblock - 1; ++i) {
                fileIndex.read(reinterpret_cast<char *>(&block1), sizeofBlock);
                int index = block1.nxt;
                fileIndex.seekg(index);
                fileIndex.read(reinterpret_cast<char *>(&block2), sizeofBlock);
                if (node > block1.array[0] && node < block2.array[0]) {
                    block1.array[block1.num] = node;
                    ++block1.num;
                    //维持有序
                    sort(block1.array, block1.array + block1.num);
                    fileIndex.seekg(block2.pre);
                    fileIndex.write(reinterpret_cast<char *>(&block1), sizeofBlock);
                    if (block1.num > BLOCK_SPLIT_THRESHOLD) {
                        splitBlock(block2.pre);
                    }
                    break;
                } else if (i != totalblock - 2) {
                    fileIndex.seekg(block2.nxt);
                } else {//特判：只能插入最后一个block
                    block2.array[block2.num] = node;
                    ++block2.num;
                    sort(block2.array, block2.array + block2.num);
                    fileIndex.seekg(block1.nxt);
                    fileIndex.write(reinterpret_cast<char *>(&block2), sizeofBlock);
                    if (block2.num > BLOCK_SPLIT_THRESHOLD) {
                        splitBlock(block1.nxt);
                    }
                }
            }
        }
    }
};

void Ull::findNode(const std::string &key, std::vector<int> &array0) {
    UllBlock block;
    fileIndex.seekg(0);
    bool haveread = false;
    while(true){
    fileIndex.read(reinterpret_cast<char *>(&block), sizeofBlock);
    if (strcmp(key.c_str(), block.array[0].str) <= 0 && strcmp(block.array[block.num - 1].str, key.c_str()) >= 0) {
        haveread = true;
        for (int i = 0; i < block.num; ++i) {
            if (strcmp(block.array[i].str, key.c_str()) == 0) {
                array0.push_back(block.array[i].position);
            }
        }
        if(block.nxt != -1){
            fileIndex.seekg(block.nxt);
        }
        else break;
    }
    else if(block.nxt != -1 && !haveread){
        fileIndex.seekg(block.nxt);
    }
    else break;

    }
};



int Ull::deleteNode(const UllNode &node) {
    UllBlock block;
    fileIndex.seekg(0);
    for (int i = 0; i < totalblock - 2; ++i) {
        fileIndex.read(reinterpret_cast<char *>(&block), sizeofBlock);
        //查找node;
        if (node >= block.array[0] && node <= block.array[block.num - 1]) {
            //删除node
            //准备merge
            UllBlock block_p, block_n;
            fileIndex.seekg(block.pre);
            fileIndex.read(reinterpret_cast<char *>(&block_p), sizeofBlock);
            fileIndex.seekg(block.nxt);
            fileIndex.read(reinterpret_cast<char *>(&block_n), sizeofBlock);
            for (int j = 0; j < block.num; ++j) {
                if (block.array[j] == node) {
                    for (int t = j; t < block.num - 1; ++t) {
                        block.array[t] = block.array[t + 1];
                    }
                    --block.num;
                    if (block.num + block_p.num < BLOCK_MERGE_THRESHOLD){
                        mergeBlock(block.pre,block_p.nxt);
                    }
                    else if(block.num + block_n.num < BLOCK_MERGE_THRESHOLD){
                        mergeBlock(block.nxt,block_n.pre);
                    }
                        break;
                }
            }
        }
        fileIndex.seekg(block.nxt);
    }
}

bool UllNode::operator<(const UllNode &x) const {
    if (strcmp(this->str, x.str) != 0) {
        if (strcmp(this->str, x.str) < 0) {
            return true;
        }
        return false;
    }
    return this->position < x.position;
};

bool UllNode::operator>(const UllNode &x) const {
    if (strcmp(this->str, x.str) != 0) {
        if (strcmp(this->str, x.str) < 0) {
            return false;
        }
        return true;
    }
    return this->position > x.position;
};

bool UllNode::operator<=(const UllNode &x) const {
    if (strcmp(this->str, x.str) == 0 && this->position == x.position) return true;
    if (strcmp(this->str, x.str) == 0) return this->position < x.position;
    if (strcmp(this->str, x.str) < 0) return true;
    return false;
};

bool UllNode::operator>=(const UllNode &x) const {
    if (strcmp(this->str, x.str) == 0 && this->position == x.position) return true;
    if (strcmp(this->str, x.str) == 0) return this->position > x.position;
    if (strcmp(this->str, x.str) > 0) return true;
    return false;
};

bool UllNode::operator==(const UllNode &x) const {
    if (strcmp(this->str, x.str) == 0 && this->position == x.position) return true;
    return false;
};

inline int Ull::nextBlock(const int &offset) {

};
inline void Ull::delBlock(const int &offset) {

};