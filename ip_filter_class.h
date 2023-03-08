#pragma once
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <memory>
#include <algorithm>
#include <sstream>

using namespace std;

vector<string> split(const string &str, char d);

class IpFilter {
    vector<vector<string>> ip_pool;
    
    void ip_print(const vector<vector<string>>& container);
    void ip_print(const vector<string>& ip);

public:
    void reverse_lexicographically_sort();
    void filter(int first_octet_value);
    void filter(int first_octet_value, int second_octet_value);
    void filter_any(int any_octet_value);

    IpFilter(istream* in_stream);
    IpFilter(const vector<vector<string>>& in_pool);
    ~IpFilter();
};
