#include <cstdio>
#include <memory>
#include <string>

#include "LinkedList.hpp"
#include "util.hpp"

using namespace std;

Time::Time(string &s1, string &s2) {
    int c1, c2;
    c1 = sscanf(s1.c_str(), "%d-%d-%d", &year, &month, &day);
    c2 = sscanf(s2.c_str(), "%d:%d:%d", &hour, &minute, &second);
    if (c1 != 3 || c2 != 3) {
        throw runtime_error("参数错误");
    }
    util::check_date(year, month, day);
    util::check_value(hour, 0, 24, "时间错误");
    util::check_value(minute, 0, 59, "时间错误");
    util::check_value(second, 0, 60, "时间错误");
}

string Time::toString() {
    return util::sprintf_cxx("%d-%02d-%02d %02d:%02d:%02d", year, month, day,
                             hour, minute, second);
}

string Incident::toString() {
    return util::sprintf_cxx("时间: %s, 地点: %s, 违章代码: %d, 是否处理: %s",
                             time.toString().c_str(), place.c_str(), code,
                             util::localize_bool(ok).c_str());
}

string Car::toString() {
    return util::sprintf_cxx("车号: %d, 车型: %s, 价格: %.1f, 驾驶员: %s", id,
                             type.c_str(), price, driver.c_str());
}
