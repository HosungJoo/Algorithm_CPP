//SWEA 5650 핀볼게임

/*
    문제 읽기
    빈 공간에서만 돌리기
    최대값 구하기
    벽이나 블록에 부딪힐 때
*/
/*
    요구한 대로 구현
    0일떄 근처 방향에 벽이 있다면 
*/
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>

using namespace std;

int n;
int map[101][101];
//상하좌우
int ydir[4] = { -1, 1, 0, 0 };
int xdir[4] = { 0, 0, -1, 1 };
// direction map[i][j] :  j방향으로 갈떄, i(블록번호)를 마주치게 된다면 바뀌는 방향
int direction_map[6][4] = {
    {0, 1, 2, 3}, //상하좌우
    {1, 3, 0, 2}, //하우상좌
    {3, 0, 1, 2}, //우상하좌
    {2, 0, 3, 1}, // 좌상우하
    {1, 2, 3, 0}, //하좌우상
    {1, 0, 3, 2}  //하상우좌
};
int wormhole[5][4];
vector<pair<int, int>> temp;
vector<pair<int, int>> temp2;

int run(int y, int x, int dir);

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int test_case;
    int T;
    cin >> T;
    for (test_case = 1; test_case <= T; ++test_case)
    {
        int result = 0;
        cin >> n;
        memset(wormhole, -1, sizeof(wormhole));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> map[i][j];
                if (map[i][j] > 5) {
                    int hole_num = map[i][j] - 6;
                    if (wormhole[hole_num][0] != -1) {
                        wormhole[hole_num][2] = i;
                        wormhole[hole_num][3] = j;
                    }
                    else {
                        wormhole[hole_num][0] = i;
                        wormhole[hole_num][1] = j;
                    }
                }
            }
        }

        int cnt = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if(map[i][j] != 0) continue;
                for (int dir = 0; dir < 4; dir++) {
                    if(((i + ydir[dir]) >= 0) && ((i+ ydir[dir]) < n) && ((j + xdir[dir]) >= 0) && ((j + xdir[dir]) < n))
                    { 
                        if((map[i+ ydir[dir]][j + xdir[dir]] < 6) && (map[i+ ydir[dir]][j + xdir[dir]] > 0) && (direction_map[map[i+ ydir[dir]][j + xdir[dir]]][dir] != direction_map[5][dir])) {
                            result = max(result, run(i, j, dir));
                        }
                    }
                    //출발 후 바로 벽에 부딪히는 경우는 무조건 result가 1 이 경우에는 다음에 result가 0일떄 따로 계산해준다.
                }
            }
        }

        if(result == 0) {
            for(int i = 0; i < n; i++) {
                if((map[i][0] == 0) || (map[0][i] == 0) || (map[n - 1][i] == 0) || (map[i][n - 1] == 0)) {
                    result = 1;
                }
            }
        }

        cout << "#" << test_case << " " << result << endl;
    }
    return 0;
}

int run(int y, int x, int dir) {
    int result = 0;
    int i = y;
    int j = x;

    do {
        i += ydir[dir];
        j += xdir[dir];

        if ((i < 0) || (i >= n) || (j < 0) || (j >= n)) {
            result++;
            //5번 블록은 모두 반대방향
            dir = direction_map[5][dir];
            i += ydir[dir];
            j += xdir[dir];
            if((i == y) && (j == x)) return result;
        }

        int m = map[i][j];
        if (m == -1) return result;
        else if (m > 5) {
            if (i == wormhole[m - 6][0]) {
                i = wormhole[m - 6][2];
                j = wormhole[m - 6][3];
            }
            else {
                i = wormhole[m - 6][0];
                j = wormhole[m - 6][1];
            }
            continue;
        }
        else if (m > 0) {
            result++;
            dir = direction_map[m][dir];
        }
    } while ((i != y) || (j != x));
    return result;
}