#include<iostream>
#include<vector>
using namespace std;
int main()
{
    int n,m;
    cin >> n >> m;
    vector<vector<int>> numbox;
    vector<vector<int>> copy;


    int a = 1;

    for(int row = 0;row < n;row++)
    {
        numbox.push_back(vector<int>{});
        copy.push_back(vector<int>{});


        for(int line = 0;line < n;line++)
        {
            numbox[row].push_back(a);
            copy[row].push_back(a);
            a++;
        }
    }

    int x,y,r,z;

    for(int i = 0;i < m;i++)
    {
        cin >> x >> y >> r >> z;
        
        x -= 1;
        y -= 1;

        if(z == 0)
        {
            int x1 = x + r,y1 = y - r;
            for(int row = x - r;row <= x+r;row++)
            {
                for(int line = y - r;line <= y + r;y++)
                {
                    numbox[row][line] = copy[x1][y1];
                    x1--;
                }
                x1 = x + r;
                y1++;
            }
        }

        if(z == 1)
        {
            int x1 = x - r,y1 = y + r;
            for(int row = x - r;row <= x+r;row++)
            {
                for(int line = y - r;line <= y + r;line++)
                {
                    numbox[row][line] = copy[x1][y1];
                    x1++;
                }
                x1 = x - r;
                y1--;
            }
        }

        for(int row = 0;row < n;row++)
        {
            for(int line = 0;line < n;line++)
            {
                copy[row][line] = numbox[row][line];
            }
        }
    }

    for(const auto row: numbox)
    {
        for(const auto num: row)
        {
            cout << num << ' ';
        }
        cout << '\n';
    }

    return 0;
}