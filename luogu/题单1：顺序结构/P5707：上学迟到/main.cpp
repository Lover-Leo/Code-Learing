#include<iostream>
#include<iomanip>
#include<cmath>
//学校和 yyy 的家之间的距离为 s 米，而 yyy 以 v 米每分钟的速度匀速走向学校。
//在上学的路上，yyy 还要额外花费 10 分钟的时间进行垃圾分类。
//学校要求必须在上午 8:00 到达，请计算在不迟到的前提下，yyy 最晚能什么时候出门。
//由于路途遥远，yyy 可能不得不提前一点出发，但是提前的时间不会超过一天。
//注意，yyy 只能在每分钟的第 0 秒时出发。
int main()
{
    double s,v;
    std::cin >> s >> v;
    int needed = static_cast<int>(std::ceil(s / v)) + 10;
    int depart_minute = 480 - needed;
    if(depart_minute < 0)
    {
        depart_minute += 24 * 60;
    }
    int hour = depart_minute / 60;
    int minute = depart_minute % 60;
    std::cout << std::setfill('0') << std::setw(2) << hour << ':'
        << std::setfill('0') << std::setw(2) << minute << '\n';
    return 0;
}