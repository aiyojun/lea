#include "basic_ds.h"

std::vector<std::string> to_vs(const std::vector<int>& v)
{std::vector<std::string> _r(v.size());for(int i=0;i<v.size();i++)_r[i] = std::to_string(v[i]);return std::move(_r);}

std::string join(cstring c, const std::vector<std::string>& v)
{std::string _r;for(int i=0;i<v.size();i++){_r+=v[i];if(i!=v.size()-1)_r+=c;}return _r;}
