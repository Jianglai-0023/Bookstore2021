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
int sizeofBlock = sizeof(UllBlock);
int totalblock = 0;


Ull::Ull(const std::string &arg) : file_name(arg) {
    fileIndex.open(file_name);
    if (!fileIndex.good()) {
        fileIndex.open(file_name, ios::out);
        fileIndex.close();
        fileIndex.open(file_name);
    }
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

void Ull::splitBlock(const int &offset) {
    ++totalblock;//总块数+1
    UllBlock block, newblock;
    UllNode node;
    fileIndex.seekg(offset);//移动指针到指定位置
    fileIndex.read(reinterpret_cast<char *>(&block), sizeofBlock);
    int nums = BLOCK_SPLIT_LEFT;
    for (int i = nums; i < block.num; ++i) {//复制过程
        newblock.array[i - nums] = block.array[i];
        block.array[i] = node;//可删去
    }
    //修改元素数量
    newblock.num = block.num - nums;
    block.num = nums;
    //改变节点
    newblock.nxt = block.nxt;
    newblock.pre = offset;
    fileIndex.seekg(0, ios::end);
    block.nxt = fileIndex.tellg();
    //写入两个block
    fileIndex.write(reinterpret_cast<char *>(&newblock), sizeofBlock);
    fileIndex.seekg(offset);
    fileIndex.write(reinterpret_cast<char *>(&block), sizeofBlock);
};

void Ull::addNode(const UllNode &node) {
    UllBlock block;
    UllBlock block1, block2;
    if (totalblock == 0) {//第一个block
        block.array[block.num] = node;

//        cout << block.array[0].str << "name" << endl;
        ++totalblock;
        ++block.num;
//        cout << block.num << " " << block.array[0].str << endl;
        fileIndex.seekg(0);
        fileIndex.write(reinterpret_cast<char *>(&block), sizeof(UllBlock));
//        fileIndex.seekg(0);
//        fileIndex.read(reinterpret_cast<char *>(&block1), sizeof(UllBlock));
//        cout << block1.num << " " << block1.array[0].str << endl;
    } else if (totalblock == 1) {//只有一个block
        fileIndex.seekg(0);
        fileIndex.read(reinterpret_cast<char *>(&block), sizeofBlock);
        block.array[block.num] = node;
        ++block.num;
        sort(block.array, block.array + block.num);
        fileIndex.seekg(0);
        fileIndex.write(reinterpret_cast<char *>(&block), sizeofBlock);
        if (block.num > BLOCK_SPLIT_THRESHOLD) {
            splitBlock(0);
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
            if (block1.num > BLOCK_SPLIT_THRESHOLD) {
                splitBlock(0);
            }
        }//正常遍历
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
                    //判断分块
                    if (block1.num > BLOCK_SPLIT_THRESHOLD) {
                        splitBlock(block2.pre);
                    }
                    //完成插入，退出循环
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
    while (true) {
        fileIndex.read(reinterpret_cast<char *>(&block), sizeofBlock);
//    std::cout << block.array[0].str << "here" << '\n';
//        std::cout << block.array[0].position << "here&" << '\n';
//std::cout << block.num - 1 << "number" << endl;
//std:: cout << key << "gey" <<'\n';
//std:: cout << strcmp(key.c_str(), block.array[0].str) << "bool" << endl;
//std:: cout << strcmp(block.array[block.num - 1].str, key.c_str()) << "bool2" << endl;
        if (strcmp(key.c_str(), block.array[0].str) >= 0 && strcmp(block.array[block.num - 1].str, key.c_str()) >= 0) {
            haveread = true;
            for (int i = 0; i < block.num; ++i) {
                if (strcmp(block.array[i].str, key.c_str()) == 0) {
                    array0.push_back(block.array[i].position);
                }
            }
            if (block.nxt != -1) {
                fileIndex.seekg(block.nxt);
            } else break;//读到最后一块
        } else if (block.nxt != -1 && !haveread) {
            fileIndex.seekg(block.nxt);
        }//已经读过，未到末位
        else break;//到达末尾/已经读过

    }
};


int Ull::deleteNode(const UllNode &node) {
    UllBlock block;
    fileIndex.seekg(0);
    //遍历block
    for (int i = 1; i <= totalblock; ++i) {
        fileIndex.read(reinterpret_cast<char *>(&block), sizeofBlock);
        //查找node;
        if (node >= block.array[0] && node <= block.array[block.num - 1]) {
            //删除node
            //准备merge，分别与前后两个块合并
            UllBlock block_p, block_n;
            for (int j = 0; j < block.num; ++j) {
                if (block.array[j] == node) {
                    for (int t = j; t < block.num - 1; ++t) {
                        block.array[t] = block.array[t + 1];
                    }
                    break;
                }
            }
            --block.num;
            //写回文件
            fileIndex.seekg((i - 1) * sizeofBlock);
            fileIndex.write(reinterpret_cast<char *>(&block), sizeofBlock);
            //有前置block
            if (block.pre != -1) {
                fileIndex.seekg(block.pre);
                fileIndex.read(reinterpret_cast<char *>(&block_p), sizeofBlock);
                if (block.num + block_p.num < BLOCK_MERGE_THRESHOLD) {
                    mergeBlock(block.pre, block_p.nxt);
                    break;
                }
            }
            if (block.nxt != -1) {
                fileIndex.seekg(block.nxt);
                fileIndex.read(reinterpret_cast<char *>(&block_n), sizeofBlock);
                if (block.num + block_n.num < BLOCK_MERGE_THRESHOLD) {
                    mergeBlock(block_n.pre, block.nxt);
                    break;
                }
            }
            break;
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