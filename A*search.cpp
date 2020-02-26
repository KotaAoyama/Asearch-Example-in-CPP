#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
using std::cout;
using std::ifstream;
using std::istringstream;
using std::string;
using std::vector;
using std::abs;
using std::sort;

enum class State {kEmpty, kObstacle, kClosed, kPath};


vector<State> ParseLine(string line) {
    istringstream sline(line);
    int n;
    char c;
    vector<State> row;
    while (sline >> n >> c && c == ',') {
      if (n == 0) {
        row.push_back(State::kEmpty);
      } else {
        row.push_back(State::kObstacle);
      }
    }
    return row;
}


vector<vector<State>> ReadBoardFile(string path) {
  ifstream myfile (path);
  vector<vector<State>> board{};
  if (myfile) {
    string line;
    while (getline(myfile, line)) {
      vector<State> row = ParseLine(line);
      board.push_back(row);
    }
  }
  return board;
}


bool Compare(vector<int> a, vector<int> b) {
  int f1 = a[2] + a[3];
  int f2 = b[2] + b[3];
  return f1 > f2;
}


void CellSort(vector<vector<int>> *v) {
  sort(v->begin(), v->end(), Compare);
}


int Heuristic(int x1, int y1, int x2, int y2) {
  return abs(x2 - x1) + abs(y2 - y1);
}


bool CheckValidCell(int x, int y, vector<vector<State>> &grid) {
  bool isXOnGrid = (x >= 0 && x < grid.size());
  bool isYOnGrid = (y >= 0 && y < grid[0].size());
  if (isXOnGrid && isYOnGrid) {
    return grid[x][y] == State::kEmpty;
  }
  return false;
}


void AddToOpen(int x, int y, int g, int h, vector<vector<int>> &openlist, vector<vector<State>> &grid) {
  openlist.push_back(vector<int> {x, y, g, h});
  grid[x][y] = State::kClosed;
}


vector<vector<State>> Search(vector<vector<State>> grid, int init[2], int goal[2] ) {
  
  vector<vector<int>> open{};

  int x = init[0];
  int y = init[1];
  int g = 0;
  int h = Heuristic(x, y, goal[0], goal[1]);
  AddToOpen(x, y, g, h, open, grid);

  while (open.size() > 0) {
    CellSort(&open);
    auto currentNode = open.back();
    open.pop_back();
    x = currentNode[0];
    y = currentNode[1];
    grid[x][y] = State::kPath;

    if (x == goal[0] && y == goal[1]) {
      return grid;
    }
  }

  cout << "No path found!" << "\n";
  return vector<vector<State>>{};
}


string CellString(State cell) {
  switch(cell) {
    case State::kObstacle: return "⛰️   ";
    case State::kPath: return "🚗   ";
    default: return "0   "; 
  }
}


void PrintBoard(const vector<vector<State>> board) {
  for (int i = 0; i < board.size(); i++) {
    for (int j = 0; j < board[i].size(); j++) {
      cout << CellString(board[i][j]);
    }
    cout << "\n";
  }
}

#include "test.cpp"

int main() {
  int init[2]{0, 0};
  int goal[2]{4, 5};
  auto board = ReadBoardFile("1.board");
  auto solution = Search(board, init, goal);
  PrintBoard(solution);
  // Tests
  TestHeuristic();
  TestAddToOpen();
  TestCompare();
  TestSearch();
  TestCheckValidCell();
}