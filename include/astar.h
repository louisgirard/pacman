#ifndef ASTAR
#define ASTAR

#include <vector>
#include <cmath>
#include <queue>
#include <algorithm>
#include <iostream>
#include <limits>

struct Node
{
	int value = 0;
	int x = 0;
	int y = 0;
	int g = std::numeric_limits<int>::max();
	int h = 0;
	struct Node *father = NULL;
};

struct CompareNodes
{
    bool operator()(Node* node1, Node* node2)
    {
		int f1 = node1->g + node1->h;
		int f2 = node2->g + node2->h;
		return (f1 > f2);
    }
};

#ifndef DIRECTION
#define DIRECTION
enum Direction{Left,Right,Up,Down,Null};
#endif

class Astar
{
public:
	std::vector<Direction> shortestPath(std::vector<std::vector<Node>> &graph, int start_x, int start_y, int goal_x, int goal_y);
	Direction shortestPathDirection(std::vector<std::vector<Node>> &graph, int start_x, int start_y, int goal_x, int goal_y);
	void printPath(std::vector<Direction> path);

private:
	std::vector<Direction> reconstructPath(Node *start, Node *current);
	void treatNeighbor(std::vector<std::vector<Node>> &graph, Node *neighbor, Node *current, Node* goal, std::priority_queue<Node*, std::vector<Node*>, CompareNodes> &openList, std::vector<Node*> &closedList);
	int heuristic(Node *start, Node *goal);
	bool equalNodes(Node *node1, Node *node2);
	int nodeValue(std::vector<std::vector<Node>> &graph, Node *node);
	Direction nodeDirection(Node *node);
	
};

#endif