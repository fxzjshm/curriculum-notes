#include "util.hpp"

#include "structs.hpp"

namespace util {
Time input_time(string prefix) {
    string date, time;
    while (true) {
        date = input_field<decltype(date)>(prefix + "日期 (示例: 1970-01-01)");
        time = input_field<decltype(time)>(prefix + "时间 (示例: 00:00:00)");
        try {
            Time t = Time(date, time);
            return t;
        } catch (runtime_error e) {
            printf("[input_time] 错误: 请输入正确的日期与时间: %s\n", e.what());
        }
    }
}
} // namespace util