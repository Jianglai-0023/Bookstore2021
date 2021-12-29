#include "lubang.h"


Book_error::Book_error() : message("Invalid") {};

Book_error::Book_error(const string s) {
    message = s;
}
double Lubang::StringTodouble(string q) {
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
    if(n == 1) ans/=10;
    else if(n == 2) ans /= 100;
    return ans;
}
string Lubang::ReturnLeft(string s) {
    string left;
    left.clear();
    for (int i = 0; i < s.length(); ++i) {
        if (s[i] == '=') break;
        else {
            left += s[i];
        }
    }
    return left;
}
string Lubang::ReturnRight(string s) {
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
}

void Lubang::ReturnKeyWord(string s, std::vector<string> &word) {
    string key;
    word.clear();
    for (int i = 0; i < s.length(); ++i) {
        if (s[i] == '|') {
            for(int j = 0; j < word.size(); ++j){
                if(key == word[j]) throw Book_error("lubang: keyword repeated");
            }
            if(key.length() > 60) throw Book_error("lubang: keyword is too long");
            word.push_back(key);
            key.clear();
            continue;
        }
        key += s[i];
    }
    for(int j = 0; j < word.size(); ++j){
        if(key == word[j]) throw Book_error("show: keyword repeated");
    }
    word.push_back(key);
}
bool Lubang::checkWord(const char c, int n) {
    if (n == 0) {
        if (c >= '0' && c <= '9' || c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '_') return true;
        return false;
    }
    if (n == 1) {
        if (int(c) >= 36 && int(c) <= 126) return true;
        return false;
    } else if (n == 2) {
        if (c >= '0' && c <= '9') return true;
        return false;
    }
    else if(n == 3){
        if(int(c) >= 36 && int(c) <= 126 && c != '"') return true;
        return false;
    }
    else if(n == 4){
        if(c >= '0' && c <= '9' || c == '.') return true;
        return false;
    }
}

