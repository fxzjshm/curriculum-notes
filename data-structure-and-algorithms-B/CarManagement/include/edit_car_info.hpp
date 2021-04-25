#pragma once
#ifndef EDIT_CAR_INFO_HPP
#define EDIT_CAR_INFO_HPP

#include "ArrayList.hpp"
#include "structs.hpp"

//////// edit car information
namespace edit_car_info {

void print_cars_verbose(ArrayList<Car> &list);

void print_menu();

void add_car(ArrayList<Car> &list);

bool select_func(ArrayList<Car> &list);

void edit_car_info(ArrayList<Car> &list);

} // namespace edit_car_info

#endif // EDIT_CAR_INFO_HPP