#pragma once
#include <sstream>
#include <fstream>
#include <algorithm>
#include <unordered_set>
#include "PathfinderInterface.h"

#define SIZE 5

class Pathfinder: public PathfinderInterface
{
private:
  int maze[SIZE][SIZE];
  vector<string> findPath(vector<string> path, unordered_set<string>& visited, int x, int y);
  void clearMaze();
  void setMaze(int mazeValues[SIZE][SIZE]);
public:
  Pathfinder();
  ~Pathfinder();
  string toString() const;
  void createRandomMaze();
  bool importMaze(string file_name);
  vector<string> solveMaze();
};
