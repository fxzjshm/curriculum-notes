#include "edit_car_info.hpp"

#include "util.hpp"
#include "edit_incident_info.hpp"

//////// edit car information
namespace edit_car_info {

void print_cars_verbose(ArrayList<Car> &list) {
    util::print_cars_verbose(list, "                ");
}

void print_menu() {
    printf("[edit_car_info] [Menu] 请输入编号以选择功能: (示例: \"p 0\", "
           "不含引号)\n");
    printf("                       [a]: 新增车辆\n");
    printf("                       [p 序号]: 输出该车的违章记录并操作\n");
    printf("                       [d 序号]: 删除该车\n");
    printf("                       [q]: 返回上一级\n");
    printf("> ");
}

void add_car(ArrayList<Car> &list) {
    using namespace util;
    Car c;
    printf("[edit_car_info] [add_car] 请输入:\n");
    c.id = util::input_field<decltype(c.id)>("                          车号");
    c.type =
        util::input_field<decltype(c.type)>("                          车型");
    c.price =
        util::input_field<decltype(c.price)>("                          价格");
    c.driver = util::input_field<decltype(c.driver)>(
        "                          驾驶员");
    list.append(c);
    printf("[edit_car_info] [add_car] 已添加车辆:\n");
    printf("                          [%u] %s\n", (unsigned int)list.size() - 1,
           c.toString().c_str());
    printf("\n");
}

bool select_func(ArrayList<Car> &list) {
    string s;
    getline(cin, s);
    stringstream ss;
    string c; // control flow
    int i;    // id of car
    if (s.length()) {
        ss.str("");
        ss.clear();
        ss << s;
        switch (s[0]) {
        case 'p':
            if (ss >> c >> i) {
                if (0 <= i && i < list.size()) {
                    printf("\n");
                    edit_incident_info::edit_incident_info(list[i]);
                } else {
                    printf("[edit_car_info] 错误: 序号越界\n\n");
                }
            } else {
                printf("[edit_car_info] 错误: 请输入序号\n\n");
            }
            break;
        case 'd':
            if (ss >> c >> i) {
                if (0 <= i && i < list.size()) {
                    list.delete_at(i);
                    printf("[edit_car_info] 已删除序号为 %d 的车辆\n\n", i);
                } else {
                    printf("[edit_car_info] 错误: 序号越界\n\n");
                }
            } else {
                printf("[edit_car_info] 错误: 请输入序号\n\n");
            }
            break;
        case 'a':
            add_car(list);
            break;
        case 'q':
            printf("\n");
            return true;
        default:
            break;
        }
    }

    return false;
}

void edit_car_info(ArrayList<Car> &list) {
    bool quit = false;
    while (!quit) {
        printf("[edit_car_info] 已有车辆信息如下:\n");
        print_cars_verbose(list);
        print_menu();
        quit = select_func(list);
    }
}

} // namespace edit_car_info