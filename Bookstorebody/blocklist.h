
#ifndef BOOKSTORE_BLOCKLIST_H
#define BOOKSTORE_BLOCKLIST_H
#define BLOCK_SIZE 634
#define BLOCK_SPLIT_THRESHOLD 630
#define BLOCK_SPLIT_LEFT 300
#define BLOCK_MERGE_THRESHOLD 300
#include<fstream>
#include<vector>
class UllNode {
// Stores key-value data
// The data type of key is `int` and the data type
// of value is `char[64]`, but the constructor only
// accepts `std::string` as value.
public:
    int position;
    char str[64];

    bool operator<(const UllNode &x) const;
    bool operator>(const UllNode &x) const;
    bool operator<=(const UllNode &x) const;
    bool operator>=(const UllNode &x) const;
    bool operator==(const UllNode &x) const;
    // Compares str

    UllNode();

    UllNode(const int &arg1, const std::string &arg2);

//    UllNode &operator=(const UllNode &right);
};

class UllBlock {
// For ULL class internal use only
public:
    int nxt = -1;
    int pre = -1;
    int num = 0;
    //数组里读head和tail

    UllNode array[BLOCK_SIZE];

    UllBlock();

//    UllBlock &operator=(const UllBlock &right);
};







class Ull {
// 'Unrolled Linked List'
// A data structure used for file data storage.
// The advantage is that it is easy to write.
// But it is inferior to 'B+ Tree' in performance.
private:
    const std::string file_name;
    std::fstream fi, fo, fi2, fo2, fip, fip2, fop, fop2;
    // File Input/Output fstream objects
    // P for private methods

    inline int nextBlock(const int &offset);

    inline void delBlock(const int &offset);

    void mergeBlock(const int &offset1, const int &offset2);

    void splitBlock(const int &offset);

public:
    Ull(const std::string &arg);

    ~Ull();

    void findNode(const std::string &key, std::vector<int> &array0);
    // Returns an empty array if the node doesn't exist

    void addNode(const UllNode &node);

    int deleteNode(const UllNode &node);

#ifdef PPL_DEBUG
    void debugPrint();
#endif

};


#endif //BOOKSTORE_BLOCKLIST_H
