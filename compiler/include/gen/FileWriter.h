//
// Created by root on 2021/8/10.
//

#ifndef LEA_FILEWRITER_H
#define LEA_FILEWRITER_H

#include "../STL.h"

class FileWriter {
public:
    void open(std::string s);
    void write(std::string s);
    void close();
private:
    std::ofstream fd;
};


#endif //LEA_FILEWRITER_H
