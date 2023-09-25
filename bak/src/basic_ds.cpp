#include "basic_ds.h"

std::vector<std::string> to_vs(const std::vector<int>& v)
{std::vector<std::string> _r(v.size());for(unsigned int i=0;i<v.size();i++)_r[i] = std::to_string(v[i]);return std::move(_r);}

std::string join(cstring c, const std::vector<std::string>& v)
{std::string _r;for(unsigned int i=0;i<v.size();i++){_r+=v[i];if(i!=v.size()-1)_r+=c;}return _r;}

std::vector<std::string> split(cstring s, cstring separator) {
    std::vector<std::string> _r;
    std::string tmp = s;
    while (tmp.length() > 0) {
        std::string::size_type pos = tmp.find_first_of(separator);
        if (pos > tmp.length() - 1) { if (tmp.length() > 0) _r.emplace_back(tmp);break; }
        if (pos != 0)
            _r.emplace_back(tmp.substr(0, pos));
        tmp = tmp.substr(pos + separator.length());
    }
    //    std::cout << "_r: ";
    //    for (cstring pp : _r) std::cout << pp << " | ";
    //    std::cout << std::endl;
    return std::move(_r);
}

std::vector<std::string> splits(cstring s, const std::vector<std::string>& separators) {
    std::vector<std::string> _r;
    if (separators.empty()) return _r;
    _r = split(s, separators[0]);
    std::vector<std::string> _r2;
    std::vector<std::string> _r3;
    for (unsigned int i = 1; i < separators.size(); i++) {
        _r2.clear();
        for (unsigned int j = 0; j <_r.size(); j++) {
            _r3 = split(_r[j], separators[i]);
            _r2.insert(_r2.end(), _r3.begin(), _r3.end());
        }
        _r = _r2;
    }
    return std::move(_r);
}

std::string quote(cstring s) {
    if (s[0] != '"' || s[s.length() - 1] != '"') return "\"" + s + "\"";
    return s;
}

std::string un_quote(cstring s) {
    if (s.length() >= 2
    && ((s[0] == '\'' && s[s.length() - 1] == '\'')
    || (s[0] == '"' && s[s.length() - 1] == '"')))
        return s.substr(1, s.length() - 2);
    else return s;
}

std::string double_sci(cstring s) {
    std::string _r = s;
    while (_r.back() == '0') {
        unsigned int len = _r.length();
        _r = _r.substr(0, len - 1);
    }
    return _r;
}