#include "ip_filter_class.h"

template <typename... Types, size_t... I>
constexpr auto TransformVectorToArray(const vector<string>& v, index_sequence<I...>)
{
    constexpr auto get_array = [](auto&& ... x){ return array{forward<decltype(x)>(x) ... }; };
    return apply(get_array, forward<IpAddressFormat>(make_tuple(atoi(v[I].c_str()) ...)));
}

template <typename>
struct VectorToArray;

template <typename... Types>
struct VectorToArray<tuple<Types...>>
{
    static auto from_vector(const vector<string>& v)
    {
        return TransformVectorToArray(v, make_index_sequence<sizeof... (Types)>());
    }
};

using Array = VectorToArray<IpAddressFormat>;

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

void IpFilter::ip_print(const vector<array<int, 4>>& container) {
    for(auto ip = container.cbegin(); ip != container.cend(); ++ip)
    {
        for(auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
        {
            if (ip_part != ip->cbegin())
            {
                cout << ".";
            }
            cout << to_string(*ip_part);
        }
        cout << '\n';
    }
}

void IpFilter::ip_print(const array<int, 4>& ip) {
    for(auto ip_part = ip.cbegin(); ip_part != ip.cend(); ++ip_part)
    {
        if (ip_part != ip.cbegin())
        {
            cout << ".";
        }
        cout << to_string(*ip_part);
    }
    cout << '\n';
}

void IpFilter::filter(int first_octet_value) {
    for (auto ip = ip_pool.begin(); ip != ip_pool.end(); ++ip) if ((*ip)[0] == first_octet_value) ip_print(*ip);
}

void IpFilter::filter(int first_octet_value, int second_octet_value) {
    for (auto ip = ip_pool.begin(); ip != ip_pool.end(); ++ip) if ((*ip)[0] == first_octet_value && (*ip)[1] == second_octet_value) ip_print(*ip);
}

void IpFilter::filter_any(int any_octet_value) {
    for (auto ip = ip_pool.begin(); ip != ip_pool.end(); ++ip) {
        for(auto octet = ip->begin(); octet != ip->end(); ++octet) {
            if (*octet == any_octet_value) { 
                ip_print(*ip); 
                break;
            }
        }
    }
}

void IpFilter::reverse_lexicographically_sort() {
    auto reverse_lexicographically_sort_functor {
        [](const array<int, 4>& lhs, const array<int, 4>& rhs) {
            for (size_t octet_idx = 0; octet_idx < lhs.size(); octet_idx++) {
                if (lhs[octet_idx] == rhs[octet_idx]) continue;
                else if (lhs[octet_idx] >rhs[octet_idx]) return true;
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
        auto ip_string_format_with_tabs = split(line, '\t');
        auto ip_string_format = split(ip_string_format_with_tabs.at(0), '.');
        ip_pool.push_back(Array::from_vector(ip_string_format));
    }
}

IpFilter::IpFilter(const vector<vector<string>>& in_pool) {
    ip_pool.clear();
    for(auto ip_string_format = in_pool.begin(); ip_string_format != in_pool.end(); ++ip_string_format) {
        ip_pool.push_back(Array::from_vector(*ip_string_format));
    }   
}

IpFilter::~IpFilter() {
    ip_pool.clear();
}
