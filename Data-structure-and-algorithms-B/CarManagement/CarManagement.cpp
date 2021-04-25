#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

using namespace std;

//////// Macros

#define panic()                                                                \
    {                                                                          \
        printf("[ERROR] Panic at %s: %d\n", __FILE__, __LINE__);               \
        exit(-1);                                                              \
    }

//////// Prerequisites

template <typename T> struct List {
  public:
    virtual void append(T data) = 0;
    virtual size_t size() = 0;
    virtual void delete_at(size_t i) = 0;
};

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
                n2_s.get()->prev = weak_ptr<LinkedListNode<T>>(n1_w.lock());
            } else {
                // n1 doesn't exist
                n2_s.get()->prev = std::weak_ptr<LinkedListNode<T>>();
                head = std::shared_ptr<LinkedListNode<T>>(n2_s);
            }

            n3_s.get()->prev = weak_ptr<LinkedListNode<T>>(n2_s);
            n2_s.get()->next = make_shared<LinkedListNode<T>>(n3_s);
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
                n3_s.get()->prev = weak_ptr<LinkedListNode<T>>(n2_s);
                n2_s.get()->next = std::shared_ptr<LinkedListNode<T>>(n3_s);
            } else {
                n2_s.get()->next = nullptr;
                tail = weak_ptr<LinkedListNode<T>>(n2_s);
            }
            n1_s.get()->next = std::shared_ptr<LinkedListNode<T>>(n2_s);
            n2_s.get()->prev = weak_ptr<LinkedListNode<T>>(n1_s);
        } else {
            panic();
        }
    }

    void append(T data) override {
        if (!tail.expired()) {
            insert_right(tail.lock(), data);
        } else {
            LinkedListNode<T> node = LinkedListNode<T>(data);
            head = make_shared<LinkedListNode<T>>(node);
            tail = weak_ptr<LinkedListNode<T>>(head);
        }

        n++;
    }

    size_t size() override { return n; }

    void delete_at(size_t i) override {
        // n1 <-> [n2] <-> n3
        std::shared_ptr<LinkedListNode<T>> n2_s = head;
        while (i--) {
            if (!n2_s.get()) {
                panic();
            }
            n2_s = n2_s.get()->next;
        }
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
    }
};

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

    T &operator[](size_t i) {
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
            memmove((void *)(p + i), (void *)(p + i + 1),
                    sizeof(T) * (n - i - 1));
            n--;
        } else {
            panic();
        }
    }
};

///////////////////////////////////////////////////////////////

//////// Constants

const string file_name = "车辆管理数据.txt";

//////// utilities
namespace util {

// reference: https://stackoverflow.com/questions/36908994/using-sprintf-with-stdstring-in-c
template <typename ...Args> string sprintf_cxx(const char* format, Args && ...args){
    size_t size = snprintf(nullptr, 0, format, std::forward<Args>(args)...);
    char output[size + 1];
    sprintf(&output[0], format, std::forward<Args>(args)...);
    output[size] = '\0';
    return string(output);
}

template <typename T> void check_value(T val, T m, T M, string error){
    if (val < m || val > M){
        throw runtime_error(error);
    }
}
} // namespace util

//////// Structs & Classes

struct Car;
struct Incident;

struct Time {
    int year, month, day, hour, minute, second;

    Time() {}

    Time(string &s1, string &s2) {
        int c1, c2;
        c1 = sscanf(s1.c_str(), "%d-%d-%d", &year, &month, &day);
        c2 = sscanf(s2.c_str(), "%d:%d:%d", &hour, &minute, &second);
        if(c1!=3||c2!=3){
            throw runtime_error("参数错误");
        }
    }

    string toString() {
        return util::sprintf_cxx("%d-%02d-%02d %02d:%02d:%02d", year, month, day, hour, minute, second);
    }
};

struct Incident { // WZ
    Time time;
    string place;
    int code;
    bool ok;
    std::shared_ptr<Car> p_car;

