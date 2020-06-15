//
// Created by sen on 2020/6/2.
//
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;


/**
 * 695. 岛屿的最大面积
 *
 * 给定一个包含了一些 0 和 1 的非空二维数组 grid 。
 * 一个 岛屿 是由一些相邻的 1 (代表土地) 构成的组合，这里的「相邻」要求两个 1 必须在水平或者竖直方向上相邻。你可以假设 grid 的四个边缘都被 0（代表水）包围着。
 * 找到给定的二维数组中最大的岛屿面积。(如果没有岛屿，则返回面积为 0 。)
 */
class Solution {
public:
    vector<vector<int>> direction = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    int dfs(vector<vector<int>>& grid, int i, int j) {
        if (i<0 || i>=grid.size() || j<0 || j>=grid[0].size() || grid[i][j]==0)
            return 0;

        int cnt = 1;
        grid[i][j] = 0;
        for (auto &d :direction)
            cnt += dfs(grid, i+d[0], j+d[1]);

        return cnt;
    }

    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int max_area = 0;
        for (int i = 0; i < grid.size(); i++)
            for (int j = 0; j < grid[0].size(); j++)
                max_area = max(dfs(grid, i, j), max_area);
        return max_area;
    }
};

/**
 * 200. 岛屿数量
 * 给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。
 * 岛屿总是被水包围，并且每座岛屿只能由水平方向或竖直方向上相邻的陆地连接形成。
 * 此外，你可以假设该网格的四条边均被水包围。
 *
 * 典型的dfs，套模板
 */
class Solution2 {
public:

    vector<vector<int>> direction = {{1,0},{-1,0},{0,1},{0,-1}};
    int dfs(vector<vector<char>>& grid, int i, int j) {
        if (i<0 || i>=grid.size() || j<0 || j>=grid[0].size() || grid[i][j] == '0')
            return 0;

        grid[i][j] = '0';
        for (auto &d : direction)
            dfs(grid, i+d[0], j+d[1]);
        return 1;
    }

    int numIslands(vector<vector<char>>& grid) {
        int cnt = 0;
        for (int i = 0; i < grid.size(); i++)
            for (int j = 0; j < grid[0].size(); j++)
                cnt += dfs(grid, i, j);
        return cnt;
    }
};


/**
 * 547. 朋友圈
 * 班上有 N 名学生。其中有些人是朋友，有些则不是。他们的友谊具有是传递性。如果已知 A 是 B 的朋友，B 是 C 的朋友，那么我们可以认为 A 也是 C 的朋友。所谓的朋友圈，是指所有朋友的集合。
 * 给定一个 N * N 的矩阵 M，表示班级中学生之间的朋友关系。如果M[i][j] = 1，表示已知第 i 个和 j 个学生互为朋友关系，否则为不知道。你必须输出所有学生中的已知的朋友圈总数
 * 套用dfs模板，下层递归的获取策略改变即可
 */
class Solution3 {
public:

    int dfs(vector<vector<int>>& M, int i, int j) {
        if (i<0 || i>=M.size() || j<0 || j>= M[0].size() || M[i][j] == 0)
            return 0;

        M[i][j] = 0;
        for (int k = 0; k < M[0].size(); k++)
            if (M[i][k] > 0)
                dfs(M, k, k); // 这里有的递归是不必要的，所以会造成内存占用过高
        return 1;
    }

    int findCircleNum(vector<vector<int>>& M) {
        int cnt = 0;
        for (int k = 0; k < M.size(); k++)
            cnt += dfs(M, k, k);
        return cnt;
    }
};


/**
 * 130. 被围绕的区域
 * 给定一个二维的矩阵，包含 'X' 和 'O'（字母 O）。
 * 找到所有被 'X' 围绕的区域，并将这些区域里所有的 'O' 用 'X' 填充。
 * 被围绕的区间不会存在于边界上，换句话说，任何边界上的 'O' 都不会被填充为 'X'。 任何不在边界上，或不与边界上的 'O' 相连的 'O' 最终都会被填充为 'X'。如果两个元素在水平或垂直方向相邻，则称它们是“相连”的。
 *
 * 对边缘套用递归模板即可
 */
class Solution4 {
public:

    vector<vector<int>> direction = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    void dfs(vector<vector<char>>& board, int i, int j) {
        if (i<0 || i>=board.size() || j<0 || j>=board[0].size() || board[i][j] == 'N' || board[i][j] == 'X')
            return;

        board[i][j] = 'N';
        for (auto &d : direction)
            dfs(board, i+d[0], j+d[1]);
    }

    void solve(vector<vector<char>>& board) {
        if (board.size() == 0) return;
        for (int i = 0; i < board.size(); i++) {
            dfs(board, i, 0);
            dfs(board, i, board[0].size()-1);
        }

        for (int j = 0; j < board[0].size(); j++) {
            dfs(board, 0, j);
            dfs(board, board.size()-1, j);
        }

        for (int i = 0; i < board.size(); i++)
            for (int j = 0; j < board[0].size(); j++)
                board[i][j] = board[i][j] == 'N' ? 'O' : 'X';

    }
};

/**
 * 417. 太平洋大西洋水流问题
 * 给定一个 m x n 的非负整数矩阵来表示一片大陆上各个单元格的高度。“太平洋”处于大陆的左边界和上边界，而“大西洋”处于大陆的右边界和下边界。
 * 规定水流只能按照上、下、左、右四个方向流动，且只能从高到低或者在同等高度上流动。
 * 请找出那些水流既可以流动到“太平洋”，又能流动到“大西洋”的陆地单元的坐标。
 *
 * 通过将结果记录在visited数组中，比较visited数组来确定结果。
 */
class Solution5 {
public:
    vector<vector<int>> direction = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    int R = 0, C = 0;

    void dfs(vector<vector<int>>& matrix, vector<vector<bool>>& cache, int i, int j, int lastm) {
        if (i<0 || i>=R || j<0 || j>=C || cache[i][j] || matrix[i][j] < lastm)
            return ;

        cache[i][j] = true;
        for (auto &d: direction)
            dfs(matrix, cache, i+d[0], j+d[1], matrix[i][j]);
    }

    vector<vector<int>> pacificAtlantic(vector<vector<int>>& matrix) {
        vector<vector<int>> ans;
        if (matrix.size() == 0 || matrix[0].size() == 0) return ans;

        R = matrix.size(), C = matrix[0].size();
        vector<vector<bool>> cacheT(R, vector<bool>(C, false));
        vector<vector<bool>> cacheD(R, vector<bool>(C, false));

        for (int i = 0; i < R; i++) {
            dfs(matrix, cacheT, i, 0, matrix[i][0]);
            dfs(matrix, cacheD, i, C-1, matrix[i][C-1]);
        }

        for (int j = 0; j < C; j++) {
            dfs(matrix, cacheT, 0, j, matrix[0][j]);
            dfs(matrix, cacheD, R-1, j, matrix[R-1][j]);
        }

        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
                if (cacheT[i][j] && cacheD[i][j])
                    ans.emplace_back(vector<int>{i, j});

        return ans;
    }
};