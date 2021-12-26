//
// Created by 蒋lai on 2021/12/17.
//
#include"Booksystem.h"
#include"lubang.h"

//BookSystem::BookSystem() : file_book_data("./rundata/book_data"), file_isbn_index("./rundata/isbn_index"),
//                           file_author_index("./rundata/author_index"),
//                           file_keyword_index("./rundata/keyword_index"), file_name_index("./rundata/name_index") {}
BookSystem::BookSystem() : file_book_data("./book_data"), file_isbn_index("./isbn_index"),
                           file_author_index("./author_index"),
                           file_keyword_index("./keyword_index"), file_name_index("./name_index") {}
//
Book::Book(string isbn) {
    strcpy(isbn_, isbn.c_str());
}

Book::Book() {}

string BookSystem::ReturnRight(string s) {
    string right;
    right.clear();
    bool flag = false;
    for (int i = 0; i < s.length(); ++i) {
        if (s[i] == '=') {
            flag = true;
            continue;
        }
        if (!flag) continue;
        if (s[i] == '"') continue;
        else {
            right += s[i];
        }
    }
    return right;
};

double BookSystem::StringTodouble(string q) {
    double ans = 0;
    bool flag = false;
    int n = 0;
    for (int i = 0; i < q.length(); ++i) {
        if (q[i] == '.') {
            flag = true;
            continue;
        }
        if (flag) ++n;
        ans *= 10;
        ans += q[i] - '0';
    }
    if (n == 1) ans /= 10;
    else if (n == 2) ans /= 100;
//    cout << "testdouble" << ans << endl;
//    cout << q <<' ' << n<< endl;
    return ans;
}

void BookSystem::ReturnKeyWord(string s, std::vector<string> &word) {
    string key;
    word.clear();
    for (int i = 0; i < s.length(); ++i) {
        if (s[i] == '|') {
            word.push_back(key);
            key.clear();
            continue;
        }
        key += s[i];
    }
    word.push_back(key);
}

void BookSystem::Print(vector<Book> &res) {
    sort(res.begin(), res.end());
    for (int i = 0; i < res.size(); ++i) {
        cout << res[i].isbn_ << '\t' << res[i].name_ << '\t' << res[i].author_ << '\t';
        for (int j = 0; j < res[i].n_; ++j) {
            if (j == res[i].n_ - 1) cout << res[i].keyword_[j] << '\t';
            else {
                cout << res[i].keyword_[j] << '|';
            }
        }
        if (res[i].n_ == 0) cout << '\t';
//        if (res[i].price_ != -1) {

            cout << setiosflags(std::ios::fixed) << setprecision(2) << res[i].price_ << '\t';


//            if(res[i].price_ != int(res[i].price_) && (int(res[i].price_ * 100) % 10) == 0) cout << res[i].price_<<'0' << '\t';
//            else if(res[i].price_ == int(res[i].price_)) cout << res[i].price_ <<".00" <<'\t';
//            else cout << res[i].price_  <<'\t';
//        } else {
//            cout << '\t';
//        }
        cout << res[i].quantity_ << '\n';
    }

}

void BookSystem::showISBN(string isbn) {
    book_key.clear();
    res.clear();

    file_isbn_index.FindNode(isbn, book_key);
    if (book_key.empty()) {
        cout << '\n';
        return;
    }
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
//    cout << name << "yuy" << endl;
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

double BookSystem::Buy(string isbn, int quantity) {
    Book buybook;
    book_key.clear();
    file_isbn_index.FindNode(isbn, book_key);
    if (book_key.empty()) throw Book_error("buy:book is not found");
    file_book_data.Read(buybook, book_key[0]);
    if (buybook.quantity_ >= quantity) {
        buybook.quantity_ -= quantity;
        file_book_data.Write(buybook, book_key[0]);

    } else throw Book_error("buy:book is not enough");
    double p = quantity * buybook.price_;
    cout << setiosflags(std::ios::fixed) << setprecision(2) << p << endl;
    return buybook.price_ * quantity;
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


void BookSystem::Modify(const vector<string> &command, int index) {//修改index
    Book bookm;
    file_book_data.Read(bookm, index);
    for (int i = 1; i < command.size(); ++i) {
        if (command[i][1] == 'I') {
            string right = ReturnRight(command[i]);
            book_key.clear();
            file_isbn_index.FindNode(right, book_key);
            if (!book_key.empty() && book_key[0] != index)throw Book_error("modify:isbn is repeated");
//            if (right == bookm.isbn_) return;
            BlockNode isbn(index, bookm.isbn_);
            file_isbn_index.DeleteNode(isbn);
            BlockNode newisbn(index, right);
            file_isbn_index.AddNode(newisbn);
            strcpy(bookm.isbn_, right.c_str());
        } else if (command[i][1] == 'a') {
            string right = ReturnRight(command[i]);
//if(bookm.author_ == right) return;
            if (bookm.author_[0] == '\0') {
                BlockNode author(index, right);
                file_author_index.AddNode(author);
            } else {
                BlockNode author(index, bookm.author_);
                file_author_index.DeleteNode(author);
                BlockNode newauthor(index, right);
                file_author_index.AddNode(newauthor);
            }
            strcpy(bookm.author_, right.c_str());
        } else if (command[i][1] == 'p') {
            bookm.price_ = StringTodouble(ReturnRight(command[i]));
        } else if (command[i][1] == 'n') {
            string right = ReturnRight(command[i]);
            //维护blocklist
            if (bookm.name_ == right) break;
            if (bookm.name_[0] == '\0') {
                BlockNode name(index, right);
                file_name_index.AddNode(name);
            } else {
                BlockNode name(index, bookm.name_);
                file_name_index.DeleteNode(name);
                BlockNode newname(index, right);
                file_name_index.AddNode(newname);
            }
            strcpy(bookm.name_, right.c_str());
        } else if (command[i][1] == 'k') {
            vector<string> word;
            ReturnKeyWord(ReturnRight(command[i]), word);

            for (int j = 0; j < bookm.n_; ++j) {
                string s = bookm.keyword_[j];
                BlockNode keyword(index, s);
                file_keyword_index.DeleteNode(keyword);
            }
            for (int j = 0; j < word.size(); ++j) {
                BlockNode newkeyword(index, word[j]);
                file_keyword_index.AddNode(newkeyword);
            }

            bookm.n_ = word.size();
            for (int j = 0; j < bookm.n_; ++j) {
                strcpy(bookm.keyword_[j], word[j].c_str());
            }
        }

    }
    file_book_data.Write(bookm, index);
}

void BookSystem::Import(int quantity, int index) {
    Book bookimport;
    file_book_data.Read(bookimport, index);
    bookimport.quantity_ += quantity;
    file_book_data.Write(bookimport, index);
}

void BookSystem::remove() {
//    file_book_data.remove();
//    file_isbn_index.remove();
//    file_name_index.remove();
//    file_author_index.remove();
//    file_keyword_index.remove();
}