#include "edit_incident_info.hpp"

#include "LinkedList.hpp"
#include "util.hpp"

//////// edit incident information
namespace edit_incident_info {

void print_incidents_verbose(Car &c) {
    unsigned int m = c.incidents.size();
    printf("[edit_incidnet_info] 违章总数: %d\n", m);
    std::shared_ptr<LinkedListNode<Incident>> p = c.incidents.head;
    for (int x = 0; x < m; x++) {
        if (!p) {
            panic();
        }
        Incident i = p.get()->data;
        printf("                     [%d] %s\n", x, i.toString().c_str());
        p = p.get()->next;
    }
}

void print_menu() {
    printf("[edit_incident_info] [Menu] 请输入编号以选择功能: (示例: \"e 0\", "
           "不含引号)\n");
    printf("                            [a]: 新增违章记录\n");
    printf("                            [d 序号]: 删除违章记录\n");
    printf("                            [e 序号]: 违章记录状态更新\n");
    printf("                            [q]: 返回上一级\n");
    printf("> ");
}

void add_incident(Car &c) {
    Incident i;
    string date, time;
    printf("[edit_incident_info] [add_incident] 请输入:\n");
    i.time = util::input_time(
        /* prefix = */ "                                    ");
    i.place = util::input_field<decltype(i.place)>(
        "                                    地点");
    i.code = util::input_field<decltype(i.code)>(
        "                                    违章代码");
    // don't set i.ok now. use `e` command later to filp the status
    // i.ok = input_field<decltype(i.ok)>(
    //  "                                    是否处理(true/false)");
    i.ok = false;
    c.incidents.append(i);
    printf("[edit_incident_info] [add_incident] 已添加违章:\n");
    printf("                                    [%u] %s\n",
           (unsigned int)c.incidents.size() - 1, i.toString().c_str());
}

void delete_incident(Car &c, size_t i) {
    printf("###############################################################\n");
    printf("根据《中华人民共和国刑法》第二百八十六条规定，违反国家规定，对计算"
           "机信息系统中存储、处理或者传输的数据和应用程序进行删除、修改、增加"
           "的操作构成破坏计算机信息系统罪。后果严重的，处五年以下有期徒刑或者"
           "拘役；后果特别严重的，处五年以上有期徒刑。\n");
    printf("###############################################################\n");
    string s = util::input_field<decltype(s)>("你确定要继续吗？(y/[n])");
    if (s == "y") {
        c.incidents.delete_at(i);
        printf("[edit_car_info] 已删除序号为 %u 的违章\n", (unsigned int)i);
    }
    printf("\n");
}

bool select_func(Car &car) {
    string s;
    getline(cin, s);
    stringstream ss;
    string c; // control flow
    int i;    // id of car
    if (s.length()) {
        ss.clear();
        ss << s;
        switch (s[0]) {
        case 'a':
            add_incident(car);
            break;
        case 'd':
            if (ss >> c >> i) {
                if (0 <= i && i < car.incidents.size()) {
                    delete_incident(car, i);
                } else {
                    printf("[edit_car_info] 错误: 序号越界\n\n");
                }
            } else {
                printf("[edit_car_info] 错误: 请输入序号\n\n");
            }
            break;
        case 'e':
            if (ss >> c >> i) {
                if (0 <= i && i < car.incidents.size()) {
                    Incident &inc = car.incidents[i];
                    inc.ok = (!inc.ok);
                    printf("[edit_car_info] 已更改序号为 %d 的违章的状态, "
                           "是否处理: %s -> %s\n\n",
                           i, util::localize_bool(!inc.ok).c_str(),
                           util::localize_bool(inc.ok).c_str());
                } else {
                    printf("[edit_car_info] 错误: 序号越界\n\n");
                }
            } else {
                printf("[edit_car_info] 错误: 请输入序号\n\n");
            }
            break;
        case 'q':
            return true;
        default:
            break;
        }
    }

    return false;
}

void edit_incident_info(Car &c) {
    bool quit = false;
    while (!quit) {
        printf("[edit_incident_info] 车辆信息: %s\n", c.toString().c_str());
        printf("[edit_incident_info] 该车违章信息:\n");
        print_incidents_verbose(c);
        print_menu();
        quit = select_func(c);
    }
}

} // namespace edit_incident_info