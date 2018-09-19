#include "Pathfinder.h"

Pathfinder::Pathfinder()
{
  clearMaze();
}

Pathfinder::~Pathfinder()
{
}

string Pathfinder::toString() const
{
  int x, y = 0;
  stringstream mazeStr;
  for(y = 0; y < SIZE; y++)
  {
    for(x = 0; x < SIZE; x++)
    {
      mazeStr << maze[x][y];
      if(x != SIZE-1)
        mazeStr << " ";
    }
    if(y != SIZE-1)
      mazeStr << endl;
  }
  return mazeStr.str();
}

void Pathfinder::createRandomMaze()
{
  srand(time(NULL));
  int x, y;
  for(x = 0; x < SIZE; x++)
  {
    for(y = 0; y < SIZE; y++)
    {
      maze[x][y] = rand() % 2;
    }
  }
  maze[0][0] = 1;
  maze[SIZE-1][SIZE-1] = 1;
}

bool Pathfinder::importMaze(string file_name)
{
  ifstream ifs;
  string line;
  int x, y = 0;
  int mazeValues[SIZE][SIZE];

  // Open file
  ifs.open(file_name, ifstream::in);
  if(!ifs.is_open())
    return false;

  for(y = 0; y < SIZE; y++)
  {
    // Read in line, make sure it works
    getline(ifs, line);
    if(ifs.bad() || ifs.fail())
      return false;
    if(line.size() != 9)
      return false;
    for(x = 0; x < SIZE; x++)
    {
      if(line[x*2] == '0')
        mazeValues[x][y] = 0;
      else if(line[x*2] == '1')
        mazeValues[x][y] = 1;
      else
        return false;
    }
  }

  // Check for no extra lines
  getline(ifs, line);
  if(!ifs.bad() && !ifs.fail())
    return false;

  // Check first and last cells
  if(mazeValues[0][0] == 0 || mazeValues[SIZE-1][SIZE-1] == 0)
    return false;

  setMaze(mazeValues);
  return true;
}

vector<string> Pathfinder::solveMaze()
{
  vector<string> path;
  unordered_set<string> visited;
  path = findPath(path, visited, 0, 0);
  return path;
}

vector<string> Pathfinder::findPath(vector<string> path, unordered_set<string>& visited, int x, int y)
{
  // If position (x, y) is outside of maze, return empty vector
  vector<string> empty;
  if(x < 0 || x >= SIZE || y < 0 || y >= SIZE)
    return empty;
  
  // If position (x, y) is an invalid path (a 0 cell), return empty vector
  if(maze[x][y] == 0)
    return empty;

  // If any paths have visited this position before, return empty vector
  stringstream ss;
  ss << "(" << x << ", " << y << ")";
  string coorStr = ss.str();
  if(visited.find(coorStr) != visited.end())
    return empty;

  // Add current coordinates to path and to visited
  path.push_back(coorStr);
  visited.insert(coorStr);

  // If end of maze, return path
  if(x == SIZE-1 && y == SIZE-1)
  {
    return path;
  }

  // Explore in all directions
  // If any direction gives a non-empty path, return the non-empty path
  vector<string> leftPath = findPath(path, visited, x-1, y);
  if(!leftPath.empty())
    return leftPath;

  vector<string> rightPath = findPath(path, visited, x+1, y);
  if(!rightPath.empty())
    return rightPath;

  vector<string> upPath = findPath(path, visited, x, y-1);
  if(!upPath.empty())
    return upPath;

  vector<string> downPath = findPath(path, visited, x, y+1);
  if(!downPath.empty())
    return downPath;

  // If all directions return empty path, return empty path
  return empty;
}

void Pathfinder::clearMaze()
{
  int x, y;
  for(x = 0; x < SIZE; x++)
  {
    for(y = 0; y < SIZE; y++)
    {
      maze[x][y] = 1;
    }
  }
}

void Pathfinder::setMaze(int mazeValues[SIZE][SIZE])
{
  int x, y = 0;
  for(x = 0; x < SIZE; x++)
  {
    for(y = 0; y < SIZE; y++)
    {
      maze[x][y] = mazeValues[x][y];
    }
  }
}
