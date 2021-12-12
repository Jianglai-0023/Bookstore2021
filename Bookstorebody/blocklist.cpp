#include"blocklist.h"
#include<cstring>
#include<fstream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<iostream>

using namespace ::std;

fstream fileIndex;

//int addNums = 0;
int sizeofInt = sizeof(int);
int sizeofBlock = sizeof(UllBlock);
int totalblock;
UllBlock block0;

Ull::Ull(const std::string &arg) : file_name(arg) {
    fileIndex.open(file_name);
    if (!fileIndex.good()) {
        fileIndex.open(file_name, ios::out);
        fileIndex.close();
        fileIndex.open(file_name);
        fileIndex.seekg(0);
        totalblock = 0;
        fileIndex.write(reinterpret_cast<char *>(&totalblock), sizeofInt);
    }
//    cout << "open" <<' ' <<  fileIndex.bad() << endl;
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
    //要求第一参数为pre，第二参数为nxt；
    UllBlock block1, block2, block3,newblock;
    fileIndex.seekg(offset1 + sizeofInt);
    fileIndex.read(reinterpret_cast<char *>(&block1), sizeofBlock);
    fileIndex.seekg(offset2 + sizeofInt);
    fileIndex.read(reinterpret_cast<char *>(&block2), sizeofBlock);
    for (int i = 0; i < block1.num + block2.num; ++i) {
        if (i <= block1.num - 1) {
            newblock.array[i] = block1.array[i];
        } else {
            newblock.array[i] = block2.array[i - block1.num];
        }
    }
    //修改2或3个块的头节点，两种情况讨论
    //后面仍有节点
    if(block2.nxt != -1){
        fileIndex.seekg(block2.nxt + sizeofInt);
        fileIndex.read(reinterpret_cast<char *>(&block3), sizeofBlock);
        newblock.pre = block1.pre;
        newblock.nxt = block2.nxt;
        newblock.num = block1.num + block2.num;
        block3.pre = offset1;
        fileIndex.seekg(block2.nxt + sizeofInt);
//        cout << block2.nxt << "test" << endl;
        fileIndex.write(reinterpret_cast<char *>(&block3), sizeofBlock);
        fileIndex.seekg(offset1 + sizeofInt);
        fileIndex.write(reinterpret_cast<char *>(&newblock), sizeofBlock);
    }//后面无节点
    else{
    newblock.pre = block1.pre;
    newblock.nxt = block2.nxt;
    newblock.num = block1.num + block2.num;
    fileIndex.seekg(offset1 + sizeofInt);
    fileIndex.write(reinterpret_cast<char *>(&newblock), sizeofBlock);
    }
};

void Ull::splitBlock(int offset) {
    fileIndex.seekg(0);
    fileIndex.read(reinterpret_cast<char *>(&totalblock), sizeofInt);
    ++totalblock;//总块数+1
    fileIndex.seekg(0);
    fileIndex.write(reinterpret_cast<char *>(&totalblock), sizeofInt);
    UllBlock block, newblock,block3;
//    UllNode node;
    fileIndex.seekg(offset + sizeofInt);//移动指针到指定位置//未读出第一个block
    fileIndex.read(reinterpret_cast<char *>(&block), sizeofBlock);
//    int nums = ;
    for (int i = BLOCK_SPLIT_LEFT; i < block.num; ++i) {//复制过程
        newblock.array[i - BLOCK_SPLIT_LEFT] = block.array[i];
//        block.array[i] = node;//可删去
    }
    //修改元素数量
    newblock.num = block.num - BLOCK_SPLIT_LEFT;
    block.num = BLOCK_SPLIT_LEFT;
    //本身是末位节点
    if(block.nxt == -1){
    newblock.pre = offset;
    newblock.nxt = block.nxt;
    block.nxt = (totalblock - 1) * sizeofBlock;
    //写入两个block
    fileIndex.seekg(block.nxt + sizeofInt);
    fileIndex.write(reinterpret_cast<char *>(&newblock), sizeofBlock);
    fileIndex.seekg(offset + sizeofInt);
    fileIndex.write(reinterpret_cast<char *>(&block), sizeofBlock);
    }
    //不是末位节点
    else{
        fileIndex.seekg(block.nxt + sizeofInt);
        fileIndex.read(reinterpret_cast<char *>(&block3), sizeofBlock);
        newblock.nxt = block.nxt;
        newblock.pre = offset;
        block3.pre = (totalblock - 1) * sizeofBlock;
        block.nxt = (totalblock - 1) * sizeofBlock;
        fileIndex.seekg(block.nxt + sizeofInt);
        fileIndex.write(reinterpret_cast<char *>(&newblock), sizeofBlock);
        fileIndex.seekg(offset + sizeofInt);
        fileIndex.write(reinterpret_cast<char *>(&block), sizeofBlock);
        fileIndex.seekg(newblock.nxt + sizeofInt);
        fileIndex.write(reinterpret_cast<char *>(&block3), sizeofBlock);
    }
};