    string toString() {
        util::sprintf_cxx("时间: %s, 地点: %s, 违章代码: %d, 是否处理: %s\n",
               time.toString().c_str(), place.c_str(), code,
               ((ok) ? ("是") : ("否")));
    }
};
typedef Incident WZ;

struct Car {
    int id;
    string type;
    double price;
    string driver;
    LinkedList<Incident> incidents; // WZ

    string toString() {
        return util::sprintf_cxx("车号: %d, 车型: %s, 价格: %.1f, 驾驶员: %s", id, type.c_str(),
               price, driver.c_str());
    }
};

namespace util {
template <typename T> T input_field(string field_name) {
    stringstream ss;
    string s;
    while (true) {
        printf("%s: ", field_name.c_str());
        getline(cin, s);
        if (!s.size()) { // read until something is given
            continue;
        }
        if (s.find(' ') != string::npos) {
            printf("[input_field] 错误: 不可以含有空格");
            continue;
        }
        break;
    }
    ss << s;
    T t;
    ss >> t;
    return t;
}

Time input_time(char *prefix){
    string date, time;
    while(true){
        printf("%s", prefix);
        date = input_field<decltype(date)>("日期(示例: 1970-01-01)");
        printf("%s", prefix);
        time = input_field<decltype(time)>("时间(示例: 00:00:00)");
        try{
            Time t = Time(date, time);
            return t;
        }catch(runtime_error e){
            printf("[input_time] 错误: 请输入正确的日期与时间\n");
        }
    }
}
} // namespace util

//////// input-output related functions
namespace io {

ArrayList<Car> read_data(string file_name) {
    // unique_ptr<FILE, decltype(&fclose)> data_file(fopen(file_name.c_str(),
    // "r"), &fclose);
    ifstream din(file_name); // alternative of `cin`, or abbr. of "data input"
    ArrayList<Car> car_list;
    if (din) {
        unsigned int n; // count of cars
        din >> n;
        string temp;
        while (n--) {
            din >> temp; // sepatator ------

            Car c;
            din >> c.id >> c.type >> c.price >> c.driver;

            unsigned int m; // count of incidents a.k.a. WZ
            din >> m;
            while (m--) {
                Incident i;
                string date, time;
                din >> date >> time;
                i.time = Time(date, time);
                din >> i.place >> i.code >> i.ok;
                i.p_car = std::make_shared<Car>(c);
                c.incidents.append(i);
            }
            car_list.append(c);
        }
        din.close();
    }
    return car_list;
}

void write_data(string file_name, ArrayList<Car> &list) {
    unique_ptr<FILE, decltype(&fclose)> data_file(fopen(file_name.c_str(), "w"),
                                                  &fclose);
    unsigned int n = list.size();
    fprintf(data_file.get(), "%u\n", n);
    for (unsigned int i = 0; i < n; i++) {
        Car c = list[i];
        fprintf(data_file.get(), "------------------------\n");
        fprintf(data_file.get(), "%d %s %f %s\n", c.id, c.type.c_str(), c.price,
                c.driver.c_str());

        unsigned int m = c.incidents.size();
        fprintf(data_file.get(), "%u\n", m);
        std::shared_ptr<LinkedListNode<Incident>> p = c.incidents.head;
        while (m--) {
            if (!p) {
                panic();
            }
            Incident i = p.get()->data;
            fprintf(data_file.get(), "%s\n", i.time.toString().c_str());
            fprintf(data_file.get(), "%s\n", i.place.c_str());
            fprintf(data_file.get(), "%d\n", i.code);
            fprintf(data_file.get(), "%d\n", i.ok);
            // no need to save i.p_car

            p = p.get()->next;
        }
    }
}

} // namespace io

