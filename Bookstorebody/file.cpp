//
// Created by 蒋lai on 2021/12/16.
//
#include "file.h"

File::File(string filename){
    file_data.open(filename);
}
