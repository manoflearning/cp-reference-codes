int N, dfsn[MAXV + 5], dCnt;
vector<int> adj[MAXV + 5];
stack<pair<int, int>> stk;
vector<vector<pair<int, int>>> bcc;

int dfs(int now, int prv = -1);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	memset(dfsn, -1, sizeof(dfsn));

	for (int v = 1; v <= N; v++)
		if (dfsn[v] == -1) dfs(v);

	return 0;
}

int dfs(int now, int prv) {
	int ret = dfsn[now] = ++dCnt;

	for (int next : adj[now]) {
		//�θ� ��� ��ŵ
		if (next == prv) continue;

		//���� �湮���� ���� 
		if (dfsn[now] > dfsn[next]) stk.push({ now, next });
		//������ ����
		if (dfsn[next] != -1) ret = min(ret, dfsn[next]);
		//Ʈ�� ����
		else {
			int tmp = dfs(next, now);
			ret = min(ret, tmp);
            
			//�ڼ� ��忡�� ���� ����� ���� ���� �� �� �ִ� ��ΰ� ����
			if (tmp >= dfsn[now]) {
				vector<pair<int, int>> nowBCC;
				while (true) {
					pair<int, int> t = stk.top();
					stk.pop();

					nowBCC.push_back(t);

					if (t == pair<int, int>(now, next)) break;
				}

				bcc.push_back(nowBCC);
			}
		}
	}

	return ret;
}
