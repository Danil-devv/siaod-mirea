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

vector<vector<pair<int, int>>> g = {
	{
		{-1, 7}, {-1, 3}, {-1, 4}, {-1, 2}, {-1, -1}   // 1
	},
	{
		{5, 2}, {6, 0}, {4, 7}, {1, 1}, {-1, 5}        // 2
	},
	{
		{8, 1}, {3, 4}, {5, 2}, {1, 7}, {-1, 2}        // 3
	},
	{
		{13, 27}, {15, 11}, {3, 9}, {12, 17}, {-1, 7}  // 4
	},
	{
		{14, 9}, {2, 7}, {4, 4}, {5, 1}, {-1, 1}       // 5
	}
	//     1       2        3       4       5
};

int main() {
	pair<int, int> start, finish;

	cout << "Input start and finish ceils:\n";
	cin >> start.first >> start.second >> finish.first >> finish.second;
	start.first--; start.second--;
	finish.first--; finish.second--;

	int n = g.size(), m = g[0].size();

	vector<vector<int>> dp(n, vector<int> (m, 1e9));
	dp[start.first][start.second] = 0;


	// start = {5, 1}; finish = {3; 5}
	// 1e9 1e9 1e9 1e9 1e9
	// 1e9 1e9 1e9 1e9 1e9
	// 1e9 1e9 1e9 1e9 1e9
	// 1e9 1e9 1e9 1e9 1e9
	//  0  1e9 1e9 1e9 1e9

	for (int i = n - 1; i >= 0; i--) {
		for (int j = 0; j < m; j++) {
			if (i != n - 1) {
				dp[i][j] = min(dp[i][j], dp[i + 1][j] + g[i + 1][j].first);
			}
			if (j != 0) {
				dp[i][j] = min(dp[i][j], dp[i][j - 1] + g[i][j - 1].second);
			}
		}
	}

	cout << dp[finish.first][finish.second];
	return 0;
}