#include "lubang.h"


Book_error::Book_error():message("Invalid"){};

bool Lubang::checkWord(const char c, int n) {
    if(n == 0){
        if(c >= '0'&& c <='9' || c >='a' && c <= 'z' || c>= 'A' && c <= 'Z' || c == '_') return true;
        return false;
    }
    if(n == 1){
        if(int(c) >= 36 && int(c) <= 126 ) return true;
        return false;
    }
    else if(n == 2){
        if(c >= '0' && c <='9') return true;
        return false;
    }
}

bool Lubang::checkSentence(const vector<string> sentence) {
    string check;
    //usersystem
    if(sentence[0] == "su"){
       if(sentence.size() != 2 && sentence.size() != 3) return false;
       check = sentence[1];
       for(int j = 0; j < check.size(); ++j){
           if(!checkWord(check[j],0)) return false;
       }
       if(sentence.size() == 3){
           check = sentence[2];
           for(int j = 0; j < check.size(); ++j){
               if(!checkWord(check[j],0)) return false;
           }
       }
       return true;
    }
    else if(sentence[0] == "logout"){
        if(sentence.size() != 1) return false;
        return true;
    }
    else if(sentence[0] == "register"){
//        string check;
        if(sentence.size() != 4) return false;
        for(int i = 1; i < 4; ++i){
            check = sentence[i];
            if(i == 1){
                for(int j = 0;j < check.length(); ++j){
                    if(!checkWord(check[j], 0)) return false;
                }
            }
            else if(i == 2){
                for(int j = 0;j < check.length(); ++j){
                    if(!checkWord(check[j], 0)) return false;
                }
            }
            else if(i == 3){
                for(int j = 0;j < check.length(); ++j){
                    if(!checkWord(check[j], 1)) return false;
                }
            }
        }
        return true;
    }
    else if(sentence[0] == "passwd"){
      if(sentence.size() != 4 && sentence.size() != 3) return false;
      for(int i = 1; i < sentence.size(); ++i) {
          check = sentence[i];
          for (int j = 0; j < check.length(); ++j) {
              if (!checkWord(check[j], 0)) return false;
          }
      }
      return true;
      //need priority;
    }
    else if(sentence[0] == "useradd"){
//        string check;
        if(sentence.size() != 5) return false;
        for(int i = 1; i < 5; ++i){
            check = sentence[i];
            if(i == 1){
                for(int j = 0;j < check.length(); ++j){
                    if(!checkWord(check[j], 0)) return false;
                }
            }
            else if(i == 2){
                for(int j = 0;j < check.length(); ++j){
                    if(!checkWord(check[j], 0)) return false;
                }
            }
            else if(i == 3){
                if(check[0] != '0' && check[0] != '1' && check[0] != '3' && check[0] != '7') return false;
                return false;
            }
            else if(i == 4){
                for(int j = 0;j < check.length(); ++j){
                    if(!checkWord(check[j], 1)) return false;
                }
            }
        }
        return true;
    }
    else if(sentence[0] == "delete"){
        if(sentence.size() != 2) return false;
        check = sentence[1];
        for(int j = 0;j < check.length(); ++j){
            if(!checkWord(check[j], 0)) return false;
        }
        return true;
    }
        //Booksystem
    else if(sentence[0] == "show"){

    }
    else if(sentence[0] == "buy"){

    }
    else if(sentence[0] == "select"){

    }
    else if(sentence[0] == "modify"){

    }
    else if(sentence[0] == "import"){

    }
        //LogSystem
    else if(sentence[0] == "report"){

    }
    else if(sentence[0] == "show"){

    }
    else if(sentence[0] == "log"){

    }
}