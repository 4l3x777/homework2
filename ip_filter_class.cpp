#include "ip_filter_class.h"

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
vector<string> split(const string &str, char d)
{
    vector<string> r;
    string::size_type start = 0;
    string::size_type stop = str.find_first_of(d);
    while(stop != string::npos)
    {
        r.push_back(str.substr(start, stop - start));
        start = stop + 1;
        stop = str.find_first_of(d, start);
    }
    r.push_back(str.substr(start));
    return r;
}

void IpFilter::ip_print(const vector<vector<string>>& container) {
    for(vector<vector<string>>::const_iterator ip = container.cbegin(); ip != container.cend(); ++ip)
    {
        for(vector<string>::const_iterator ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
        {
            if (ip_part != ip->cbegin())
            {
                cout << ".";
            }
            cout << *ip_part;
        }
        cout << '\n';
    }
}

void IpFilter::ip_print(const vector<string>& ip) {
    for(vector<string>::const_iterator ip_part = ip.cbegin(); ip_part != ip.cend(); ++ip_part)
    {
        if (ip_part != ip.cbegin())
        {
            cout << ".";
        }
        cout << *ip_part;
    }
    cout << '\n';
}

void IpFilter::filter(int first_octet_value) {
    for (auto ip = ip_pool.begin(); ip != ip_pool.end(); ++ip) if (stoi((*ip)[0]) == first_octet_value) ip_print(*ip);
}

void IpFilter::filter(int first_octet_value, int second_octet_value) {
    for (auto ip = ip_pool.begin(); ip != ip_pool.end(); ++ip) if (stoi((*ip)[0]) == first_octet_value && stoi((*ip)[1]) == second_octet_value) ip_print(*ip);
}

void IpFilter::filter_any(int any_octet_value) {
    for (auto ip = ip_pool.begin(); ip != ip_pool.end(); ++ip) {
        for(auto octet = ip->begin(); octet != ip->end(); ++octet) {
            if (stoi(*octet) == any_octet_value) { 
                ip_print(*ip); 
                break;
            }
        }
    }
}

void IpFilter::reverse_lexicographically_sort() {
    auto reverse_lexicographically_sort_functor {
        [](const vector<string>& lhs, const vector<string>& rhs) {
            for (size_t octet_idx = 0; octet_idx < lhs.size(); octet_idx++) {
                if (stoi(lhs[octet_idx]) == stoi(rhs[octet_idx])) continue;
                else if (stoi(lhs[octet_idx]) > stoi(rhs[octet_idx])) return true;
                else return false;
            }
            return false;
        }
    };
    sort(
        ip_pool.begin(),
        ip_pool.end(),
        reverse_lexicographically_sort_functor
    );
    ip_print(ip_pool);
}

IpFilter::IpFilter(istream* in_stream) {
    ip_pool.clear();
    for(string line; getline(*in_stream, line);) {
        vector<string> v = split(line, '\t');
        ip_pool.push_back(split(v.at(0), '.'));
    }
}

IpFilter::IpFilter(const vector<vector<string>>& in_pool) {
    ip_pool.clear();
    ip_pool = in_pool;
}

IpFilter::~IpFilter() {
    ip_pool.clear();
}
