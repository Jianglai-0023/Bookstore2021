//
// Created by 蒋lai on 2021/12/17.
//
#include"Booksystem.h"
#include"lubang.h"

BookSystem::BookSystem() : file_book_data("book_data"), file_isbn_index("isbn_index"),
                           file_author_index("author_index"),
                           file_keyword_index("keyword_index"), file_name_index("name_index") {}

Book::Book(string isbn) {
    strcpy(isbn_, isbn.c_str());
}

void BookSystem::ReturnKeyWord(string s, std::vector<string> word) {
    string key;
    word.clear();
    for (int i = 0; i < s.length(); ++i) {
        if (s[i] == '|') {
            word.push_back(key);
            key.clear();
        }
        key += s[i];
    }
    word.push_back(key);
}

void BookSystem::Print(vector<Book> &res) {
    sort(res.begin(), res.begin() + res.size());
    for (int i = 0; i < res.size(); ++i) {
        cout << res[i].isbn_ << '\t' << res[i].name_ << '\t' << res[i].author_ << '\t';
        for (int j = 0; j < res[i].n_; ++j) {
            if (j == res[i].n_ - 1) cout << res[i].keyword_[j] << '\t';
            else {
                cout << res[i].keyword_[j] << '|';
            }
        }
        cout << res[i].price_ << '\t' << res[i].quantity_ << '\n';
    }

}

void BookSystem::showISBN(string isbn) {
    book_key.clear();
    res.clear();
    file_isbn_index.FindNode(isbn, book_key);
    if (book_key.empty()) cout << '\n';
    for (int i = 0; i < book_key.size(); ++i) {
        Book findbook;
        file_book_data.Read(findbook, book_key[i]);
        res.push_back(findbook);
    }
    Print(res);
}

void BookSystem::showName(string name) {
    book_key.clear();
    res.clear();
    file_name_index.FindNode(name, book_key);
    if (book_key.empty()) cout << '\n';
    for (int i = 0; i < book_key.size(); ++i) {
        Book findbook;
        file_book_data.Read(findbook, book_key[i]);
        res.push_back(findbook);
    }
    Print(res);
}

void BookSystem::showAuthor(string author) {
    book_key.clear();
    res.clear();
    file_author_index.FindNode(author, book_key);
    if (book_key.empty()) cout << '\n';
    for (int i = 0; i < book_key.size(); ++i) {
        Book findbook;
        file_book_data.Read(findbook, book_key[i]);
        res.push_back(findbook);
    }
    Print(res);
}

void BookSystem::showKeyword(string keyword) {
//    ReturnKeyWord(keyword,keyword_);
    book_key.clear();
    res.clear();
    file_keyword_index.FindNode(keyword, book_key);
    if (book_key.empty()) cout << '\n';
    for (int i = 0; i < book_key.size(); ++i) {
        Book findbook;
        file_book_data.Read(findbook, book_key[i]);
        res.push_back(findbook);
    }
    Print(res);
}

void BookSystem::showAll() {
    book_key.clear();
    res.clear();
    file_isbn_index.FindAll(book_key);
    if (book_key.empty()) cout << '\n';
    for (int i = 0; i < book_key.size(); ++i) {
        Book findbook;
        file_book_data.Read(findbook, book_key[i]);
        res.push_back(findbook);
    }
    Print(res);
}

void BookSystem::Buy(string isbn, int quantity) {
    Book buybook;
    book_key.clear();
    file_isbn_index.FindNode(isbn, book_key);
    if (book_key.empty()) throw Book_error("buy:book is not found");
    file_book_data.Read(buybook, book_key[0]);
    if (buybook.quantity_ >= quantity) {
        buybook.quantity_ -= quantity;
        file_book_data.Write(buybook, book_key[0]);
    } else throw Book_error("buy:book is not enough");
}

int BookSystem::Select(string isbn) {
    book_key.clear();
    file_isbn_index.FindNode(isbn, book_key);
    if (book_key.empty()) {
        Book newbook(isbn);
        int position = file_book_data.Add(newbook);
        BlockNode newbook_key(position, isbn);
        file_isbn_index.AddNode(newbook_key);
        return position;
    } else {
        return book_key[0];
    }
}

void BookSystem::Modify(string isbn, string name, string author, string keyword, string price, int index) {
//todo
}

void BookSystem::Import(int quantity, int index) {
    Book bookimport;
    file_book_data.Read(bookimport, index);
    bookimport.quantity_ += quantity;
    file_book_data.Write(bookimport, index);
}
