#pragma once
#ifndef LIST_HPP
#define LIST_HPP

#include <cstdlib>

template <typename T> struct List {
  public:
    virtual void append(T data) = 0;
    virtual size_t size() = 0;
    virtual void delete_at(size_t i) = 0;
    virtual T &operator[](size_t i) = 0;
};

#endif // LIST_HPP