void Ull::addNode(const UllNode &node) {
fileIndex.seekg(0);
fileIndex.read(reinterpret_cast<char *>(&totalblock), sizeofInt);
    UllBlock block;
    UllBlock block1, block2;
    if (totalblock == 0) {//第一个block
        block.array[block.num] = node;
        ++totalblock;
        fileIndex.seekg(0);
        fileIndex.write(reinterpret_cast<char *>(&totalblock), sizeofInt);
        ++block.num;
        fileIndex.seekg(0 + sizeofInt);
        fileIndex.write(reinterpret_cast<char *>(&block), sizeofBlock);
    } else {//遍历链表头
        //特判：node比第一个链表头小
        //delete后只有一个block的情况
        //开始只有一个block的情况
        fileIndex.seekg(0 + sizeofInt);
        fileIndex.read(reinterpret_cast<char *>(&block), sizeofBlock);
        if (node < block.array[0] && block.nxt != -1 || block.nxt == -1) {
            block.array[block.num] = node;
            ++block.num;
            sort(block.array, block.array + block.num);
            fileIndex.seekg(0 + sizeofInt);
            fileIndex.write(reinterpret_cast<char *>(&block), sizeofBlock);
            if (block.num > BLOCK_SPLIT_THRESHOLD) {
                splitBlock(0);
            }
        }//正常遍历
        else {
            fileIndex.seekg(0 + sizeofInt);
            fileIndex.read(reinterpret_cast<char *>(&block1), sizeofBlock);
            for (int i = 0; i < totalblock - 1; ++i) {
                int index = block1.nxt;
                fileIndex.seekg(index + sizeofInt);
                fileIndex.read(reinterpret_cast<char *>(&block2), sizeofBlock);
                if (node > block1.array[0] && node < block2.array[0]) {
                    block1.array[block1.num] = node;
                    ++block1.num;
                    //维持有序
                    sort(block1.array, block1.array + block1.num);
                    fileIndex.seekg(block2.pre + sizeofInt);
                    fileIndex.write(reinterpret_cast<char *>(&block1), sizeofBlock);
                    //判断分块
                    if (block1.num > BLOCK_SPLIT_THRESHOLD) {
                        splitBlock(block2.pre);
                    }
                    //完成插入，退出循环
                    break;
                } else if (block2.nxt != -1) {
                    fileIndex.seekg(block1.nxt + sizeofInt);
                    fileIndex.read(reinterpret_cast<char *>(&block1), sizeofBlock);
                } else {//特判：只能插入最后一个block
                    block2.array[block2.num] = node;
                    ++block2.num;
                    sort(block2.array, block2.array + block2.num);
                    fileIndex.seekg(block1.nxt + sizeofInt);
                    fileIndex.write(reinterpret_cast<char *>(&block2), sizeofBlock);
                    if (block2.num > BLOCK_SPLIT_THRESHOLD) {
                        splitBlock(block1.nxt);
                    }
                    break;
                }
            }
        }
    }
};

