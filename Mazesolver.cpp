#include <iostream>
#include <vector>

using namespace std;

struct Point {
    int x, y;
};

struct Node {
    Point pt;
    int dist;
};

int rowNum[] = {-1, 0, 0, 1};
int colNum[] = {0, -1, 1, 0};

bool isValid(int row, int col, int numRows, int numCols, vector<vector<int>>& maze) {
    return (row >= 0) && (row < numRows) && (col >= 0) && (col < numCols) && (maze[row][col] == 0);
}

int BFS(vector<vector<int>>& maze, Point src, Point dest) {
    if (maze[src.x][src.y] == 1 || maze[dest.x][dest.y] == 1)
        return -1;

    int numRows = maze.size();
    int numCols = maze[0].size();

    vector<vector<bool>> visited(numRows, vector<bool>(numCols, false));
    visited[src.x][src.y] = true;

    vector<Node> q;
    q.push_back({src, 0});
    int front = 0;

    while (front < q.size()) {
        Node curr = q[front];
        Point pt = curr.pt;

        if (pt.x == dest.x && pt.y == dest.y)
            return curr.dist;

        front++;

        for (int i = 0; i < 4; i++) {
            int row = pt.x + rowNum[i];
            int col = pt.y + colNum[i];

            if (isValid(row, col, numRows, numCols, maze) && !visited[row][col]) {
                visited[row][col] = true;
                q.push_back({{row, col}, curr.dist + 1});
            }
        }
    }

    return -1;
}

int main() {
    vector<vector<int>> maze = {
        { 0, 1, 0, 0, 0 },
        { 0, 1, 0, 1, 0 },
        { 0, 0, 0, 1, 0 },
        { 1, 1, 1, 1, 0 },
        { 0, 0, 0, 0, 0 }
    };

    Point src = {0, 0};
    Point dest = {4, 4};

    int dist = BFS(maze, src, dest);

    if (dist != -1)
        cout << "Shortest path is " << dist << endl;
    else
        cout << "No path exists" << endl;

    return 0;
}
