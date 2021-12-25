//
// Created by 蒋lai on 2021/12/17.
//

#ifndef BOOKSTORE_BOOKSYSTEM_H
#define BOOKSTORE_BOOKSYSTEM_H

#include<iostream>
#include"file.h"
#include"blocklist.h"

class Book {
public:
    Book();

    Book(string isbn);

    char isbn_[21] = {'\0'};

    char name_[61] = {'\0'};

    char author_[61] = {'\0'};

    //the number of the keywords
    int n_ = 0;

    char keyword_[20][61];

    double price_ = -1;

    int quantity_ = 0;

    bool operator<(const Book &b) const {
        if (strcmp(isbn_, b.isbn_) == 0) return false;
        else if (strcmp(isbn_, b.isbn_) < 0) return true;
        return false;
    };

};

class BookSystem {
private:
    Book book_selected;

    File<Book> file_book_data;

    Blocklist file_isbn_index;

    Blocklist file_name_index;

    Blocklist file_author_index;

    Blocklist file_keyword_index;

    vector<Book> res;

    vector<int> book_key;

    vector<string> keyword_;

public:
    BookSystem();

    void showISBN(string isbn);

    void showName(string name);

    void showAuthor(string author);

    void showKeyword(string keyword);

    void showAll();

    void Print(vector<Book> &res);

    void Buy(string isbn, int quantity);

    int Select(string isbn);

//    void Modify(string isbn, string name, string author, string keyword, string price, int index);

    void Modify(const vector<string> &command, int index);

    void Import(int quantity, int index);

    void ReturnKeyWord(string s, std::vector<string> word);

    string ReturnRight(string s);

    int StringToInt(string q);

};


#endif //BOOKSTORE_BOOKSYSTEM_H
