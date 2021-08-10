//
// Created by root on 2021/8/10.
//

#include "../include/gen/FileWriter.h"

void FileWriter::open(std::string path) {
    fd.open(path);
}

void FileWriter::write(std::string s) {
    fd << s;
}

void FileWriter::close() {
    fd.close();
}