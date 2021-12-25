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
Book::Book() {}
string BookSystem::ReturnRight(string s){
    string right;
    right.clear();
    bool flag = false;
    for (int i = 0; i < s.length(); ++i) {
        if (s[i] == '='){
            flag = true;
            continue;
        }
        if (!flag) continue;
        else {
            right += s[i];
        }
    }
    return right;
};
int BookSystem::StringToInt(string q) {
    int ans = 0;
    for (int i = 0; i < q.length(); ++i) {
        ans *= 10;
        ans += q[i] - '0';
    }
    return ans;
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
    sort(res.begin(), res.end());
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
    cout << "testISBN" << isbn << endl;
    file_isbn_index.FindNode(isbn, book_key);
    if (book_key.empty()){
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
        cout << "qwq" << endl;
         file_isbn_index.Test(1);
         file_book_data.Add(newbook);
        return position;
    } else {
        return book_key[0];
    }
}


void BookSystem::Modify(const vector<string> &command, int index) {//修改index
    Book bookm;
    file_book_data.Read(bookm,index);
    for(int i = 1; i < command.size(); ++i){
        if(command[i][1] == 'I'){
            string right = ReturnRight(command[i]);
            //维护blocklist
            book_key.clear();
            file_isbn_index.FindNode(right,book_key);
            if(book_key.empty()){
                BlockNode isbn;
                isbn.position = index;
                strcpy(isbn.str,right.c_str());
                file_isbn_index.AddNode(isbn);
            }
            else{
                BlockNode isbn(book_key[0],bookm.isbn_);
                file_isbn_index.DeleteNode(isbn);
                BlockNode newisbn(book_key[0],right);
                file_isbn_index.AddNode(newisbn);
            }
            strcpy(bookm.isbn_, right.c_str());
        }
        else if(command[i][1] == 'a'){
            string right = ReturnRight(command[i]);
            //维护blocklist
            book_key.clear();
            file_author_index.FindNode(right,book_key);
            if(book_key.empty()){
                BlockNode author(index,right);
                file_author_index.AddNode(author);
            }
            else{
                for(auto iter = book_key.begin(); iter != book_key.end();++iter){
                    if(*iter == index){
                        BlockNode author(*iter,bookm.author_);
                        file_author_index.DeleteNode(author);
                        BlockNode newauthor(book_key[0],right);
                        file_author_index.AddNode(newauthor);
                        break;
                    }
                }
            }
            strcpy(bookm.author_, ReturnRight(command[i]).c_str());
        }
        else if(command[i][1] == 'p'){
            bookm.price_ = StringToInt(command[i]);
        }
        else if(command[i][1] == 'n'){
            string right = ReturnRight(command[i]);
            //维护blocklist
            book_key.clear();
            file_name_index.FindNode(right,book_key);
            if(book_key.empty()){
                BlockNode name(index,right);
                file_name_index.AddNode(name);
            }
            else{
                for(auto iter = book_key.begin(); iter != book_key.end();++iter){
                    if(*iter == index){
                        BlockNode name(*iter,bookm.name_);
                        file_name_index.DeleteNode(name);
                        BlockNode newname(book_key[0],right);
                        file_name_index.AddNode(newname);
                        break;
                    }
                }
            }
            strcpy(bookm.name_, ReturnRight(command[i]).c_str());
        }
        else if(command[i][1] == 'k'){
            vector<string> word;
            ReturnKeyWord(ReturnRight(command[i]), word);
            for(int j = 0;j < bookm.n_; ++j){
                string s = bookm.keyword_[j];
                book_key.clear();
                file_keyword_index.FindNode(s,book_key);
                for(auto iter = book_key.begin(); iter != book_key.end(); ++iter){
                    if(*iter == index){
                        BlockNode keyword(index,s);
                        file_keyword_index.DeleteNode(keyword);
                        break;
                    }
                }

            }
            for(int j = 0; j < word.size(); ++j){
              BlockNode newkeyword(index,word[j]);
              file_keyword_index.AddNode(newkeyword);
            }

            bookm.n_ = word.size();
            for(int j = 0;j < bookm.n_; ++j){
                strcpy(bookm.keyword_[j],word[j].c_str());
            }
        }

    }
    file_book_data.Write(bookm,index);
}

void BookSystem::Import(int quantity, int index) {
    Book bookimport;
    file_book_data.Read(bookimport, index);
    bookimport.quantity_ += quantity;
    file_book_data.Write(bookimport, index);
}