bool Lubang::checkSentence(const vector<string> sentence) {
    string check;
    //usersystem
    if (sentence[0] == "su") {
        if (sentence.size() != 2 && sentence.size() != 3) return false;
        check = sentence[1];
        if(check.length() > 30) return false;
        for (int j = 0; j < check.size(); ++j) {
            if (!checkWord(check[j], 0)) return false;
        }
        if (sentence.size() == 3) {
            check = sentence[2];
            if(check.length() > 30) return false;
            for (int j = 0; j < check.size(); ++j) {
                if (!checkWord(check[j], 0)) return false;
            }
        }
        return true;
    } else if (sentence[0] == "logout") {
        if (sentence.size() != 1) return false;
        return true;
    } else if (sentence[0] == "register") {
//        string check;
        if (sentence.size() != 4) return false;
        for (int i = 1; i < 4; ++i) {
            check = sentence[i];
            if (i == 1) {
                if(check.length() > 30) return false;
                for (int j = 0; j < check.length(); ++j) {
                    if (!checkWord(check[j], 0)) return false;
                }
            } else if (i == 2) {
                if(check.length() > 30) return false;
                for (int j = 0; j < check.length(); ++j) {
                    if (!checkWord(check[j], 0)) return false;
                }
            } else if (i == 3) {
                if(check.length() > 30) return false;
                for (int j = 0; j < check.length(); ++j) {
                    if (!checkWord(check[j], 1)) return false;
                }
            }
        }
        return true;
    } else if (sentence[0] == "passwd") {
        if (sentence.size() != 4 && sentence.size() != 3) return false;
        for (int i = 1; i < sentence.size(); ++i) {
            check = sentence[i];
            if(check.length() > 30) return false;
            for (int j = 0; j < check.length(); ++j) {
                if (!checkWord(check[j], 0)) return false;
            }
        }
        return true;
        //need priority;
    } else if (sentence[0] == "useradd") {
//        string check;
        if (sentence.size() != 5) return false;
        for (int i = 1; i < 5; ++i) {
            check = sentence[i];
            if (i == 1) {
                if(check.length() > 30) return false;
                for (int j = 0; j < check.length(); ++j) {
                    if (!checkWord(check[j], 0)) return false;
                }
            } else if (i == 2) {
                if(check.length() > 30) return false;
                for (int j = 0; j < check.length(); ++j) {
                    if (!checkWord(check[j], 0)) return false;
                }
            } else if (i == 3) {
                if(check.length() > 1) return false;
                if (check[0] != '0' && check[0] != '1' && check[0] != '3' && check[0] != '7') return false;
            } else if (i == 4) {
                if(check.length() > 30) return false;
                for (int j = 0; j < check.length(); ++j) {
                    if (!checkWord(check[j], 1)) return false;
                }
            }
            else if(i == 5){

            }
        }
        return true;
    } else if (sentence[0] == "delete") {
        if (sentence.size() != 2) return false;
        check = sentence[1];
        if(check.length() > 30) return false;
        for (int j = 0; j < check.length(); ++j) {
            if (!checkWord(check[j], 0)) return false;
        }
        return true;
    }
        //Booksystem
    else if (sentence[0] == "show"&& sentence.size() == 1 || sentence[0] == "show" &&sentence[1] != "finance") {
        int canshu[4] = {0,0,0,0};
      for(int i = 1; i<sentence.size(); ++i){
          if(ReturnLeft(sentence[i]) == "-ISBN" && canshu[0] != 1){
              canshu[0] = 1;
              check = ReturnRight(sentence[i]);
              if(check.length() == 0) return false;
              if(check.length() > 20) return false;
              for(int j = 0; j < check.length(); ++j){
                  if(!checkWord(check[j],1)) return false;
              }
          }
          else if(ReturnLeft(sentence[i] )== "-name"&&canshu[1] != 1){
              canshu[1] = 1;
              check = ReturnRight(sentence[i]);
              if(check.length() == 0) return false;
              if(check.length() > 60) return false;
              for(int j = 0; j < check.length(); ++j){
                  if(!checkWord(check[j],3)) return false;
              }
          }
          else if(ReturnLeft(sentence[i]) == "-author"&&canshu[2] != 1){
              canshu[2] = 1;
              check = ReturnRight(sentence[i]);
              if(check.length() == 0) return false;
              if(check.length() > 60) return false;
              for(int j = 0; j < check.length(); ++j){
                  if(!checkWord(check[j],3)) return false;
              }
          }
          else if(ReturnLeft(sentence[i]) == "-keyword"&&canshu[3] != 1){
              vector<string> word;
              check = ReturnRight(sentence[i]);
              if(check.length() == 0) return false;
              ReturnKeyWord(ReturnRight(sentence[i]),word);
              for(int j = 0; j < word.size(); ++j){
                  check = word[j];
                  for(int s = 0; s < check.length(); ++s){
                      if(!checkWord(check[s],3)) return false;
                  }
              }
              canshu[3] = 1;
          }
          else return false;
      }
      return true;
    } else if (sentence[0] == "buy") {
        if(sentence.size() != 3) return false;
        check = sentence[1];
        if(check.length() > 20) return false;
        for(int j = 0 ; j < check.size(); ++j){
            if(!checkWord(check[j],1)) return false;
        }
        check = sentence[2];
        if(StringTodouble(check) > 2147483647) return false;
        for(int j = 0 ; j < check.size(); ++j){
            if(!checkWord(check[j],2)) return false;
        }
        return true;
    } else if (sentence[0] == "select") {
        if(sentence.size() != 2) return false;
        check = sentence[1];
        if(check.length() > 20) return false;
        for(int j = 0; j < check.length(); ++j){
            if(!checkWord(check[j],1)) return false;
        }
        return true;
    } else if (sentence[0] == "modify") {
        int canshu[5] = {0,0,0,0,0};
        if(sentence.size() == 1) return false;
        for(int i = 1; i<sentence.size(); ++i){
            if(ReturnLeft(sentence[i]) == "-ISBN" && canshu[0] != 1){
                canshu[0] = 1;
                check = ReturnRight(sentence[i]);
                if(check.length() > 20) return false;
                if(check.length() == 0) return false;
                for(int j = 0; j < check.length(); ++j){
                    if(!checkWord(check[j],1)) return false;
                }
            }
            else if(ReturnLeft(sentence[i] )== "-name"&&canshu[1] != 1){
                canshu[1] = 1;
                check = ReturnRight(sentence[i]);
                if(check.length() > 60) return false;
                if(check.length() == 0) return false;
                for(int j = 0; j < check.length(); ++j){
                    if(!checkWord(check[j],3)) return false;
                }
            }
            else if(ReturnLeft(sentence[i]) == "-author"&&canshu[2] != 1){
                canshu[2] = 1;
                check = ReturnRight(sentence[i]);
                if(check.length() == 0) return false;
                if(check.length() > 60) return false;
                for(int j = 0; j < check.length(); ++j){
                    if(!checkWord(check[j],3)) return false;
                }
            }
            else if(ReturnLeft(sentence[i]) == "-keyword"&&canshu[3] != 1){
                vector<string> word;
                check = ReturnRight(sentence[i]);
                if(check.length() == 0) return false;
                ReturnKeyWord(ReturnRight(sentence[i]),word);
                for(int j = 0; j < word.size(); ++j){
                    check = word[j];
                    for(int s = 0; s < check.length(); ++s){
                        if(!checkWord(check[s],3)) return false;
                    }
                }
                canshu[3] = 1;
            }
            else if(ReturnLeft(sentence[i]) == "-price"&&canshu[4] != 1){
                check = ReturnRight(sentence[i]);
                if(check.length() > 13) return false;
            }
            else return false;
        }
        return true;
    } else if (sentence[0] == "import") {
        if(sentence.size() != 3) return false;
        check = sentence[1];
        if(StringTodouble(check) > 2147483647) return false;
//        if (check.length()  >10 ) return false;
        for(int j = 0; j< check.length(); ++j){
            if(!checkWord(check[j],2)) return false;
        }
        check = sentence[2];
        if(check.length() > 13) return false;
        bool flag = true;
        for(int j = 0; j < check.length(); ++j){
            if(check[j] == '.' && flag){
                flag = false;
            }
            else if(check[j] == '.' && !flag) return false;
            if(!checkWord(check[j],4)) return false;
        }
//        if(flag) return false;
        return true;
    }
        //LogSystem
    else if (sentence[0] == "report") {
        return true;
    } else if (sentence[0] == "show") {
        if(sentence[1] != "finance") return false;
        if(sentence.size() != 3 && sentence.size() != 2) return false;
        if(sentence.size() == 3){
            check = sentence[2];
            if(check.length() > 10) return false;
            for(int j = 0; j < check.length(); ++j){
                if(!checkWord(check[j],2)) return false;
            }
        }
        return true;
    } else if (sentence[0] == "log") {
        return true;
    }
}