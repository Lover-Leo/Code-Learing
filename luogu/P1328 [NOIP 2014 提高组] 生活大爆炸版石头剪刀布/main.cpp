#include<iostream>
#include<vector>
using namespace std;

vector<vector<char>> result(5,vector<char>(5,'0'));

int main()
{
    result[0][1] = 'B';
    result[0][2] = 'A';
    result[0][3] = 'A';
    result[0][4] = 'B';
    result[1][2] = 'B';
    result[1][3] = 'A';
    result[1][4] = 'B';
    result[2][3] = 'B';
    result[2][4] = 'A';
    result[3][4] = 'A';

    int N,Na,Nb;
    cin >> N >> Na >> Nb;

    vector<int> A;
    vector<int> B;

    for(int i = 0;i < Na;i++)
    {
        int a;
        cin >> a;
        A.push_back(a);
    }
    for(int i = 0;i < Nb;i++)
    {
        int a;
        cin >> a;
        B.push_back(a);
    }

    vector<int> numA(N,-1);
    vector<int> numB(N,-1);
    
    int num = 0;
    for(int i = 0;i < N;i++)
    {
        numA[i] = A[num];
        num++;

        if(num == Na)
        {
            num = 0;
        }
    }

    num = 0;
    for(int i = 0;i < N;i++)
    {
        numB[i] = B[num];
        num++;

        if(num == Nb)
        {
            num = 0;
        }
    }

    int scoreA = 0,scoreB = 0;

    for(int i = 0;i < N;i++)
    {
        if(numA[i] > numB[i])
        {
            if(result[numB[i]][numA[i]] == 'A')
                scoreB++;
            if(result[numB[i]][numA[i]] == 'B')
                scoreA++;
        }
        else
        {
            if(result[numA[i]][numB[i]] == 'A')
            scoreA++;
            if(result[numA[i]][numB[i]] == 'B')
            scoreB++;
        }
    }

    cout << scoreA << ' ' << scoreB;

    return 0;
}
