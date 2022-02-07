#pragma once

#include <vector>
#include <unordered_set>
using namespace std;

//LeetCode

//Number of Islands（岛屿的个数）/problems/number-of-islands/
int numIslands(vector<vector<char>>& grid) {
	int count = 0;
	for (int i = 0; i < grid.size(); i++) {
		for (int j = 0; j < grid[0].size(); j++) {
			if (grid[i][j] == '1') {
				dfs(grid, i, j);
				count++;
			}
		}
	}
	return count;
}
void dfs(vector<vector<char>>& grid, int i, int j) {
	if (i < 0 || j < 0 || i >= grid.size() || j >= grid[0].size() || grid[i][j] == '0')
		return;
	// set to 0 (visited)
	grid[i][j] = '0';
	// search surrounding cells at horizontal/vertical
	dfs(grid, i + 1, j);
	dfs(grid, i, j + 1);
	dfs(grid, i - 1, j);
	dfs(grid, i, j - 1);
}

//Valid Sudoku（有效的数独）/problems/valid-sudoku/
bool isValidSudoku(vector<vector<char>>& board) {
	vector<unordered_set<char>> row(9);
	vector<unordered_set<char>> col(9);
	vector<unordered_set<char>> box(9);

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (board[i][j] == '.') { continue; }

			if (!((row[i].find(board[i][j]) == row[i].end()) &&
				(col[j].find(board[i][j]) == col[j].end()) &&
				(box[j / 3 + (i / 3) * 3].find(board[i][j]) == box[j / 3 + (i / 3) * 3].end())))
			{
				return false;
			}

			row[i].insert(board[i][j]);
			col[j].insert(board[i][j]);
			box[j / 3 + (i / 3) * 3].insert(board[i][j]);

		}
	}
	return true;
}