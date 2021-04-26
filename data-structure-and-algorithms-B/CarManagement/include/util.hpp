#pragma once
#ifndef UTIL_HPP
#define UTIL_HPP

#include <cstdio>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "ArrayList.hpp"
#include "LinkedList.hpp"
#include "structs.hpp"

using namespace std;

//////// utilities
namespace util {

// reference:
// https://stackoverflow.com/questions/36908994/using-sprintf-with-stdstring-in-c
template <typename... Args>
string sprintf_cxx(const char *format, Args &&... args) {
    size_t size = snprintf(nullptr, 0, format, std::forward<Args>(args)...);
    unique_ptr<char[]> output = unique_ptr<char[]>(new char[size + 1]);
    sprintf(&output[0], format, std::forward<Args>(args)...);
    output[size] = '\0';
    return string(output.get());
}

template <typename T> void check_value(T val, T m, T M, string error) {
    if (val < m || val > M) {
        throw runtime_error(error);
    }
}

inline void check_date(int year, int month, int day) {
    check_value(month, 1, 12, "日期错误");
    check_value(day, 1, 31, "日期错误");

    const int m[2][13] = {
        {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
        {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    };

    bool b = false;
    if (year % 400) {
        b = true;
    } else if (year % 100) {
        b = false;
    } else if (year % 4) {
        b = true;
    }

    if (day > m[b][month]) {
        throw runtime_error("日期错误");
    }
}

inline string localize_bool(bool b) { return (b) ? ("是") : ("否"); }

template <typename T> T input_field(string field_name, string prefix) {
    stringstream ss;
    string s;
    T t;
    while (true) {
        ss.str("");
        ss.clear();
        s.clear();
        printf("%s%s: ", prefix.c_str(), field_name.c_str());
        getline(cin, s);
        if (!s.size()) { // read until something is given
            continue;
        }
        if (s.find(' ') != string::npos) {
            printf("[input_field] 错误: 不可以含有空格\n");
            continue;
        }
        ss << s;
        if (ss >> t){
            break;
        } else {
            printf("[input_field] 错误: 没有读取到有效信息\n");
        }
    }
    return t;
}

template <typename T> T input_field(string field_name) {
    return input_field<T>(field_name, "");
}

Time input_time(string prefix);

inline void print_cars_verbose(ArrayList<Car> &list, string prefix) {
    unsigned int n = list.size();
    printf("%s车辆总数: %d\n", prefix.c_str(), n);
    for (unsigned int i = 0; i < n; i++) {
        printf("%s[%d] %s\n", prefix.c_str(), i, list[i].toString().c_str());
    }
}

inline void print_incidents_verbose(LinkedList<Incident>& list, string prefix) {
    unsigned int m = list.size();
    printf("%s违章总数: %d\n", prefix.c_str(), m);
    std::shared_ptr<LinkedListNode<Incident>> p = list.head;
    for (unsigned int x = 0; x < m; x++) {
        if (!p) {
            panic();
        }
        Incident i = p.get()->data;
        printf("%s[%d] %s\n", prefix.c_str(), x, i.toString().c_str());
        p = p.get()->next;
    }
}

} // namespace util

#endif // UTIL_HPP