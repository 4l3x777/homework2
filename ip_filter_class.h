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
#include <array>

using namespace std;
using IpAddressFormat = tuple<int, int, int, int>;

vector<string> split(const string &str, char d);

class IpFilter {
    vector<array<int, tuple_size_v<IpAddressFormat>>> ip_pool;
    
    void ip_print(const vector<array<int, 4>>& container);
    void ip_print(const array<int, 4>& ip);

public:
    void reverse_lexicographically_sort();
    void filter(int first_octet_value);
    void filter(int first_octet_value, int second_octet_value);
    void filter_any(int any_octet_value);

    IpFilter(istream* in_stream);
    IpFilter(const vector<vector<string>>& in_pool);
    ~IpFilter();
};
