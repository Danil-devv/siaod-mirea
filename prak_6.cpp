#include <stdio.h>
#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <vector>
#include <random>
#include <map>
#include <queue>
#include <stack>

using namespace std;

map<char, vector<char>> g;


// поиск в ширину (расстояние от вершины from до вершины to)
int bfs(char from, char to) {
    vector<int> dist(26, 0);

    queue<char> q;
    q.push(from);

    while (!q.empty()) {
        char v = q.front(); q.pop();

        for (auto u : g[v]) {
            if (dist[u - 'a'] == 0) {
                dist[u - 'a'] = dist[v - 'a'] + 1;
                q.push(u);
            }
            else if (dist[u-'a'] > dist[v-'a'] + 1) {
                dist[u-'a'] = dist[v-'a'] + 1;
                q.push(u);
            }
        }
    }

    return dist[to - 'a'];
}

void findEulerPath() {
	int n = 26;
	vector < vector<int> > h(n, vector<int>(n));
	for (auto u : g) {
		for (auto v : u.second) {
			h[u.first - 'a'][v - 'a'] = 1;
		}
	}
	
	vector<int> deg(n);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			deg[i] += h[i][j];

	int first = 0;
	while (!deg[first])  ++first;

	int v1 = -1, v2 = -1;
	bool bad = false;
	for (int i = 0; i < n; ++i)
		if (deg[i] & 1)
			if (v1 == -1)
				v1 = i;
			else if (v2 == -1)
				v2 = i;
			else
				bad = true;

	if (v1 != -1)
		++h[v1][v2], ++h[v2][v1];

	stack<int> st;
	st.push(first);
	vector<int> res;
	while (!st.empty())
	{
		int v = st.top();
		int i;
		for (i = 0; i < n; ++i)
			if (h[v][i])
				break;
		if (i == n)
		{
			res.push_back(v);
			st.pop();
		}
		else
		{
			--h[v][i];
			--h[i][v];
			st.push(i);
		}
	}

	if (v1 != -1)
		for (size_t i = 0; i + 1 < res.size(); ++i)
			if (res[i] == v1 && res[i + 1] == v2 || res[i] == v2 && res[i + 1] == v1)
			{
				vector<int> res2;
				for (size_t j = i + 1; j < res.size(); ++j)
					res2.push_back(res[j]);
				for (size_t j = 1; j <= i; ++j)
					res2.push_back(res[j]);
				res = res2;
				break;
			}

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			if (h[i][j])
				bad = true;

	if (bad)
		puts("-1");
	else
		for (size_t i = 0; i < res.size(); ++i)
			printf("%c ", 'a' + res[i]);
}

int main() {
    g['g'] = { 'h', 'f' };
    g['h'] = { 'g', 'f', 'k', 'i' };
    g['f'] = { 'g', 'h', 'a', 'b' };
    g['a'] = { 'f', 'b' };
    g['b'] = { 'a', 'f', 'd', 'c' };
    g['c'] = { 'b', 'd', 'j' };
    g['d'] = { 'b', 'c', 'i', 'j' };
    g['j'] = { 'c', 'd', 'i' };
    g['i'] = { 'j', 'd', 'k', 'h' };
    g['k'] = { 'h', 'i' };

    cout << bfs('a', 'i') << "\n"; // -> 3
	findEulerPath();

    return 0;
}