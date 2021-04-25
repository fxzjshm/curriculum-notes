#pragma once
#ifndef IO_HPP
#define IO_HPP

#include <string>

#include "ArrayList.hpp"
#include "structs.hpp"

//////// input-output related functions
namespace io {

using namespace std;

ArrayList<Car> read_data(string file_name);

void write_data(string file_name, ArrayList<Car> &list);

} // namespace io

#endif // IO_HPP