namespace edit_incident_info {

void print_incidents_verbose(Car& c) {
    unsigned int m = c.incidents.size();
    printf("[edit_incidnet_info] 违章总数: %d\n", m);
    std::shared_ptr<LinkedListNode<Incident>> p = c.incidents.head;
    for (int x = 0; x < m; x++) {
        if (!p) {
            panic();
        }
        Incident i = p.get()->data;
        printf("                     [%d] %s\n", x, i.toString());
        p = p.get()->next;
    }
}

void print_menu() {
    printf("[edit_incident_info] [Menu] 请输入编号以选择功能: (示例: \"p 0\", "
           "不含引号)\n");
    printf("                            [a]: 新增违章记录\n");
    printf("                            [d 序号]: 删除违章记录\n");
    printf("                            [e 序号]: 违章记录状态更新\n");
    printf("                            [q]: 返回上一级\n");
    printf("> ");
}


void add_incident(Car& c){
    using namespace util;
    Incident i;
    string date, time;
    printf("[edit_incident_info] [add_incident] 请输入:\n");
    i.time = input_time( /* prefix = */ "                                    ");
    i.place = input_field<decltype(i.place)>("                                    地点");
    i.code = input_field<decltype(i.code)>("                                    违章代码");
    i.ok = input_field<decltype(i.ok)>("                                    是否处理(true/false)");
    c.incidents.append(i);
    printf("[edit_incident_info] [add_incident] 已添加违章:\n");
    printf("                                    [%u] %s", (unsigned int)c.incidents.size() - 1, i.toString());
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
                    car.incidents.delete_at(i);
                    printf("[edit_car_info] 已删除序号为 %d 的车辆\n\n", i);
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
                    
                    printf("[edit_car_info] 已删除序号为 %d 的\n\n", i);
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
        printf("[edit_incident_info] 该车违章信息:");
        print_incidents_verbose(c);
        print_menu();
        quit = select_func(c);
    }
}

} // namespace edit_incident_info

//////// edit car information
namespace edit_car_info {

void print_cars_verbose(ArrayList<Car> &list) {
    size_t n = list.size();
    for (int i = 0; i < n; i++) {
        Car c = list[i];
        printf("                [%d] %s", i, c.toString().c_str());
    }
}

void print_menu() {
    printf("[edit_car_info] [Menu] 请输入编号以选择功能: (示例: \"p 0\", "
           "不含引号)\n");
    printf("                       [p 序号]: 输出该车的违章记录并操作\n");
    printf("                       [d 序号]: 删除该车\n");
    printf("                       [a]: 新增车辆\n");
    printf("                       [q]: 返回上一级\n");
    printf("> ");
}

void add_car(ArrayList<Car> &list) {
    using namespace util;
    Car c;
    printf("[edit_car_info] [add_car] 请输入:\n");
    c.id = input_field<decltype(c.id)>("                          车号");
    c.type = input_field<decltype(c.type)>("                          车型");
    c.price = input_field<decltype(c.price)>("                          价格");
    c.driver = input_field<decltype(c.driver)>("                          驾驶员");
    list.append(c);
    printf("[edit_car_info] [add_car] 已添加车辆:\n");
    printf("                          [%u] %s\n", (unsigned int)list.size() - 1, c.toString().c_str());
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
        case 'p':
            if (ss >> c >> i) {
                if (0 <= i && i < list.size()) {
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

//////// main program functions
namespace program {

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
    // TODO statistics
    printf("       [9] 退出但不保存\n");
    printf("       [0] 退出并保存\n");
    printf("> ");
}

void select_func(ArrayList<Car> &list) {
    string s;
    getline(cin, s);
    if (s == "1") {
        edit_car_info::edit_car_info(list);
    } else if (s == "9") {
        exit_without_saving();
    } else if (s == "0") {
        exit_with_saving(list);
    }
}

} // namespace program

int main() {
    using namespace program;
    ArrayList<Car> list = io::read_data(file_name);
    while (true) {
        print_menu();
        select_func(list);
    }
    return 0;
}

