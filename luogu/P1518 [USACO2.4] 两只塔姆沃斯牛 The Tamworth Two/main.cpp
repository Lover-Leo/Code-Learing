#include <iostream>
#include <vector>

struct object
{
    int row = 0;
    int column = 0;
    char Direction = 'N';
};

void Move(const std::vector<std::vector<char>>& maps, object& obj)
{
    // 先计算前方位置，不立即移动
    int nextRow = obj.row;
    int nextColumn = obj.column;

    if (obj.Direction == 'N')
        nextRow--;
    else if (obj.Direction == 'E')
        nextColumn++;
    else if (obj.Direction == 'S')
        nextRow++;
    else
        nextColumn--;

    // 先判断边界，再访问地图
    if (nextRow < 0 || nextRow >= 10 ||
        nextColumn < 0 || nextColumn >= 10 ||
        maps[nextRow][nextColumn] == '*')
    {
        // 不能前进：原地顺时针转向
        if (obj.Direction == 'N')
            obj.Direction = 'E';
        else if (obj.Direction == 'E')
            obj.Direction = 'S';
        else if (obj.Direction == 'S')
            obj.Direction = 'W';
        else
            obj.Direction = 'N';
    }
    else
    {
        // 可以前进：更新坐标，方向不变
        obj.row = nextRow;
        obj.column = nextColumn;
    }
}

int main()
{
    std::vector<std::vector<char>> maps(
        10, std::vector<char>(10)
    );

    object C, F;

    for (int row = 0; row < 10; row++)
    {
        for (int column = 0; column < 10; column++)
        {
            std::cin >> maps[row][column];

            if (maps[row][column] == 'C')
            {
                C.row = row;
                C.column = column;
                maps[row][column] = '.';
            }
            else if (maps[row][column] == 'F')
            {
                F.row = row;
                F.column = column;
                maps[row][column] = '.';
            }
        }
    }

    for (int minute = 1; minute <= 160000; minute++)
    {
        Move(maps, C);
        Move(maps, F);

        // 两者都完成本分钟的行动后，再判断相遇
        if (C.row == F.row && C.column == F.column)
        {
            std::cout << minute << '\n';
            return 0;
        }
    }

    std::cout << 0 << '\n';
    return 0;