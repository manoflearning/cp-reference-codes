#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

const int INF = 1e9 + 7;
const int MAXV = 1000;

int N, M, st = 0, en = MAXV + 1;
int c[MAXV + 5][MAXV + 5], f[MAXV + 5][MAXV + 5];
int d[MAXV + 5][MAXV + 5], prv[MAXV + 5];
vector<int> adj[MAXV + 5];
int mFlow, mCost;

void input();
void mcmf();
void spfa();
void flow();

int main() {
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    mcmf();

    cout << mFlow << '\n' << mCost << '\n';

    return 0;
}

void input() {
    //»ý·«
}

void mcmf() {
    while (true) {
        spfa();

        if (prv[en] == -1) break;

        flow();
    }
}

void spfa() {
    memset(prv, -1, sizeof(prv));
    vector<int> dist(MAXV + 5, INF);
    vector<bool> inQ(MAXV + 5);

    queue<int> q;
    q.push(st);
    dist[st] = 0, inQ[st] = true;

    while (!q.empty()) {
        int now = q.front();
        q.pop();

        inQ[now] = false;

        for (int next : adj[now]) {
            if (dist[now] + d[now][next] < dist[next] && c[now][next] - f[now][next] > 0) {
                dist[next] = dist[now] + d[now][next];
                prv[next] = now;
                if (!inQ[next]) {
                    inQ[next] = true;
                    q.push(next);
                }
            }
        }
    }
}

void flow() {
    int block = INF;
    for (int i = en; i != st; i = prv[i]) {
        block = min(block, c[prv[i]][i] - f[prv[i]][i]);
    }
    for (int i = en; i != st; i = prv[i]) {
        mCost += d[prv[i]][i] * block;
        f[prv[i]][i] += block;
        f[i][prv[i]] -= block;
    }
    mFlow += block;
}
