#pragma once
#ifndef ARRAY_LIST_HPP
#define ARRAY_LIST_HPP

#include "List.hpp"

#include <memory>

#include "common.h"

template <typename T> struct ArrayList : public List<T> {
    static const size_t initial_capacity = 16;

  private:
    size_t n;
    size_t capacity;
    std::unique_ptr<T[]> p_data;

    // ArrayList(const ArrayList&);

  public:
    ArrayList(size_t init_capacity) {
        n = 0;
        capacity = init_capacity;
        p_data = std::unique_ptr<T[]>(new T[capacity]);
    }

    ArrayList() { new (this) ArrayList(initial_capacity); }

    void resize() {
        int new_capacity = capacity * 2;
        std::unique_ptr<T[]> new_p(new T[new_capacity]);
        std::copy(p_data.get(), p_data.get() + capacity, new_p.get());
        capacity = new_capacity;
        p_data = std::move(new_p);
    }

    void push_back(T t) {
        if (n == capacity) {
            resize();
        }
        if (n == capacity) {
            panic();
        }

        p_data[n] = t;
        n++;
    }

    void pop_back() {
        if (n == 0) {
            panic();
        }

        n--;
    }

    T &operator[](size_t i) override {
        if (0 <= i && i < n) {
            return p_data[i];
        } else {
            panic();
        }
    }

    inline size_t size() override { return n; }

    void append(T value) override { push_back(value); }

    void delete_at(size_t i) override {
        if (0 <= i && i < n) {
            T *p = p_data.get();
            // Insert cast to suppress -Wdynamic-class-memaccess
            // see https://github.com/MariaDB/server/commit/94bad73
            // memmove((void *)(p + i), (void *)(p + i + 1), sizeof(T) * (n - i
            // - 1));

            // nope, this don't work. mannually copying

            for (size_t j = i; j < n - 1; j++) {
                p[j] = p[j + 1];
            }

            n--;
        } else {
            panic();
        }
    }
};

#endif // ARRAY_LIST_HPP