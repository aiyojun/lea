#ifndef __basic_ds_h__
#define __basic_ds_h__

#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <vector>

typedef const std::string& cstring;

template<typename T, typename _>
bool contains(std::map<T, _> map, T key)
{return map.find(key) != map.end();}

template<typename T>
bool contains(std::set<T> map, T key)
{return map.find(key) != map.end();}

template<typename T>
bool contains(std::vector<T> container, T key) {
    return std::find(container.begin(), container.end(), key) != container.end();
}

std::vector<std::string> to_vs(const std::vector<int>& v);
std::string join(cstring c, const std::vector<std::string>& v);
std::vector<std::string> split(cstring s, cstring separator);
std::vector<std::string> splits(cstring s, const std::vector<std::string>& separators);
std::string quote(cstring s);

#endif//__basic_ds_h__