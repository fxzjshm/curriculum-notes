#include "io.hpp"

#include<fstream>

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