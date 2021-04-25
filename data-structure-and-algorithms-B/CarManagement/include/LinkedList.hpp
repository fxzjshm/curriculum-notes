#pragma once
#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <memory>

#include "List.hpp"
#include "common.h"

template <typename T> struct LinkedListNode {
  public:
    T data;
    std::weak_ptr<LinkedListNode<T>> prev;
    std::shared_ptr<LinkedListNode<T>> next;

    LinkedListNode(T value) { data = value; }
};

template <typename T> struct LinkedList : public List<T> {
  private:
    size_t n;

  public:
    std::shared_ptr<LinkedListNode<T>> head;
    std::weak_ptr<LinkedListNode<T>> tail;

    LinkedList() { n = 0; }

    void insert_left(std::shared_ptr<LinkedListNode<T>> n3_s, T new_data) {
        // prev<->(new_node)<->node
        // n1 <-> (n2) <-> n3
        std::shared_ptr<LinkedListNode<T>> n2_s(
            new LinkedListNode<T>(new_data));
        if (n3_s.get()) {
            std::weak_ptr<LinkedListNode<T>> n1_w = n3_s.get()->prev;
            if (!n1_w.expired()) {
                n1_w.lock()->next = std::shared_ptr<LinkedListNode<T>>(n2_s);
                n2_s.get()->prev = std::weak_ptr<LinkedListNode<T>>(n1_w.lock());
            } else {
                // n1 doesn't exist
                n2_s.get()->prev = std::weak_ptr<LinkedListNode<T>>();
                head = std::shared_ptr<LinkedListNode<T>>(n2_s);
            }

            n3_s.get()->prev = std::weak_ptr<LinkedListNode<T>>(n2_s);
            n2_s.get()->next = std::make_shared<LinkedListNode<T>>(n3_s);
        } else {
            panic();
        }
    }

    void insert_right(std::shared_ptr<LinkedListNode<T>> n1_s, T new_data) {
        // node<->(new_node)<->next
        // n1 <-> (n2) <-> n3
        std::shared_ptr<LinkedListNode<T>> n2_s(
            new LinkedListNode<T>(new_data));
        if (n1_s.get()) {
            std::shared_ptr<LinkedListNode<T>> n3_s = n1_s.get()->next;

            if (n3_s) {
                n3_s.get()->prev = std::weak_ptr<LinkedListNode<T>>(n2_s);
                n2_s.get()->next = std::shared_ptr<LinkedListNode<T>>(n3_s);
            } else {
                n2_s.get()->next = nullptr;
                tail = std::weak_ptr<LinkedListNode<T>>(n2_s);
            }
            n1_s.get()->next = std::shared_ptr<LinkedListNode<T>>(n2_s);
            n2_s.get()->prev = std::weak_ptr<LinkedListNode<T>>(n1_s);
        } else {
            panic();
        }
    }

    void append(T data) override {
        if (!tail.expired()) {
            insert_right(tail.lock(), data);
        } else {
            LinkedListNode<T> node = LinkedListNode<T>(data);
            head = std::make_shared<LinkedListNode<T>>(node);
            tail = std::weak_ptr<LinkedListNode<T>>(head);
        }

        n++;
    }

    size_t size() override { return n; }

    void delete_at(size_t i) override {
        // n1 <-> [n2] <-> n3
        std::shared_ptr<LinkedListNode<T>> n2_s = ref(i);
        std::weak_ptr<LinkedListNode<T>> n1_w = n2_s.get()->prev;
        std::shared_ptr<LinkedListNode<T>> n3_s = n2_s.get()->next;
        if (n1_w.expired()) { // n2 is head
            head = std::shared_ptr<LinkedListNode<T>>(n3_s);
        } else {
            n1_w.lock().get()->next = std::shared_ptr<LinkedListNode<T>>(n3_s);
        }
        if (n3_s.get()) {
            n3_s.get()->prev = std::weak_ptr<LinkedListNode<T>>(n1_w);
        } else {
            tail = std::weak_ptr<LinkedListNode<T>>(n1_w);
        }

        n--;
    }

    std::shared_ptr<LinkedListNode<T>> ref(size_t i) {
        std::shared_ptr<LinkedListNode<T>> p = head;
        while (i--) {
            if (!p.get()) {
                panic();
            }
            p = p.get()->next;
        }
        return p;
    }

    T &operator[](size_t i) override { return ref(i).get()->data; }
};

#endif // LINKED_LIST_HPP