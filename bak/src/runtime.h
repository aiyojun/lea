#ifndef __runtime_h__
#define __runtime_h__

#include <string>
#include <vector>
#include <fstream>
#include <deque>

typedef const std::string& cstring;

std::string join(cstring c, const std::vector<std::string>& v);

class file_writer {
public:
    void open(const std::string& s) {ostream.open(s);};
    void write(const std::string& s) {ostream << s;};
    void close() {ostream.close();};
    static std::string out;
private:
    std::ofstream ostream;
};

class runtime {
public:
    static int size_of_expect;
    static std::deque<std::string> expects;
    typedef const std::deque<std::string>& exp_q;
};

runtime::exp_q get_expects();


#endif//__runtime_h__