#include <cstdio>

#include "ArrayList.hpp"
#include "LinkedList.hpp"
#include "common.h"

#include "edit_car_info.hpp"
#include "edit_incident_info.hpp"
#include "io.hpp"
#include "statistics.hpp"
#include "structs.hpp"
#include "util.hpp"

using namespace std;

//////// Constants

const string file_name = "车辆管理数据.txt";

//////// main program functions
namespace main_program {

void exit_without_saving() {
    printf("[exit_without_saving] 真的不保存并退出吗？(y/[n])\n");
    printf("> ");
    string s;
    getline(cin, s);
    if (s == "y") {
        exit(0);
    }
}

void exit_with_saving(ArrayList<Car> &list) {
    printf("[exit_with_saving] 保存并退出？([y]/n)\n");
    printf("> ");
    string s;
    getline(cin, s);
    if (s != "n") {
        io::write_data(file_name, list);
        exit(0);
    }
}

void print_menu() {
    printf("[Menu] 请输入编号以选择功能：\n");
    printf("       [1] 查看与修改车辆与违章信息\n");
    printf("       [2] 统计违章信息\n");
    printf("       [9] 退出但不保存\n");
    printf("       [0] 退出并保存\n");
    printf("> ");
}

void select_func(ArrayList<Car> &list) {
    string s;
    getline(cin, s);
    if (s == "1") {
        edit_car_info::edit_car_info(list);
    } else if (s == "2") {
        statistics::statistics(list);
    } else if (s == "9") {
        exit_without_saving();
    } else if (s == "0") {
        exit_with_saving(list);
    }
}

} // namespace main_program

int main() {
    // set code page to utf-8(65001) on windows
    #ifdef _WIN32
    system("chcp 65001");
    #endif // _WIN32

    using namespace main_program;
    ArrayList<Car> list = io::read_data(file_name);
    while (true) {
        print_menu();
        select_func(list);
    }
    return 0;
}
