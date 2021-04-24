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
};

template <typename T> struct LinkedListNode {
  public:
    T data;
    std::weak_ptr<LinkedListNode<T>> prev;
    std::shared_ptr<LinkedListNode<T>> next;

    LinkedListNode(T value) { data = value; }
};

template <typename T> struct LinkedList : public List<T> {
  public:
    size_t n;
    std::shared_ptr<LinkedListNode<T>> head;
    std::weak_ptr<LinkedListNode<T>> tail;

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
                n2_s.get()->next =
                    std::make_shared<LinkedListNode<T>>(*n3_s.get());
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
            // printf("Not empty list.\n");
            insert_right(tail.lock(), data);
            // printf("!tail.expired(): %d\n",!tail.expired());
        } else {
            // printf("Empty list.\n");
            LinkedListNode<T> node = LinkedListNode<T>(data);
            head = make_shared<LinkedListNode<T>>(node);
            tail = weak_ptr<LinkedListNode<T>>(head);
        }

        n++;
    }

    LinkedList() { n = 0; }
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

    T operator[](size_t i) {
        if (0 <= i && i < n) {
            return p_data[i];
        } else {
            panic();
        }
    }

    inline size_t size() { return n; }

    void append(T value) override { push_back(value); }

    void delete_at(size_t i) {
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

//////// Structs & Classes

struct Car;
struct Incident;

struct Time {
    int year, month, day, hour, minute, second;

    Time() {}

    Time(string &s1, string &s2) {
        sscanf(s1.c_str(), "%d-%d-%d", &year, &month, &day);
        sscanf(s2.c_str(), "%d:%d:%d", &hour, &minute, &second);
    }

    string toString() {
        stringstream ss;
        ss << year << "-" << month << "-" << day << " ";
        ss << hour << ":" << minute << ":" << second;
        return ss.str();
    }
};

struct Incident { // WZ
    Time time;
    string place;
    int code;
    bool ok;
    std::shared_ptr<Car> p_car;

    void print_verbose() {
        printf("时间: %s, 地点: %s, 违章代码: %d, 是否处理: %s\n",
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

    void print_verbose() {
        printf("车号: %d, 车型: %s, 价格: %.1f, 驾驶员: %s\n", id, type.c_str(),
               price, driver.c_str());
    }

    void print_incident_verbose() {
        print_verbose();
        unsigned int m = incidents.n;
        printf("违章总数: %d\n", m);
        std::shared_ptr<LinkedListNode<Incident>> p = incidents.head;
        for (int x = 0; x < m; x++) {
            if (!p) {
                panic();
            }
            Incident i = p.get()->data;
            printf("[%d] ", x);
            i.print_verbose();
            p = p.get()->next;
        }
    }
};

//////// utilities
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

        unsigned int m = c.incidents.n;
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

//////// edit car information
namespace edit_car_info {

void print_cars_verbose(ArrayList<Car> &list) {
    size_t n = list.size();
    for (int i = 0; i < n; i++) {
        Car c = list[i];
        printf("            [%d] ", i);
        c.print_verbose();
    }
}

void print_menu() {
    printf("[edit_info] [Menu] 请输入编号以选择功能: (示例: \"p 0\", "
           "不含引号)\n");
    printf("                   [p 序号]: 输出该车的违章记录并操作\n");
    printf("                   [d 序号]: 删除该车\n");
    printf("                   [a]: 新增车辆\n");
    printf("                   [q]: 返回上一级\n");
    printf("> ");
}

void add_car(ArrayList<Car> &list) {
    using namespace util;
    Car c;
    printf("[edit_info] [add_car] 请输入:\n");
    c.id = input_field<decltype(c.id)>("                      车号");
    c.type = input_field<decltype(c.type)>("                      车型");
    c.price = input_field<decltype(c.price)>("                      价格");
    c.driver = input_field<decltype(c.driver)>("                      驾驶员");
    list.append(c);
    printf("[edit_info] [add_car] 已添加车辆:\n");
    printf("                      [%u] ", (unsigned int)list.size() - 1);
    c.print_verbose();
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
                    list[i].print_incident_verbose();
                    // edit_incident_info::edit_incident_info();
                } else {
                    printf("[edit_info] 错误: 序号越界\n\n");
                }
            } else {
                printf("[edit_info] 错误: 请输入序号\n\n");
            }
            break;
        case 'd':
            if (ss >> c >> i) {
                if (0 <= i && i < list.size()) {
                    list.delete_at(i);
                    printf("[edit_info] 已删除序号为 %d 的车辆\n\n", i);
                } else {
                    printf("[edit_info] 错误: 序号越界\n\n");
                }
            } else {
                printf("[edit_info] 错误: 请输入序号\n\n");
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
        printf("[edit_info] 已有车辆信息如下：\n");
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

