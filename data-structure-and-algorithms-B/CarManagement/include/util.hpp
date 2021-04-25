#pragma once
#ifndef UTIL_HPP
#define UTIL_HPP

#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>

#include "structs.hpp"

using namespace std;

//////// utilities
namespace util {

// reference:
// https://stackoverflow.com/questions/36908994/using-sprintf-with-stdstring-in-c
template <typename... Args>
string sprintf_cxx(const char *format, Args &&... args) {
    size_t size = snprintf(nullptr, 0, format, std::forward<Args>(args)...);
    char output[size + 1];
    sprintf(&output[0], format, std::forward<Args>(args)...);
    output[size] = '\0';
    return string(output);
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
    while (true) {
        printf("%s%s: ", prefix.c_str(), field_name.c_str());
        getline(cin, s);
        if (!s.size()) { // read until something is given
            continue;
        }
        if (s.find(' ') != string::npos) {
            printf("[input_field] 错误: 不可以含有空格");
            continue;
        }
        break;
    }
    ss << s;
    T t;
    ss >> t;
    return t;
}

template <typename T> T input_field(string field_name) {
    return input_field<T>(field_name, "");
}

Time input_time(string prefix);
} // namespace util

#endif // UTIL_HPP