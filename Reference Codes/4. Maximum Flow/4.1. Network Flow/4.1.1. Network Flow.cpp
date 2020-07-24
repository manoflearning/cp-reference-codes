#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXV = 1e3;
const int INF = 1e9 + 7; 

int N, c[MAXV + 5][MAXV + 5], f[MAXV + 5][MAXV + 5];
vector<int> adj[MAXV + 5];
int prv[MAXV + 5];
int st, en;

void input();
int max_flow();
void BFS(int st, int en);
int flow(int st, int en);

int main() {
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    st = 1, en = N;
    int total = max_flow();

    cout << total << endl;

    return 0;
}

void input() {
    cin >> N;

    for (int i = 0; i < N; i++) {
        int n1, n2, cap;
        cin >> n1 >> n2 >> cap;

        c[n1][n2] += cap;

        adj[n1].push_back(n2);
        //역방향 간선을 추가해야 한다
        adj[n2].push_back(n1);
    }
}

int max_flow() {
    int ret = 0;
    while (true) {
        BFS(st, en);

        if (prv[en] == -1) break;

        ret += flow(st, en);
    }
    return ret;
}

void BFS(int st, int en) {
    memset(prv, -1, sizeof(prv));

    queue<int> q;
    q.push(st);
    prv[st] = 0;

    while (!q.empty() && prv[next] == -1) {
        int now = q.front();
        q.pop();

        for (int next : adj[now]) {
            if (prv[next] == -1 && c[now][next] - f[now][next] > 0) {
                q.push(next);
                prv[next] = now;
            }
        }
    }
}

int flow(int st, int en) {
    int block = INF;
    for (int i = en; i != st; i = prv[i]) {
        block = min(block, c[prv[i]][i] - f[prv[i]][i]);
    }
    for (int i = en; i != st; i = prv[i]) {
        f[prv[i]][i] += block;
        f[i][prv[i]] -= block;
    }
    return block;
}