void Ull::findNode(const std::string &key, std::vector<int> &array0) {
    if(totalblock == 0) return;
    UllBlock block;
    fileIndex.seekg(0 + sizeofInt);
    fileIndex.read(reinterpret_cast<char *>(&block), sizeofBlock);
    if(block.num == 0) return;
    if(strcmp(key.c_str(), block.array[0].str) < 0) return;
    bool haveread = false;
    while (true) {
//        if(strcmp(key.c_str(), block.array[0].str) < 0) return;
        if (strcmp(key.c_str(), block.array[0].str) >= 0 && strcmp(key.c_str(), block.array[block.num - 1].str) <= 0) {
            haveread = true;
            for (int i = 0; i < block.num; ++i) {
                if (strcmp(block.array[i].str, key.c_str()) == 0) {
                    array0.push_back(block.array[i].position);
                }
            }
            if(block.nxt != -1){
                fileIndex.seekg(block.nxt + sizeofInt);
                fileIndex.read(reinterpret_cast<char *>(&block), sizeofBlock);
            }
            else break;
        }
        else if (block.nxt != -1 && !haveread) {
            fileIndex.seekg(block.nxt + sizeofInt);
            fileIndex.read(reinterpret_cast<char *>(&block), sizeofBlock);
        }
        else break;
    }
}


int Ull::deleteNode(const UllNode &node) {
    UllBlock block;
    fileIndex.seekg(0);
    fileIndex.read(reinterpret_cast<char *>(&totalblock), sizeofInt);
    if(totalblock == 0) return 0;
    fileIndex.seekg(0 + sizeofInt);
    fileIndex.read(reinterpret_cast<char *>(&block), sizeofBlock);
    if(block.num == 0) return 0;
    int index = 0;
    bool havedeleted = false;
    //遍历block
    for (int i = 1; i <= totalblock; ++i) {
        //查找node;
        if(node < block.array[0]) return 0;
        if (node >= block.array[0] && node <= block.array[block.num - 1]) {
            //删除node
            //准备merge，分别与前后两个块合并
            //可能找不到这个元素，不能--num
            UllBlock block_p, block_n;
            for (int j = 0; j < block.num; ++j) {
                if (block.array[j] == node) {
                    havedeleted = true;
                    for (int t = j; t < block.num - 1; ++t) {
                        block.array[t] = block.array[t + 1];
                    }
                    break;
                }
            }
            if(havedeleted == true){
                --block.num;
            }

            //写回文件
            fileIndex.seekg(index + sizeofInt);
            fileIndex.write(reinterpret_cast<char *>(&block), sizeofBlock);
            //有前置block
            if (block.pre != -1) {
                fileIndex.seekg(block.pre + sizeofInt);
                fileIndex.read(reinterpret_cast<char *>(&block_p), sizeofBlock);
                if (block.num + block_p.num < BLOCK_MERGE_THRESHOLD || block.num == 0) {
                    mergeBlock(block.pre, block_p.nxt);
                    break;
                }
            }
            if (block.nxt != -1) {
                fileIndex.seekg(block.nxt + sizeofInt);
                fileIndex.read(reinterpret_cast<char *>(&block_n), sizeofBlock);
                if (block.num + block_n.num < BLOCK_MERGE_THRESHOLD || block.num == 0) {
                    mergeBlock(block_n.pre, block.nxt);
                    break;
                }
            }
            break;
        }
        if(block.nxt == -1) return 0;
        index = block.nxt;
        fileIndex.seekg(block.nxt + sizeofInt);
        fileIndex.read(reinterpret_cast<char *>(&block), sizeofBlock);
    }
    return 0;
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

void Test(int x) {
    fileIndex.seekg(0);
    fileIndex.read(reinterpret_cast<char *>(&totalblock), sizeofInt);
    cout << totalblock;
    fileIndex.seekg(0 + sizeofInt);
    fileIndex.read(reinterpret_cast<char *>(&block0), sizeofBlock);
    cout << "______" << x << "______" << endl;
    for (int i = 0; i < totalblock; ++i) {
        cout <<'|' << "pre nxt" << ' ' << block0.pre << ' ' << block0.nxt << '|' ;
        for (int j = 0; j < block0.num; ++j) {
            cout << block0.array[j].str <<'+' << block0.array[j].position << ' ';
        }
        cout << endl;
        if(block0.nxt == -1)
            return;
        fileIndex.seekg(block0.nxt + sizeofInt);
        fileIndex.read(reinterpret_cast<char *>(&block0), sizeofBlock);
    }
}