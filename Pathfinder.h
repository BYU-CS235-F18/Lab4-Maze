/*
WARNING: It is expressly forbidden to modify any part of this file, including its name
*/
#pragma once
#include <sstream>
#include <fstream>
#include <algorithm>
#include <unordered_set>
#include "PathfinderInterface.h"

/*
 * The size of the maze in every dimension. Each dimension of the maze has valid indices
 * between 0 and SIZE-1. You should use SIZE in your .cpp file.
 */
#define SIZE 5

/*
WARNING: It is expressly forbidden to modify any part of this file, including its name
*/
class Pathfinder
{
private:

  /*
   * 3-dimensional array of integers. The constructor should initiate all values to 1.
   * Values are 0 or 1. 1 means a valid path, 0 means an invalid path (i.e. a wall).
   */
  int maze[SIZE][SIZE][SIZE];

  /*
   * This is the recursive helper function called by solveMaze.
   *
   * It will return a vector of strings that represents the path.
   * Each string in the vector should look something like this:
   *  (0, 4, 2) for position x=0, y=4, z=2.
   *
   * It will return an empty vector if input is invalid or a valid path
   *  is not found.
   *
   * The path parameter is a vector of strings where each string has
   *  the format above. It represents the path you are currently exploring.
   *  It is a pass-by-value parameter, so the path will be copied every time
   *  you make a recursive call.
   * When solveMaze first calls findPath, the path parameter should just be
   *  an empty vector because you haven't started exploring anything yet.
   *  Whenever you visit a valid position in the maze, push_back the
   *  coordinate string onto the path.
   *
   * The visited parameter is an unordered_set of strings where each string
   *  has the format above. It represents ALL coordinates that have been
   *  visited. So "path" has the coordinates of the path you are CURRENTLY
   *  exploring and "visited" has the coordinates of every position you have
   *  ever explored. It is a pass-by-reference parameter, so it will NOT be
   *  copied every time you make a recursive call, which allows it to store
   *  every cell visited in any recursive path (instead of just the current
   *  one).
   * When solveMaze first calls findPath, the visited parameter should just
   *  be an empty set. Whenever you visit a valid position in the maze,
   *  insert the coordinate string into the "visited" set.
   *
   * The x, y, z parameters represent the current position you're exploring.
   *  You can use a stringstream to make a string representation of the
   *  coordinates so that you can add the position to your "path" and
   *  "visited" containers.
   * When solveMaze first calls findPath, what should x, y, z be?
   *
   *  --- BASE CASES ---
   * Remember that all recursive functions need base cases, some case where
   *  the function is not called recursively. Otherwise it will result in
   *  an infinite loop that will cause a stack overflow error.
   *  
   * Base case 1: The position (x, y, z) is outside of the limits of the
   *  maze. They're not valid indices for our 3D array. That's not a valid path,
   *  so just return an empty vector.
   *
   * Base case 2: The position (x, y, z) is an invalid path (0 in the array),
   *  so just return an empty vector.
   *
   * Base case 3: Maybe you've already been here before. You're going in circles.
   *  (That is by design, don't worry!). Fortunately you can use the "visited"
   *  set to quickly test whether or not you have visited the position (x, y, z)
   *  before. If you have been here before, just return an empty vector.
   *
   * Base case 4: You've reached the end of the maze! Use push_back to add the
   *  position (x, y z) to your path. Then go ahead and return path.
   *
   * --- RECURSIVE CALLS ---
   * You've made it past the base cases, so now you need to make some recursive calls.
   *  But first, remember to add the position (x, y, z) to your path and your set of
   *  visited positions.
   *
   * Explore in all 6 directions:
   *  Move left/right by changing x by +/- 1.
   *  Move up/down by changing y by +/- 1.
   *  Move in/out by changing z by +/- 1.
   *
   * To explore in 6 directions, you'll need to make 6 recursive calls. Each recursive
   *  call will return a vector<string>. If any of the recursive calls returns a vector
   *  that is not empty, then it must have found the end of the maze! So return it!
   *  (This will pass it back up the call stack so that solveMaze() gets it). But if
   *  all 6 recursive calls return an empty vector, then that means you explored in
   *  every direction and found no valid path to the end. Return an empty vector to
   *  pass it back up the call stack.
   */ 
  vector<string> findPath(vector<string> path, unordered_set<string>& visited, int x, int y, int z);

  /*
   * Use this function to initialize every cell in the maze to 1.
   */
  void clearMaze();

  /*
   * The importMaze function builds a 3D array of maze values
   *  If importMaze fails, it returns false and doesn't make
   *  any changes. But if it succeeds, then it should call this
   *  setMaze function to save the changes before returning
   *  true.
   */
  void setMaze(int mazeValues[SIZE][SIZE][SIZE]);
public:
  /* These are all explained in PathfinderInterface.h */
  Pathfinder();
  ~Pathfinder();
  string toString();
  void createRandomMaze();
  bool importMaze(string file_name);
  vector<string> solveMaze();
};
