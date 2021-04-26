#include "statistics.hpp"

#include <cstdio>
#include <iostream>
#include <memory>
#include <sstream>

#include "LinkedList.hpp"
#include "common.h"
#include "edit_incident_info.hpp"
#include "util.hpp"

namespace statistics {

void print_menu() {
    printf("[statistics] [Menu] 统计相关功能\n");
    printf("                    [t]: 统计某一时间段内所有的违章记录\n");
    printf("                    [p]: 统计某一地点的所有违章记录\n");
    printf("                    [c]: 统计某一违章代码的所有违章记录\n");
    printf("                    [q]: 返回上一级\n");
    printf("> ");
}

LinkedList<Incident> collect_by_(ArrayList<Car> &list, std::function<bool (Incident&)> filter) {
    LinkedList<Incident> collected;
    size_t n = list.size();
    for (size_t i = 0; i < n; i++){
        Car &c = list[i];
        size_t m = c.incidents.size();
        std::shared_ptr<LinkedListNode<Incident>> p = c.incidents.head;
        while (m--){
            if (!p){
                panic();
            }
            Incident &incident = p.get()->data;
            if (filter(incident)) {
                collected.append(incident);
            }
        }
    }
    return collected;
}

void collect_by_time(ArrayList<Car> &list) {
    Time start, end;
    printf("[statistics] [collect_by_time] 输入起始时间\n");
    start = util::input_time( /* prefix = */ "                               ");
    printf("[statistics] [collect_by_time] 输入结束时间\n");
    end = util::input_time( /* prefix = */ "                               ");
    LinkedList<Incident> collected = collect_by_(list,
    [&](Incident &incident) -> bool {
        return (start <= incident.time && incident.time <= end);
    });
    print_incidents_verbose(collected);
}

bool select_func(ArrayList<Car> &list) {
    string s;
    getline(cin, s);
    stringstream ss;
    string c; // control flow
    int i;    // id of car
    if (s.length()) {
        ss.clear();
        ss << s;
        switch (s[0]) {
        case 't':
            collect_by_time(list);
            break;
        case 'p':
            // collect_by_place(list);
            break;
        case 'c':
            // collect_by_code(list);
            break;
        case 'q':
            return true;
        default:
            break;
        }
    }

    return false;
}

void statistics(ArrayList<Car> &list) {
    bool quit = false;
    while (!quit) {
        print_menu();
        quit = select_func(list);
    }
}

}