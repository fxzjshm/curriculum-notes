#pragma once
#ifndef STRUCTS_HPP
#define STRUCTS_HPP

//////// Structs & Classes

#include "LinkedList.hpp"

using namespace std;

struct Car;
struct Incident;

struct Time {
    int year, month, day, hour, minute, second;

    Time() {}

    Time(string &s1, string &s2);

    string toString();
};

struct Incident { // WZ
    Time time;
    string place;
    int code;
    bool ok;
    std::shared_ptr<Car> p_car;

    string toString();
};
typedef Incident WZ;

struct Car {
    int id;
    string type;
    double price;
    string driver;
    LinkedList<Incident> incidents; // WZ

    string toString();
};

#endif // STRUCTS_HPP