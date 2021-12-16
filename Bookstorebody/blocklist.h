#ifndef BOOKSTORE_BLOCKLIST_H
#define BOOKSTORE_BLOCKLIST_H
#define BLOCK_SIZE 305
#define BLOCK_MAX 300
#define BLOCK_MIN 150
#define BLOCK_SPLIT_LEFT 145

#include<fstream>
#include<vector>

//void Test(int x);

class BlockNode {

public:

    int position;
    char str[64];

    bool operator<(const BlockNode &x) const;

    bool operator>(const BlockNode &x) const;

    bool operator<=(const BlockNode &x) const;

    bool operator>=(const BlockNode &x) const;

    bool operator==(const BlockNode &x) const;

    BlockNode();

    BlockNode(const int &index, const std::string &filename);
};

class Block {
public:
    int nxt = -1;
    int pre = -1;
    int num = 0;
    //read head and tail from array
    BlockNode array[BLOCK_SIZE];
    Block();
};

class Blocklist {
private:
    const std::string file_name;
    std::fstream fileIndex;
    void MergeBlock(const int &offset1, const int &offset2);

    void SplitBlock(int offset);

public:

    Blocklist(const std::string &arg);

    ~Blocklist();

    void AddNode(const BlockNode &BlockNode);

    int DeleteNode(const BlockNode &BlockNode);

    void FindNode(const std::string &key, std::vector<int> &array0);

};


#endif //BOOKSTORE_BLOCKLIST_H
