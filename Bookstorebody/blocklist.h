#ifndef BOOKSTORE_BLOCKLIST_H
#define BOOKSTORE_BLOCKLIST_H
#define BLOCK_SIZE 634
#define BLOCK_MAX 630//use for split
#define BLOCK_MIN 290//use for merge
#define BLOCK_SPLIT_LEFT 300

#include<fstream>
#include<vector>

void Test(int x);

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
