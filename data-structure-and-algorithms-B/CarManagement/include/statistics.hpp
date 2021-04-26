#pragma once
#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include <functional>

#include "ArrayList.hpp"
#include "structs.hpp"

namespace statistics {

    LinkedList<Incident> collect_by_(ArrayList<Car> &list, std::function<bool (Incident&)> filter);

    void statistics(ArrayList<Car> &list);

}

#endif // STATISTICS_HPP